#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cdata_ioctl.h"

int main(void)
{
	int devfd;
	int num = 0;

	devfd = open("/dev/cdata", O_RDONLY);
	if(devfd == -1)
	{
		printf("Can't open /dev/debug\n");
		return -1;
	}

	ioctl(devfd, IOCTL_EMPTY, NULL);
	ioctl(devfd, IOCTL_SYNC, NULL);

	close(devfd);
	return 0;
}
