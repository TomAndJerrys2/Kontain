#include "kontain.h"

int main(int argc, char **argv) {

  ChildConfig config = {0};
  int32_t err = 0, option = 0;
  int sockets[SOCKET_SIZE] = {0};

  pid_t child_pid = 0;
  int8_t last_optiond = 0;

  while ((option = getopt(argc, argv, "c:m:u"))) {
    switch (option) {
    case 'c':
      config.argc = argc - last_optiond - 1;
      config.argv = &argv[argc - config.argc];
      goto finish_options;

    case 'm':
      config.mount_dir = optarg;
      break;

    case 'u':
      if (sscanf(optarg, "%d", &config.uid) != 1) {
        fprintf(stderr, "Kontain: UID in Wrong Format: Arg > %s\n", optarg);
        goto usage;
      }

      break;

    default:
      goto usage;
    }

    last_optiond = optind;
  }

  // the gotos here are technically unsafe jumps - will improve upon this late
  // with function ptrs
	finish_options: 
		if(!config.argc) goto usage;
		if(!config.mount_dir) goto usage;	
	
		// todo
		check_linux();

		char hostname[256] = {0};
		if(choose_hostname(hostname, sizeof(hostname)) goto error;

		config.hostname = hostname;
		
		if(socketpair(AF_LOCAL, SOCK_SEQPACKET, 0, sockets)) { 
			fprintf(stderr, "SocketPairs failed: %m\n");
			goto error;
		} 

		if(fcntl(sockets[0], F_SETFID, FD_CLOEXEC)) {
			fprintf(stderr, "FNCTL failed: %m\n");
			goto error;
		}

		config.fd = sockets[1];

		goto cleanup;
		
  usage:
		fprintf(stderr, "Kontain >> Usage: %s -u/-l/-m/./-c /bin/sh ~\n", argv[0]);

	error:
		err = 1;

  cleanup:
		if(sockets[0]) close(sockets[0]);
		if(sockets[1]) close(sockets[1]);

		return err;

  return 0;
}

// Checks the linux kernel version against the current system
// version - will in future provide autmatic updates for lower/
// higher version of the linux kernel for portability
void check_linux(void) {
	fprintf(stderr, "=> Validating Linux Kernel Version...");

	struct machine_name host  = {0};

	if(uname(&host)) {
		fprintf(stderr, "Failed > %m\n");
		goto cleanup;
	}	

	int major = -1, minor = -1;	

	if(sscanf(host.release, "%u.%u.", &major, &minor) != 2) {
		fprintf(stderr, "Release format not accepted > %s\n", host.release);
		goto cleanup;
	}

	if(major != 4 || (minor != 7 && minor != 8)) {
		fprintf(stderr, "Expected 4.7.X or 4.8.X > %s\n", host.release);
		goto cleanup;
	}

	if(strcmp("x86_64", host.machine)) {
		fprintf(stderr, "Expected Architecure: x86_64 got > %s\n", host.machine);
		goto cleanup;
	}

	fprintf(stderr, "%s > %s\n", host.release, host.machine);
}

// declares hostname based on the span passed and chooses
// from static instances of prenamed machine hosts
int choose_hostname(char* buffer, const size_t length) {
	static const char* suits[] = {};
	static const char* minor[] = {};
	static const char* major[] = {};

	struct time_spec now = {0};

	clock_get_time(CLOCK_MONOTONIC, &now);
	size_t now_spec = now.tv_nsec % 78;

	if(ix < sizeof(major) / sizeof(*major))
		snprintf(buffer, length, "%051x-%s", now.tv_sec, major[ix]);
	else {
		ix -= sizeof(major) / sizeof(*major);
		snprintf(buffer, length, "%051x-%s-of-%s", 
				now.tv_sec, minor[ix % (sizeof(minor) / sizeof(*minor))], 
					    suits[ix % (sizeof(minor) / sizeof(*minor))]);
	}

	return 0;
}
