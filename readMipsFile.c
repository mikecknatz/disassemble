#include "functCodes.h"
#include "opCodes.h"
#include "processOpts2.h"
#include "structs.h"
//structs.h contains the unions and structs used for this assignment that I made.
/*
	Michael Conrad Knatz
	Partial mips disassembler.
*/
int
readMipsFile(int argc, char *argv[], int rFormatFlag, int jFormatFlag, int iFormatFlag){
	unsigned long progCounter;
	int valueUsed;
	int i;
	FILE *stream;
	union formats fromHFile;
	for(i = 1; i < argc; i++){
		printf("File '%s' contains:\n", argv[i]);
		//Open and check the file
		stream = fopen(argv[i], "r");
		//File does not exist, or is in use, or is denied access, etc...
		if(stream == NULL){
			fprintf(stderr, "Unable to open %s for reading\n", argv[i]);
			fprintf(stderr, "Usage: %s [-r] [-i] [-j] [-a] file [file ...]\n", argv[0]);
			fprintf(stderr, "  %-14sprint this information and exit\n", "--usage");
			fprintf(stderr, "  %-14sdisassemble R-format instructions\n", "-r --Rformat");
			fprintf(stderr, "  %-14sdisassemble I-format instructions\n", "-i --Iformat");
			fprintf(stderr, "  %-14sdisassemble J-format instructions\n", "-j --Jformat");
			fprintf(stderr, "  %-14sdisassemble all instructions\n", "-a --all");
			return 1;
		}

		//mips main address
		progCounter = 0x00400024;
		while(!feof(stream)){
			valueUsed = 0;
			if(!fread(&fromHFile, 1, 4, stream) != 0){
				break;
			}
			//Done
			if(rFormatFlag){
				if(fromHFile.rInst.opcode == 0){
					valueUsed = 1;
					//funct rd, rs, rt
					if(fromHFile.rInst.funct != 8 && fromHFile.rInst.funct != 12 && !(fromHFile.rInst.funct < 4)){
						printf("0x%08lX %-7s  %s, %s, %s\n", progCounter,
							FunctCodes[fromHFile.rInst.funct].name, registers[fromHFile.rInst.rd].regName,
							registers[fromHFile.rInst.rs].regName, registers[fromHFile.rInst.rt].regName);
					}
					//jr $r
					else if(fromHFile.rInst.funct == 8){
						printf("0x%08lX %-7s  %s\n", progCounter, FunctCodes[fromHFile.rInst.funct].name, 
							registers[fromHFile.rInst.rs].regName);
					}
					//syscall
					else if(fromHFile.rInst.funct == 12){
						printf("0x%08lX %-7s  \n", progCounter, FunctCodes[fromHFile.rInst.funct].name);
					}
					//sra sll srl
					else{
						printf("0x%08lX %-7s  %s, %s, %d\n", progCounter,
							FunctCodes[fromHFile.rInst.funct].name, registers[fromHFile.rInst.rd].regName, 
							registers[fromHFile.rInst.rt].regName, fromHFile.rInst.shamt);
					}
				}
			}

			//Done
			if(jFormatFlag && !valueUsed){
				if(fromHFile.jInst.opcode == 3 || fromHFile.jInst.opcode == 2){
					printf("0x%08lX %-7s  0x%08lX\n", progCounter, OpCodes[fromHFile.jInst.opcode].name,
						((fromHFile.jInst.target*4)+(0xf0000000 & progCounter)));
				}
			}


			if(iFormatFlag && !valueUsed){
				//unsigned functions
				if((fromHFile.iInst.opcode < 15 && fromHFile.iInst.opcode > 7)){
					//Use masks to maintain unsigned status
					if(fromHFile.iInst.opcode == 9 || fromHFile.iInst.opcode > 11){
						printf("0x%08lX %-7s  %s, %s, %u\n", progCounter, OpCodes[fromHFile.iInst.opcode].name, 
							registers[fromHFile.iInst.rt].regName,  registers[fromHFile.iInst.rs].regName, 
							(fromHFile.iInst.number & 0x0000FFFF));
					}
					else{
						printf("0x%08lX %-7s  %s, %s, %d\n", progCounter, OpCodes[fromHFile.iInst.opcode].name, 
							registers[fromHFile.iInst.rt].regName,  registers[fromHFile.iInst.rs].regName, 
							fromHFile.iInst.number);
					}
				}
				//lui
				else if(fromHFile.iInst.opcode == 15){
					printf("0x%08lX %-7s  %s, %d\n", progCounter, OpCodes[fromHFile.iInst.opcode].name, 
						registers[fromHFile.iInst.rt].regName, (unsigned int)(fromHFile.iInst.number & 0x0000FFFF));
				}
				//branch functions
				else if(fromHFile.iInst.opcode == 4 || fromHFile.iInst.opcode == 5){
					printf("0x%08lX %-7s  %s, %s, 0x%08lX\n", progCounter, OpCodes[fromHFile.iInst.opcode].name, 
						registers[fromHFile.iInst.rs].regName,  registers[fromHFile.iInst.rt].regName, 
						(fromHFile.iInst.number*4)+progCounter);
				}
				//remaining functions
				else if(fromHFile.iInst.opcode > 16){
					printf("0x%08lX %-7s  %s, %d(%s)\n", progCounter, OpCodes[fromHFile.iInst.opcode].name, 
						registers[fromHFile.iInst.rt].regName,  fromHFile.iInst.number, 
						registers[fromHFile.iInst.rs].regName);
				}
			}
			progCounter += 4;
		}
		printf("\n");

		//close and check for correct close.
		int properClose = fclose(stream);
		if(properClose != 0){
			fprintf(stderr, "Unable to close %s\n", argv[i]);
			fprintf(stderr, "Usage: %s [-r] [-i] [-j] [-a] file [file ...]\n", argv[0]);
			fprintf(stderr, "  %-14sprint this information and exit\n", "--usage");
			fprintf(stderr, "  %-14sdisassemble R-format instructions\n", "-r --Rformat");
			fprintf(stderr, "  %-14sdisassemble I-format instructions\n", "-i --Iformat");
			fprintf(stderr, "  %-14sdisassemble J-format instructions\n", "-j --Jformat");
			fprintf(stderr, "  %-14sdisassemble all instructions\n", "-a --all");
			return 1;
		}
	}
	return 0;
}