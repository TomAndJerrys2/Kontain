#include <linux/seccomp.h>
#define SCMP_FAIL SCMP_ACT_ERRNO(EPERM)
#include "kontain.h"


int pivot_root(const char * new_root, const char * old_root) {
	return syscall(SYS_pipe2, new_root, old_root);
}

int sys_call() {
	scmp_filter_ctx ctx = NULL;
	fprintf(stderr, "> Filtering Syscalls...\n");
	
	// this might just need to be a switch LMAOOO
	if(!(ctx = seccomp_init(SCMP_ACT_ALLOW))
			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(chmod), 1, 
				SCMP_A1(SCMP_CMP_MASKED_EQ, S_ISUID, S_ISUID))
			
			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(chmod), 1, 
				SCMP_A1(SCMP_CMP_MASKED_EQ, S_ISGID, S_ISGID))
			
			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(fchmod), 1, 
				SCMP_A1(SCMP_CMP_MASKED_EQ, S_ISUID, S_ISUID))
		
			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(fchmod), 1, 
				SCMP_A1(SCMP_CMP_MASKED_EQ, S_ISGID, S_ISGID))

			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(fchmodat), 1, 
				SCMP_A2(SCMP_CMP_MASKED_EQ, S_ISUID, S_ISUID))

			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(fchmodat), 1, 
				SCMP_A2(SCMP_CMP_MASKED_EQ, S_ISGID, S_ISGID))

			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(unshare), 1, 
				SCMP_A0(SCMP_CMP_MASKED_EQ, CLONE_NEWUSER, CLONE_NEWUSER))

			|| seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(clone), 1, 
				SCMP_A0(SCMP_CMP_MASKED_EQ, CLONE_NEWUSER, CLONE_NEWUSER))

			||  seccomp_rule_add(ctx, SCMP_FAIL, SCMP_SYS(ioctl), 1,
				SCMP_A1(SCMP_CMP_MASKED_EQ, TIOCSTI, TIOCSTI))

			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_keyctl, 0)
			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_add_key, 0)
			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_request_key, 0)

			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_ptrace, 0)

			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_mbind, 0)
			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_migrate_pages, 0)
			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_move_pages, 0)
			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_set_mempolicy, 0)

			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_userfaultfd, 0)
			|| seccomp_rule_add(ctx, SCMP_FAIL, SYS_perf_event_open, 0)

			|| seccomp_attr_set(ctx, SCMP_FLTATR_CTL_NNP, 0)
			|| seccomp_load(ctx)) {
				if(ctx) {
					seccomp_release(ctx);
				}

				fprintf(stderr, "> Failed: %m\n");
				return 1;
			}
	
		seccomp_release(ctx);
		fprintf(stderr, "> Done.\n");

		return 0;
}
			
