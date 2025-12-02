#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int src, dst, n;
	char buf[512];

	if(argc != 3)
  {
		fprintf(2, "please enter the destnation file \n");
		exit(1);
	}

	if(strcmp(argv[1], argv[2]) == 0)
  {
		fprintf(2, "cp: source and destination files are the same\n");
		exit(0);
	}

	if((src = open(argv[1], O_RDONLY)) < 0)
  {
		fprintf(2, "cannot open the source file\n");
		exit(1);
	}

	// Create destination (or truncate) and open for writing
	if((dst = open(argv[2], O_CREATE|O_WRONLY|O_TRUNC)) < 0)
  {
		fprintf(2, "cannot create the destination file"); //not only create but also truncate
		exit(1);
	}


  // Read from source and write to destination


	while((n =read(src, buf, sizeof(buf))) > 0)    //read return number of bytes read or -1 if error or 0 if EOF

  {
		if(write(dst, buf, n) != n)  //!=n means there is an error in rewriting the file
    {
			fprintf(2, "writing error\n");
			exit(1);
		}
	}

	if(n < 0)
  {
		fprintf(2, "reading error\n");
		exit(1);
	}

	close(src);
	close(dst);

	exit(0);
}
