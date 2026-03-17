//Chapter 15 Virtual Machine

#include <stdlib.h>
#include <string.h>

#include "chunk.h"

static void* growArray(void* pointer, size_t oldSize, size_t newSize) {
    (void)oldSize;
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}

#define GROW_CAPACITY(capacity) \
((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
(type*)growArray(pointer, sizeof(type) * (oldCount), \
sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
growArray(pointer, sizeof(type) * (oldCount), 0)

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;

    chunk->constants = NULL;
    chunk->constantsCount = 0;
    chunk->constantsCapacity = 0;
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    FREE_ARRAY(Value, chunk->constants, chunk->constantsCapacity);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
    if (chunk->constantsCapacity < chunk->constantsCount + 1) {
        int oldCapacity = chunk->constantsCapacity;
        chunk->constantsCapacity = GROW_CAPACITY(oldCapacity);
        chunk->constants = GROW_ARRAY(Value, chunk->constants,
                                      oldCapacity, chunk->constantsCapacity);
    }

    chunk->constants[chunk->constantsCount] = value;
    chunk->constantsCount++;
    return chunk->constantsCount - 1;
}