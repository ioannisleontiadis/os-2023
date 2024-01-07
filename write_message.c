#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 2

char buffer[BUFFER_SIZE];

void print_message();
void write_message(char *);

int main(int argc, char *argv[]) {
	if (access("/dev/device", F_OK) != 0) {
		printf("\nDevice does not exist.\n\n");
		return 0;
	}

	printf("\n");
	printf("Old message: ");
	print_message();

	write_message(argv[1]);

	printf("New message: ");
	print_message();
	printf("\n");
	
	return 0;
}

void print_message() {
	int fd = open("/dev/device", O_RDONLY);

	if (fd == -1) {
		printf("Cannot open for reading.\n");
		return;
	}

	while (read(fd, buffer, sizeof(buffer))) {
		printf("%s", buffer);
	}

	close(fd);
}

void write_message(char *message) {
	int fd = open("/dev/device", O_WRONLY);

	if (fd == -1) {
		printf("Cannot open for writing.\n");
		return;
	}

	if (message != NULL) {
		write(fd, message, strlen(message));
	}
	write(fd, "\n", 2);

	close(fd);
}	
