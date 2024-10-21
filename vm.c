#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() {
  vm.stackTop = vm.stack;
}

void initVM() {
	resetStack();
}

void freeVM() {
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

static InterpretResult run() {
	#define READ_BYTE() (*vm.ip++)
	#define READ_BYTE_LONG() (*vm.lc++)
	#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
	#define READ_CONSTANT_LONG() (vm.chunk->constants.values[READ_BYTE_LONG()])
	#define BINARY_OP(op) \
    				do { \
      					double b = pop(); \
      					double a = pop(); \
      					push(a op b); \
    				} while (false)

	for (;;) {
		#ifdef DEBUG_TRACE_EXECUTION
			printf("          ");
    			for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
      				printf("[ ");
      				printValue(*slot);
      				printf(" ]");
    			}
    			printf("\n");
    			disassembleInstruction(vm.chunk,(int)(vm.ip - vm.chunk->code));
		#endif
		uint8_t instruction;
		switch (instruction = READ_BYTE()) {
			case OP_CONSTANT: {
        			Value constant = READ_CONSTANT();
        			push(constant);
        			break;
      			}
			case OP_CONSTANT_LONG: {
				Value constant = READ_CONSTANT_LONG();
				READ_BYTE();
				push(constant);
				break;
			}
			case OP_ADD:		BINARY_OP(+); break;
			case OP_SUBTRACT:	BINARY_OP(-); break;
			case OP_MULTIPLY:	BINARY_OP(*); break;
			case OP_DIVIDE:		BINARY_OP(/); break;
			case OP_NEGATE: 	push(-pop()); break;	       
      			case OP_RETURN: {
				printValue(pop());
				printf("\n");
        			return INTERPRET_OK;
      			}
    		}
  	}	

	#undef READ_BYTE
	#undef READ_BYTE_LONG
	#undef READ_CONSTANT
	#undef READ_CONSTANT_LONG
	#undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  vm.lc = vm.chunk->const_long;
  return run();
}
