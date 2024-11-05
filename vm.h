#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

//#define STACK_MAX 2

typedef struct {
  	Chunk* chunk;
  	uint8_t* ip;
  	uint16_t* lc;
//Value stack[STACK_MAX];
  	Value* stack;
	size_t stackMax;
	size_t stackCount;
  	Value* stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;


void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif
