#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "mus2mid.h"

#define MUS2MID_VERSION "1.0.0"

static void usage(void)
{
	fprintf(stderr,
			"mus2mid %s\n"
			"Converts a DOOM MUS file to a MIDI file.\n"
			"\n"
			"Usage: mus2mid <input.mus> <output.midi>\n"
			"  -h, --help              Output this help and exit\n"
			"  -V, --version           Output version and exit\n"
			"\n", MUS2MID_VERSION);
	exit(EXIT_FAILURE);
}

char * inputFilePath=0;
char * outputFilePath=0;

static void parse_options(int argc, char **argv)
{
	int i;

	for(i=1;i<argc;i++)
	{
		int lastarg = i==argc-1;

		if(!strcmp(argv[i],"-h") || !strcmp(argv[i], "--help"))
		{
			usage();
		}
		else if(!strcmp(argv[i],"-V") || !strcmp(argv[i], "--version"))
		{
			printf("mus2mid %s\n", MUS2MID_VERSION);
			exit(EXIT_SUCCESS);
		}
		else
		{
			break;
		}
	}

	argc -= i;
	argv += i;

	if(argc<2)
		usage();

	inputFilePath = argv[0];
	outputFilePath = argv[1];
}

int main(int argc, char ** argv)
{
	FILE * inputFile=0;
	FILE * outputFile=0;
	struct stat s;

	parse_options(argc, argv);

	if(stat(inputFilePath, &s)==-1)
	{
		fprintf(stderr, "Failed to stat [%s]: %s\n", inputFilePath, strerror(errno));
		goto cleanup;
	}

	inputFile = fopen(inputFilePath, "r");
	if(!inputFile)
	{
		fprintf(stderr, "Failed to open input file for reading [%s]: %s\n", inputFilePath, strerror(errno));
		goto cleanup;
	}

	outputFile = fopen(outputFilePath, "w");
	if(!outputFile)
	{
		fprintf(stderr, "Failed to open output file for writing [%s]: %s\n", outputFilePath, strerror(errno));
		goto cleanup;
	}

	if(mus2mid(inputFile, outputFile))
	{
		fprintf(stderr, "Failed to convert [%s] to [%s]\n", inputFilePath, outputFilePath);
		goto cleanup;
	}

	goto cleanup;

	cleanup:
	fclose(inputFile);
	fclose(outputFile);

	exit(EXIT_SUCCESS);
}
