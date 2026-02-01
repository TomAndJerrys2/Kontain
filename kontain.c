#include "kontain.h"

int main(int argc, char** argv) {
	
	
	ChildConfig config = {0};
	int32_t err = 0, option = 0;
	int sockets[SOCKET_SIZE] = {0};
	
	pid_t child_pid = 0;
	int8_t last_optiond = 0;

	while((option = getopt(argc, argv, "c:m:u"))) {
		
		
	}	

	return 0;
}	
