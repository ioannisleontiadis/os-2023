#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char argv[]) {

	printf("\n");
	if (access("/dev/device", F_OK) == 0) {
		printf("Device found.\n");
	} else {
		printf("Device not found.\n");
	}

	if (open("/dev/device", O_RDWR) > 0) {
		printf("Device opened.\n");
	} else {
		printf("Device could not be opened.\n");
	}
	
	if (open("/dev/device", O_RDWR) > 0) {
		printf("Device opened again.\n");
	} else {
		printf("Device could not be opened again.\n");
	}
	printf("\n");

	return 0;
}
