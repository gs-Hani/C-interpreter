#include <stdio.h>

#include "debug.h"
#include "value.h"

int getLine(Chunk* chunk, int index) {	

	int seq = index+1;
//	printf("init seq = %d\n", seq);
	for (int i=0; i < chunk->lineCount; i++) {
	
		if (seq - chunk->linesRep[i] <= 0) {
//			printf("\t \tIndex %d = %d,lineReps = %d, final sequence = %d\n", index, chunk->lines[i],chunk->linesRep[i],seq);
			return chunk->lines[i];
		} else {
			seq -= chunk->linesRep[i];
//			printf("seq = %d\n",seq);
		}
	}
}

static int simpleInstruction(const char* name, int offset) {
  	printf("%s\n", name);
  	return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk,int offset) {
  	uint8_t constant = chunk->code[offset + 1];
	printf("%-16s %4d ", name, constant);
  	printValue(chunk->constants.values[constant]);
  	printf("\n");
	return offset + 2;
}

static int constantLongInstruction(const char* name, Chunk* chunk, int offset, uint16_t* instructionL) {
	uint16_t constant = chunk->const_long[*instructionL];
	printf("%-16s %4d ", name, constant);
	printValue(chunk->constants.values[constant]);
	printf("\n");
	instructionL++;
	return offset + 2;	
}

int disassembleInstruction(Chunk* chunk, int offset) {
  	printf("%04d ", offset);

//	if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
	if (offset > 0 && getLine(chunk,offset) == getLine(chunk, offset-1)) {
    		printf("   | ");
  	} else {
//    		printf("%4d ", chunk->lines[offset]);
		printf("%4d ", getLine(chunk, offset));
  	}

  	uint8_t instruction = chunk->code[offset];
	uint16_t instructionL = 0;
  	switch (instruction) {
		case OP_CONSTANT:
      			return constantInstruction("OP_CONSTANT", chunk, offset);
		case OP_CONSTANT_LONG:
			return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset, &instructionL);
		case OP_ADD:
      			return simpleInstruction("OP_ADD", offset);
    		case OP_SUBTRACT:
      			return simpleInstruction("OP_SUBTRACT", offset);
    		case OP_MULTIPLY:
      			return simpleInstruction("OP_MULTIPLY", offset);
    		case OP_DIVIDE:
      			return simpleInstruction("OP_DIVIDE", offset);
		case OP_NEGATE:
			return simpleInstruction("OP_NEGATE", offset);
    		case OP_RETURN:
      			return simpleInstruction("OP_RETURN", offset);
    		default:
      			printf("Unknown opcode %d\n", instruction);
      		return offset + 1;
  	}
}

void disassembleChunk(Chunk* chunk, const char* name) {
  	printf("== %s ==\n", name);

  	for (int offset = 0; offset < chunk->count;) {
    		offset = disassembleInstruction(chunk, offset);
  	}
}

