#include "processOpts2.h"

int processOpts2( int argc, char *argv[], int *rFormatFlag, int *jFormatFlag, int *iFormatFlag){

	int c;
	struct option long_options[] = {
			{ "Rformat", no_argument, NULL, 'r'},
			{ "Iformat", no_argument, NULL, 'i'},
			{ "Jformat", no_argument, NULL, 'j'},
			{ "all", no_argument, NULL, 'a'},
			{ "usage", no_argument, NULL, 'u'},
			{ NULL, 0, NULL, 0}
		};
	while(1){
		int option_index = 0;

		c = getopt_long(argc, argv, "irja",
			long_options, &option_index);

		if (c == -1){
			break;
		}

		switch(c){
		case 'i':
			*iFormatFlag = 1;
			break;
		case 'r':
			*rFormatFlag = 1;
			break;
		case 'j':
			*jFormatFlag = 1;
			break;
		case 'a':
			*rFormatFlag = 1;
			*jFormatFlag = 1;
			*iFormatFlag = 1;
			break;
		case 'u':
			printf("Usage: %s [-r] [-i] [-j] [-a] file [file ...]\n", argv[0]);
			printf("  %-14sprint this information and exit\n", "--usage");
			printf("  %-14sdisassemble R-format instructions\n", "-r --Rformat");
			printf("  %-14sdisassemble I-format instructions\n", "-i --Iformat");
			printf("  %-14sdisassemble J-format instructions\n", "-j --Jformat");
			printf("  %-14sdisassemble all instructions\n", "-a --all");
			return 0;
			break;
		case '?':
			fprintf(stderr, "Usage: %s [-r] [-i] [-j] [-a] file [file ...]\n", argv[0]);
			fprintf(stderr, "  %-14sprint this information and exit\n", "--usage");
			fprintf(stderr, "  %-14sdisassemble R-format instructions\n", "-r --Rformat");
			fprintf(stderr, "  %-14sdisassemble I-format instructions\n", "-i --Iformat");
			fprintf(stderr, "  %-14sdisassemble J-format instructions\n", "-j --Jformat");
			fprintf(stderr, "  %-14sdisassemble all instructions\n", "-a --all");
			return -1;
			break;
		default:
			printf("Something has gone terribly wrong...");
			break;
		}
	}
	if(optind >= argc){
		fprintf(stderr, "Missing file name\n");
		fprintf(stderr, "Usage: %s [-r] [-i] [-j] [-a] file [file ...]\n", argv[0]);
		fprintf(stderr, "  %-14sprint this information and exit\n", "--usage");
		fprintf(stderr, "  %-14sdisassemble R-format instructions\n", "-r --Rformat");
		fprintf(stderr, "  %-14sdisassemble I-format instructions\n", "-i --Iformat");
		fprintf(stderr, "  %-14sdisassemble J-format instructions\n", "-j --Jformat");
		fprintf(stderr, "  %-14sdisassemble all instructions\n", "-a --all");
		return -1;
	}
	if(argc <= 2){
		fprintf(stderr, "Missing file name\n");
		fprintf(stderr, "Usage: %s [-r] [-i] [-j] [-a] file [file ...]\n", argv[0]);
		fprintf(stderr, "  %-14sprint this information and exit\n", "--usage");
		fprintf(stderr, "  %-14sdisassemble R-format instructions\n", "-r --Rformat");
		fprintf(stderr, "  %-14sdisassemble I-format instructions\n", "-i --Iformat");
		fprintf(stderr, "  %-14sdisassemble J-format instructions\n", "-j --Jformat");
		fprintf(stderr, "  %-14sdisassemble all instructions\n", "-a --all");
		return -1;
	}
	return optind;
}