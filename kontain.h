#define _GNU_SOURCE

#ifndef KONTAIN_H
#define KONTAIN_H

#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#include <sys/capability.h>
#include <sys/mount.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <linux/capability.h>
#include <linux/limits.h>

#define KONTAIN_VERSION 1.0
#define KONTAIN_ARCH "UNIX"

#define null (void*(0)) 
#define SOCKET_SIZE 2

/*
 * for configuring the image in the container setup
 */
typedef struct child_config {
	int32_t argc;
	uid_t 	uid;
	int16_t fd;

	char* 	hostname;
	char** 	argv;
	char* 	mount_dir;

} ChildConfig;

void check_linux(void);
void check_hostname(int*, const size_t);
void check_namespace(void);

#undef SOCKET_SIZE
#endif

