#ifndef _CDATA_IOCTL_H_
#define _CDATA_IOCTL_H_

#include <linux/ioctl.h>

#define IOCTL_EMPTY _IO(0xCD, 1)
#define IOCTL_SYNC  _IO(0xCD,2)

#endif
