#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_CONSTANT_LONG,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_NEGATE,
  	OP_RETURN,
} 	OpCode;

typedef struct {
	int count;
	int capacity;
	uint8_t* code;

	int count_long;
	int capacity_long;
	uint16_t* const_long;

	int lineCount; 
	int lineCapacity;
	int* linesRep;
	int* lines;

	ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void writeConstant(Chunk* chunk, Value value, int line);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);

#endif
