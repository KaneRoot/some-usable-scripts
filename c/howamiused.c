#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define TMPDIR "/tmp/"

// When invoked, this application writes its input, parameters and
// environment variables in differents files: last-(input|parameters|env) in TMPDIR.
//
// Useful for debugging purposes.

int main(int argc, char **argv, char **env) {
	int fd = open(TMPDIR "last-input", O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0) { return -1; }

	size_t nb = 0;
	char buffer[BUFSIZ];
	while((nb = read(0, buffer, BUFSIZ-1))) {
		dprintf(fd, "%*s", (int)nb, buffer);
	}

	close(fd);
	fd = open(TMPDIR "last-parameters", O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0) { return -1; }

	for (size_t i = 0 ; i < argc ; i++) {
		dprintf(fd, "%s\n", argv[i]);
	}

	close(fd);
	fd = open(TMPDIR "last-env", O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0) { return -1; }

	while (env[0] != NULL) {
		dprintf(fd, "%s\n", env[0]);
		printf("env: %s\n", env[0]);
		env++;
	}

	close(fd);

	return 0;
}
