#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cdata_ioctl.h"

int main(void)
{
	int devfd;
	int num = 0;
	pid_t child;

	child = fork();

	devfd = open("/dev/cdata", O_RDWR);
	if( child != 0 ) { // Parent
		write(devfd, "ABCDE", 5);
	}else{ 		// Child
		write(devfd, "12345", 5);
	}

	
	ioctl(devfd, IOCTL_SYNC, NULL);
	ioctl(devfd, IOCTL_EMPTY, NULL);

	close(devfd);
	return 0;
}
