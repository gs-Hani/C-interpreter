#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  	chunk->count = 0;
	chunk->lineCount = 0;

  	chunk->capacity = 0;
	chunk->lineCapacity = 0;

	chunk->linesRep = NULL;

  	chunk->code = NULL;
	chunk->lines = NULL;

  	initValueArray(&chunk->constants);
}

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

int addConstant(Chunk* chunk, Value value) {
  	writeValueArray(&chunk->constants, value);
  	return chunk->constants.count - 1;
}

