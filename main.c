#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

static void repl() {
	char line[1024];
	for (;;) {
		printf("> ");

		if (!fgets(line, sizeof(line), stdin)) {
		printf("\n");
		break;
		}

	interpret(line);
	}
}

static char* readFile(const char* path) {
	FILE* file = fopen(path, "rb");
	if (file == NULL) {
		fprintf(stderr, "Could not open file \"%s\".\n", path);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL) {
	fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
	exit(74);
	}

	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	if (bytesRead < fileSize) {
	fprintf(stderr, "Could not read file \"%s\".\n", path);
	exit(74);
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}

static void runFile(const char* path) {
	char* source = readFile(path);
	InterpretResult result = interpret(source);
	free(source);

	if (result == INTERPRET_COMPILE_ERROR) exit(65);
	if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

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
	initVM();
	
	if (argc == 1) {
		repl();
	} else if (argc == 2) {
		runFile(argv[1]);
	} else {
		fprintf(stderr, "Usage: clox [path]\n");
		exit(64);
	}

	freeVM();

  	return 0;
}
