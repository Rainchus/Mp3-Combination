#ifndef __PROCESS_H
#define __PROCESS_H

#include "ultra64.h"

typedef struct jump_buf
{
    u32* sp;
    void *func;
    u32 regs[21];
} jmp_buf;

extern s32 setjmp(jmp_buf *jump_buf);
extern s32 longjmp(jmp_buf *jump_buf, s32 val);

#define EXEC_PROCESS_DEFAULT 0
#define EXEC_PROCESS_SLEEPING 1
#define EXEC_PROCESS_WATCH 2
#define EXEC_PROCESS_DEAD 3

typedef void (*process_func)();

typedef struct mp3_Process {
/* 0x00 */ struct mp3_Process *next;
/* 0x04 */ struct mp3_Process *youngest_child;
/* 0x08 */ struct mp3_Process *oldest_child;
/* 0x0C */ struct mp3_Process *relative;
/* 0x10 */ struct mp3_Process *parent_oldest_child;
/* 0x14 */ struct mp3_Process *new_process;
/* 0x18 */ void *heap;
/* 0x1C */ u16 exec_mode;
/* 0x1E */ u16 stat;
/* 0x20 */ u16 priority;
/* 0x22 */ s16 dtor_idx;
/* 0x24 */ s32 sleep_time;
/* 0x28 */ void *base_sp;
/* 0x2C */ jmp_buf prc_jump;
/* 0x88 */ process_func destructor;
/* 0x8C */ void *user_data;
} mp3_Process;

void HuPrcSysInit();
void HuPrcLink(mp3_Process**root, mp3_Process*process);
void HuPrcUnlink(mp3_Process**root, mp3_Process*process);
mp3_Process* HuPrcCreate(process_func func, u16 priority, s32 stack_size, s32 extra_data_size);
void HuPrcChildLink(mp3_Process*process, mp3_Process*child);
void HuPrcChildUnlink(mp3_Process*process);
mp3_Process* HuPrcCreateChild(process_func func, u16 priority, s32 stack_size, s32 extra_data_size, mp3_Process* parent);
void HuPrcChildWait();
mp3_Process* mp3_HuPrcCurrentGet();
s32 HuPrcChildGet(mp3_Process*process);
s32 HuPrcStatKill(mp3_Process*process);
void HuPrcKill(mp3_Process*process);
void HuPrcChildKill(mp3_Process*process);
void HuPrcTerminate(mp3_Process*process);
void HuPrcExit();
void HuPrcSleep(s32 time);
void mp3_HuPrcVSleep();
void HuPrcAwake(mp3_Process*process);
void HuPrcDtor(mp3_Process*process, process_func destructor);
void HuPrcCurrentDtor(process_func destructor);
void* HuPrcAllocMem(s32 size);
void HuPrcFreeMem(void *ptr);

#endif