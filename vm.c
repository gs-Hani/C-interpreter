#include <stdio.h>
#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm; 

void initVM() {
}

void freeVM() {
}

static InterpretResult run() {
	#define READ_BYTE() (*vm.ip++)
	#define READ_BYTE_LONG() (*vm.lc++)
	#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
	#define READ_CONSTANT_LONG() (vm.chunk->constants.values[READ_BYTE_LONG()])
	for (;;) {
		#ifdef DEBUG_TRACE_EXECUTION
    			disassembleInstruction(vm.chunk,(int)(vm.ip - vm.chunk->code));
		#endif
		uint8_t instruction;
		switch (instruction = READ_BYTE()) {
			case OP_CONSTANT: {
        			Value constant = READ_CONSTANT();
        			printValue(constant);
        			printf("\n");
        			break;
      			}
			case OP_CONSTANT_LONG: {
				Value constant = READ_CONSTANT_LONG();
				READ_BYTE();
				printValue(constant);
				printf("\n");
				break;
			}	       
      			case OP_RETURN: {
        			return INTERPRET_OK;
      			}
    		}
  	}	

	#undef READ_BYTE
	#undef READ_BYTE_LONG
	#undef READ_CONSTANT
	#undef READ_CONSTANT_LONG
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  vm.lc = vm.chunk->const_long;
  return run();
}
