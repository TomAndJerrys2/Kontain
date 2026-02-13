#define MEMORY "1073741824"
#define SHARES "256"
#define PIDS "64"
#define WEIGHT "10"
#define FD_COUNT 64

struct cgrp_control {

	char control[256];
	struct cgrp_setting {
		char name[256];
		char value[256];
	} **settings;
};

struct cgrp_setting add_to_tasks = {
	.name = "tasks",
	.value = "0"
};

struct cgrp_control *cgrps[] = {

	& (struct cgrp_control) {
		.control = "memory",
		.settings = (struct cgrp_setting* []) {
			& (struct cgrp_setting) {
				.name = "memory.limit_in_bytes",
				.value = MEMORY
			},

			& (struct cgrp_setting) {
				.name = "memory.limit_in_bytes",
				.value = MEMORY
			},

			&add_to_tasks,
			NULL
		}
	},

	& (struct cgrp_control) {
		.control = "cpu",
		.settings = (struct cgrp_setting* []) {
			&(struct cgrp_setting) {
				.name = "cpu.shares",
				.value = SHARES
			},

			&add_to_tasks,
			NULL
		}
	},

	& (struct cgrp_control) {
		.control = "pids",
		.settings = (struct cgrp_setting* []) {
			&(struct cgrp_setting) {
				.name = "pids.max",
				.value = PIDS
			},

			&add_to_tasks,
			NULL
		}
	},

	&(struct cgrp_control) {
		.control = "blkio",
		.settings = (struct cgrp_setting* []) {
			&(struct cgrp_setting) {
				.name = "blkio.weight",
				.value = PIDS
			},

			&add_to_tasks,
			NULL
		}
	},

	NULL
};

int resources(const ChildConfig * config) {
	fprintf(stderr, "> Setting CGroups...\n");

	for(struct cgrp_control** cgrp = cgrps; *cgrp; cgrp++) {
		char dir[PATH_MAX] = {0};

		fprintf(stderr, "%s...", (*cgrp)->control);
		if(snprintf(dir, sizeof(dir), "/sys/fs/cgroup/%s/%s", 
					(*cgrp)->control, config->hostname) == -1) {
			return -1;
		}

		if(mkdir(dir, S_IRUSR | S_IWUSER | S_IXUSER)) {
			fprintf(stderr, "mkdir %s failed: %m\n", dir);
			return -1;
		}

		for(struct cgrp_setting** setting = (*cgrp)->settings; *setting; setting++) {
			char path[PATH_MAX} = {0};
			int fd = 0;

			if(snprintf(path, sizeof(path), "%s/%s", dir, (*setting)->name) == -1) {
				fprintf(stderr, "> snprintf failed: %m\n");
				return -1;_
			}

			if((fd = open(path, O_WRONGLY)) == -1)  {
				fprintf(stderr, "> Opening %s failed: %m\n", path);
				return -1;
			}

			if(write(fd, (*setting)->value, strlen((*setting)->value)) == -1) {
				fprintf(stderr, "> Writing to %s failed: %m\n", path);
				close(fd);

				return -1;
			}

			close(fd);
		}
	}

	fprintf(stderr, "> Done\n");

	fprintf(stderr, "> Setting rlimit...\n");
	if(setrlimit(RLIMIT_NOFILE, &(struct rlimit) {
		.rlim_max = FD_COUNT,
		.rlim_cur = FD_COUNT		
	})) {
		fprintf(stderr, "> Failed: %m\n");
		return 1;
	}

	fprintf(stderr, "> Done\n");
	return 0;
}
