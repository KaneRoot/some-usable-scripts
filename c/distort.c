#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sndfile.h>

#define BUFFER_LEN  1024

int main(int argc, char **argv) {
	int    distortionLevel;
	SNDFILE *infile, *outfile;
	SF_INFO sfinfo;
	double buffer[BUFFER_LEN];

	// Check for distortion level argument
	if (argc < 2) {
		printf("Usage: %s distortion_level\n", argv[0]);
		return 1;
	}
	distortionLevel = atoi(argv[1]);

	// Open standard input as input file
	if (!(infile = sf_open_fd(0, SFM_READ, &sfinfo, 0))) {
		printf("Error: could not open standard input\n");
		return 1;
	}

	// Open standard output as output file
	if (!(outfile = sf_open_fd(1, SFM_WRITE, &sfinfo, 0))) {
		printf("Error: could not open standard output\n");
		return 1;
	}

	// Read and process data
	while (sf_read_double(infile, buffer, BUFFER_LEN) > 0) {
		for (int i=0; i<BUFFER_LEN; i++) {
			// Add distortion to the sample
			buffer[i] = buffer[i] * (1.0 + (distortionLevel/100.0) * sin(2.0 * M_PI * buffer[i]));
		}

		// Write the processed sample to the output file
		sf_write_double(outfile, buffer, BUFFER_LEN);
	}

	// Close files
	sf_close(infile);
	sf_close(outfile);

	return 0;
}
