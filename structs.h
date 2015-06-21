struct Rformat{
	unsigned int funct:6;
	unsigned int shamt:5;
	unsigned int rd:5;
	unsigned int rt:5;
	unsigned int rs:5;
	unsigned int opcode:6;
};

struct Jformat {
	unsigned int target:26;
	unsigned int opcode:6;
};

struct Iformat{
	int number:16;
	unsigned int rt:5;
	unsigned int rs:5;
	unsigned int opcode:6;
};

union formats{
	unsigned int valueUsed;
	struct Iformat iInst;
	struct Rformat rInst;
	struct Jformat jInst;
};

struct reg{
	unsigned int regi;
	char *regName;
};

struct reg registers[] = {
	{ 0, "$zero" },
	{ 1, "$at" },
	{ 2, "$v0" },
	{ 3, "$v1" },
	{ 4, "$a0" },
	{ 5, "$a1" },
	{ 6, "$a2" },
	{ 7, "$a3" },
	{ 8, "$t0" },
	{ 9, "$t1" },
	{ 10, "$t2" },
	{ 11, "$t3" },
	{ 12, "$t4" },
	{ 13, "$t5" },
	{ 14, "$t6" },
	{ 15, "$t7" },
	{ 16, "$s0" },
	{ 17, "$s1" },
	{ 18, "$s2" },
	{ 19, "$s3" },
	{ 20, "$s4" },
	{ 21, "$s5" },
	{ 22, "$s6" },
	{ 23, "$s7" },
	{ 24, "$t8" },
	{ 25, "$t9" },
	{ 26, "$k0" },
	{ 27, "$k1" },
	{ 28, "$gp" },
	{ 29, "$sp" },
	{ 30, "$fp" },
	{ 31, "$ra" },
};