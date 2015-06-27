disassemble

This repository contains a partial mips disassembler written in C.
Eventually I plan on finishing this project, but until then I am leaving it here as an example.

Quick run through:
  It will run line by line through a given file and check the opcodes against known r i and/or j instructions.
  It does this by having a union with the various formats in structs and referencing the listed mips instructions.
