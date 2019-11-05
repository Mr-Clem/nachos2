#include "syscall.h"

void print(void* x)
{
    char* c = (char*) x;
  PutChar(*c);
  PutChar('\n');
  ThreadExit();
}

void  main() {
    char c = 'b';
    char* k;
    ThreadCreate(print,&c);
    GetChar(k);
    //return 0;
}
