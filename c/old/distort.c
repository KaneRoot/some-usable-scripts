#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sndfile.h>

#define BUFFER_LEN  1024

void applyOverdriveDistortion (SNDFILE *inputFile, SNDFILE *outputFile);
void applyFuzzDistortion      (SNDFILE *inputFile, SNDFILE *outputFile);
void applyDistortion          (SNDFILE *inputFile, SNDFILE *outputFile);
void applyBoostDistortion     (SNDFILE *inputFile, SNDFILE *outputFile, float gain);

int main(int argc, char **argv) {
	int    distortionLevel;
	SNDFILE *infile, *outfile;
	SF_INFO sfinfo;

	// Check for distortion level argument
	if (argc < 3) {
		printf("Usage: %s distortion-type distortion_level\n", argv[0]);
		return 1;
	}
	distortionLevel = atoi(argv[2]);

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

	if (memcmp(argv[1], "overdrive", strlen("overdrive")) == 0) {
		fprintf(stderr, "overdrive\n");
		applyOverdriveDistortion(infile, outfile);
	}
	if (memcmp(argv[1], "fuzz", strlen("fuzz")) == 0) {
		fprintf(stderr, "fuzz\n");
		applyFuzzDistortion(infile, outfile);
	}
	if (memcmp(argv[1], "distortion", strlen("distortion")) == 0) {
		fprintf(stderr, "distortion\n");
		applyDistortion(infile, outfile);
	}
	if (memcmp(argv[1], "boost", strlen("boost")) == 0) {
		fprintf(stderr, "boost\n");
		applyBoostDistortion(infile, outfile, distortionLevel);
	}

//	// Read and process data
//	double buffer[BUFFER_LEN];
//	while (sf_read_double(infile, buffer, BUFFER_LEN) > 0) {
//		for (int i=0; i<BUFFER_LEN; i++) {
//			// Add distortion to the sample
//			buffer[i] = buffer[i] * (1.0 + (distortionLevel/100.0) * sin(2.0 * M_PI * buffer[i]));
//		}
//
//		// Write the processed sample to the output file
//		sf_write_double(outfile, buffer, BUFFER_LEN);
//	}

	// Close files
	sf_close(infile);
	sf_close(outfile);

	return 0;
}

// TODO: use these functions

// function to apply overdrive distortion to an audio signal using sndfile API
void applyOverdriveDistortion(SNDFILE *inputFile, SNDFILE *outputFile)
{
    // read in the data from the input file
    int bufferSize = 1024;
    float *inputBuffer = malloc(bufferSize * sizeof(float));
    int framesRead;
    while ((framesRead = sf_readf_float(inputFile, inputBuffer, bufferSize))) {
        // apply overdrive distortion
        for (int i = 0; i < framesRead; i++) {
            float x = inputBuffer[i];
            float y = (1 + x) * (1 + x) / (1 + 2 * x + x * x);
            inputBuffer[i] = y;
        }
        // write processed data to output file
        sf_writef_float(outputFile, inputBuffer, framesRead);
    }
    free(inputBuffer);
}

// function to apply fuzz distortion to an audio signal using sndfile API
void applyFuzzDistortion(SNDFILE *inputFile, SNDFILE *outputFile)
{
    // read in the data from the input file
    int bufferSize = 1024;
    float *inputBuffer = malloc(bufferSize * sizeof(float));
    int framesRead;
    while ((framesRead = sf_readf_float(inputFile, inputBuffer, bufferSize))) {
        // apply fuzz distortion
        for (int i = 0; i < framesRead; i++) {
            float x = inputBuffer[i];
            float y = x / (1 + fabs(x));
            inputBuffer[i] = y;
        }
        // write processed data to output file
        sf_writef_float(outputFile, inputBuffer, framesRead);
    }
    free(inputBuffer);
}

// function to apply distortion to an audio signal using sndfile API
void applyDistortion(SNDFILE *inputFile, SNDFILE *outputFile)
{
    // read in the data from the input file
    int bufferSize = 1024;
    float *inputBuffer = malloc(bufferSize * sizeof(float));
    int framesRead;
    while ((framesRead = sf_readf_float(inputFile, inputBuffer, bufferSize))) {
        // apply distortion
        for (int i = 0; i < framesRead; i++) {
            float x = inputBuffer[i];
            float y = x / (1 + fabs(x));
            y = y * 0.5 + 0.5;
            inputBuffer[i] = y;
        }
        // write processed data to output file
        sf_writef_float(outputFile, inputBuffer, framesRead);
    }
    free(inputBuffer);
}

// function to apply boost to an audio signal using sndfile API
void applyBoostDistortion(SNDFILE *inputFile, SNDFILE *outputFile, float gain)
{
    // read in the data from the input file
    int bufferSize = 1024;
    float *inputBuffer = malloc(bufferSize * sizeof(float));
    int framesRead;
    while ((framesRead = sf_readf_float(inputFile, inputBuffer, bufferSize))) {
        // apply boost
        for (int i = 0; i < framesRead; i++) {
            float x = inputBuffer[i];
            float y = x * gain;
            inputBuffer[i] = y;
        }
        // write processed data to output file
        sf_writef_float(outputFile, inputBuffer, framesRead);
    }
    free(inputBuffer);
}
