#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"
// file types st.type get T_device , T_DIR , T_FILE
// DIRSIZ constant for maximm filw in xv6 14 characters
void
find(char *path, char *target)
{
    char buf[512], *p; // buffer and pointer to build path ex/ex
    int fd;
    struct dirent de; // directory entry represent a file (name, number)
    struct stat st; // data about file

    // Try to open the directory / file
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    // Get status info
    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    // If it's not a directory error
    if (st.type != T_DIR) {
        close(fd);
        return;
    }
    //check if the path is longer than buffer size

    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
        fprintf(2, "find: path too long\n");
        close(fd);
        return;
    }
     // Prepare buffer: base path + "/" + entry name

    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    // Read each entry inside the directory
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {

        // Skip empty entries
        if (de.inum == 0)
            continue;

        // Skip "." and ".."
        if (!strcmp(de.name, ".") || !strcmp(de.name, ".."))
            continue;

        // Append the filename to the path buffer
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0; //add zeero to be a stringg

        // Get file status a file or a directory ?
        if (stat(buf, &st) < 0) {
           fprintf(2, "find: cannot stat %s\n", path);
            continue;
        }

        // Check if filename matches the target name
        if (!strcmp(de.name, target)) {
            printf("%s\n", buf);
        }

        // If it's a directory, recurse into it
        if (st.type == T_DIR) {
            find(buf, target);
        }
    }
    close(fd);
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(2, "format: find <directory> <filename>\n");
        exit(1);
    }

    find(argv[1], argv[2]);  // start searching
    exit(0);
}
