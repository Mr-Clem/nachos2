#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

#include "copyright.h"
#include "addrspace.h"
#include "thread.h"
#include "bitmap.h"

extern int do_ThreadCreate(int f, int arg);

extern void do_ThreadExit();

#endif //USERTHREAD_H
#endif //CHANGED
