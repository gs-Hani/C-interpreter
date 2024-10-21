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
	printf("Constants count = %d\n", chunk->constants.count);
	printf("Constnats capacity = %d\n", chunk->constants.capacity);
	printf("Constants:");
	for (int i = 0; i<chunk->constants.count; i++) {
		if (i==chunk->constants.count-1) {
			printf(",%g\n",chunk->constants.values[i]);
		} else {
			printf(",%g",chunk->constants.values[i]);
		}
	}
	printf("\n");
}

int main(int argc, const char* argv[]) {

	//checkSizes();
//	initVM();

	Chunk chunk;
  	initChunk(&chunk);

//	printChunk(&chunk);

  	int constant = addConstant(&chunk, 1.2);
  	writeChunk(&chunk, OP_CONSTANT, 123);
  	writeChunk(&chunk, constant, 123);
	
	printChunk(&chunk);

  	constant = addConstant(&chunk, 3.4);
  	writeChunk(&chunk, OP_CONSTANT, 123);
  	writeChunk(&chunk, constant, 123);

	printChunk(&chunk);

//  	writeChunk(&chunk, OP_ADD, 123);

//  	constant = addConstant(&chunk, 5.6);
//  	writeChunk(&chunk, OP_CONSTANT, 123);
//  	writeChunk(&chunk, constant, 123);

//  	writeChunk(&chunk, OP_DIVIDE, 123);

//  	writeChunk(&chunk, OP_NEGATE, 123);

  	writeChunk(&chunk, OP_RETURN, 123);


//	printChunk(&chunk);

	disassembleChunk(&chunk, "test chunk");

//	getLine(&chunk,0);
//	getLine(&chunk,1);
//	getLine(&chunk,2);
//	getLine(&chunk,3);
//	getLine(&chunk,4);
//	getLine(&chunk,5);
//	getLine(&chunk,6);

//	interpret(&chunk);
//	freeVM();
 	freeChunk(&chunk);
  	return 0;
}
