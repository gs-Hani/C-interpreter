#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
  	OP_RETURN,
} 	OpCode;

typedef struct {
	int count;
	int lineCount;

  	int capacity;
	int lineCapacity;

	int* linesRep;

	uint8_t* code;
	int* lines;

	ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);

#endif
