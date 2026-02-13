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
