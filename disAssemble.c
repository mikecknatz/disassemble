#include "processOpts2.h"

int
main( int argc, char *argv[] ){
	char *progName;
	progName = argv[0];
	int iFormatFlag = 0;
	int jFormatFlag = 0;
	int rFormatFlag = 0;
	int numOptions = processOpts2( argc, argv, &rFormatFlag, &jFormatFlag, &iFormatFlag);
	//0 for --usage -1 for error, processOpts2 also checks for at least one option having been entered.
	if(numOptions < 1){
		if(numOptions == 0)
			return 0;
		else
			return 1;	
	}
	argc = argc - (numOptions-1);
	argv = argv + (numOptions-1);
	argv[0] = progName;
	
	//isError returns 1 for errors otherwise fileReadWrite handles files and sorts
	int isError = readMipsFile(argc, argv, rFormatFlag, jFormatFlag, iFormatFlag);
	if(isError != 0)
		return 1;
	return 0;
} /* main */