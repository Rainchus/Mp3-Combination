#ifndef __MALLOC_H
#define __MALLOC_H

#include "ultra64.h"

typedef struct HeapNode {
/* 0x00 */ s32 size;
/* 0x04 */ u8 heap_constant;
/* 0x05 */ u8 active;
/* 0x08 */ struct HeapNode* prev;
/* 0x0C */ struct HeapNode* next;
} HeapNode;

void* mp3_HuMemHeapInit(void *ptr, u32 size);
void* mp3_HuMemMemoryAlloc(HeapNode *heap, s32 size);
void mp3_HuMemMemoryFree(void *ptr);
void* mp3_HuMemMemoryRealloc(HeapNode *heap, void *mem, u32 new_size);
u32 mp3_HuMemUsedMemorySizeGet(HeapNode *heap);
u32 mp3_HuMemUsedMemoryBlockGet(HeapNode *heap);
s32 mp3_HuMemMemoryAllocSizeGet(s32 value);

HeapNode* mp3_HuMemHeapInitPerm(void *ptr, u32 size);
void* mp3_HuMemMemoryAllocPerm(u32 size);
void mp3_HuMemMemoryFreePerm(void *ptr);
void* mp3_HuMemMemoryReallocPerm(void *mem, u32 new_size);
u32 mp3_HuMemHeapAllocPermSizeGet(void);
u32 mp3_HuMemUsedMemoryBlockGetPerm(void);

HeapNode* mp3_HuMemHeapInitTemp(void *ptr, u32 size);
void* mp3_HuMemMemoryAllocTemp(u32 size);
void mp3_HuMemMemoryFreeTemp(void *ptr);
void* mp3_HuMemMemoryReallocTemp(void *mem, u32 new_size);
u32 mp3_HuMemHeapAllocTempSizeGet(void);
u32 mp3_HuMemUsedMemoryBlockGetTemp(void);

#endif