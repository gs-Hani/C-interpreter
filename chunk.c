#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;

	chunk->count_long = 0;
	chunk->capacity_long = 0;
	chunk->const_long = NULL;

	chunk->lineCount = 0;
	chunk->lineCapacity = 0;
	chunk->linesRep = NULL;
	chunk->lines = NULL;

  	initValueArray(&chunk->constants);
}

void updateLine(Chunk* chunk, int line);

void freeChunk(Chunk* chunk) {
  	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->capacity);
  	freeValueArray(&chunk->constants);
  	initChunk(chunk);
}


void writeChunk(Chunk* chunk, uint8_t byte,int line ) {
  	if (chunk->capacity < chunk->count + 1) {
    		int oldCapacity = chunk->capacity;
    		chunk->capacity = GROW_CAPACITY(oldCapacity);
    		chunk->code = GROW_ARRAY(uint8_t, chunk->code,oldCapacity, chunk->capacity);	
  	}

  	chunk->code[chunk->count] = byte;
	chunk->count++;
	
	updateLine(chunk, line);

	if(byte == OP_CONSTANT_LONG) {
		chunk->code[chunk->count] = byte;
		chunk->count++;
	}
}

int addConstant(Chunk* chunk, Value value) {
  	writeValueArray(&chunk->constants, value);
  	return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, Value value, int line) {

	 writeValueArray(&chunk->constants, value);

	uint16_t index = chunk->constants.count - 1;
		
	if(chunk->capacity_long < chunk->count_long + 1) {
		int oldCapacity = chunk->capacity_long;
		chunk->capacity_long = GROW_CAPACITY(oldCapacity);
		chunk->const_long = GROW_ARRAY(uint16_t,chunk->const_long,oldCapacity, chunk->capacity_long);
	}

	chunk->const_long[chunk->count_long] = index;
	chunk->count_long++;

	updateLine(chunk, line);

}

void updateLine(Chunk* chunk, int line) {
	if (chunk->lineCapacity < chunk->lineCount + 1) {
		int oldCapacity = chunk->lineCapacity;
		chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
		chunk->lines = GROW_ARRAY(int, chunk->lines,oldCapacity, chunk->lineCapacity);	
		chunk->linesRep = GROW_ARRAY(int, chunk->linesRep,oldCapacity, chunk->lineCapacity);
	}

	if (line == chunk->lines[chunk->lineCount-1]) {
		chunk->linesRep[chunk->lineCount-1]++;     	
	} else {
		chunk->lines[chunk->lineCount] = line;
		chunk->linesRep[chunk->lineCount] = 1;
		chunk->lineCount++;
	}
}
