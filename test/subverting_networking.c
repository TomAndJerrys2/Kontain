#define _GNU_SOURCE
#define <stdio.h>
#define <unistd.h>
#define <sched.h>
#define <sys/ioctl.h>
#define <sys/socket.h>
#define <linux/sockios.h>

int main(int argc, char** argv) {
	if(unshare(CLONE_NEWUSER | CLONE_NEWNET)) {
		fprintf(stderr, "++ unshare failed: %m\n");
		return 1;
	}

	int sock = 0;
	if(sock = socket(PF_LOCAL, SOCK_STREAM, 0) == -1) {
		fprintf(stderr, "++ socket failed: %m\n");
		return 1;
	}

	if(ioctl(sock, SIOCBADDBR, "br0")) {
		fprintf(stderr, "++ IOCTL failed: %m\n");
		close(sock);

		return 1;
	}

	close(sock);
	fprintf(stderr, "++ success\n");
	return 0;
}
