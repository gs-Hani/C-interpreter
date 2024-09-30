#include <stdio.h> //for testing

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

void checkSizes() {
	printf("int = %lu\n",sizeof(int));
	printf("uint16_t = %lu\n",sizeof(uint16_t));
	printf("double = %lu\n",sizeof(double));
}

void printChunk(Chunk* chunk) {
	printf("Count = %d\n", chunk->count);
	printf("Capacity = %d\n", chunk->capacity);
	printf("lineCount = %d\n", chunk->lineCount);
	printf("lineCapacity = %d\n", chunk->lineCapacity);

	printf("Codes:");
	for (int i = 0; i< chunk->count; i++) {
		if (i==chunk->count-1) {
			printf(",%d\n",chunk->code[i]);
		} else {
			printf(",%d",chunk->code[i]);
		}
	}

	printf("lines:");
	for (int i = 0; i< chunk->lineCount; i++) {
		if (i==chunk->lineCount-1) {
			printf(",%d\n",chunk->lines[i]);
		} else {
			printf(",%d",chunk->lines[i]);
		}
	}

	printf("Lines repetition:");
	for (int i = 0; i< chunk->lineCount; i++) {
		if (i==chunk->lineCount-1) {
			printf(",%d\n",chunk->linesRep[i]);
		} else {
			printf(",%d",chunk->linesRep[i]);
		}
	}
}

int main(int argc, const char* argv[]) {

	//checkSizes();
	initVM();

	Chunk chunk;
  	initChunk(&chunk);

	int constant = addConstant(&chunk, 1.2);

  	writeChunk(&chunk, OP_CONSTANT,123);
  	writeChunk(&chunk, constant,123);
	writeChunk(&chunk, OP_CONSTANT_LONG,223);
	writeConstant(&chunk, 2.4, 223);
	writeChunk(&chunk, OP_CONSTANT,456);
  	writeChunk(&chunk, constant,456);
  	writeChunk(&chunk, OP_RETURN,678);

//	printChunk(&chunk);

	disassembleChunk(&chunk, "test chunk");
//	getLine(&chunk,0);
//	getLine(&chunk,1);
//	getLine(&chunk,2);
//	getLine(&chunk,3);
//	getLine(&chunk,4);
//	getLine(&chunk,5);
//	getLine(&chunk,6);

	freeVM();
 	freeChunk(&chunk);
  	return 0;
}
