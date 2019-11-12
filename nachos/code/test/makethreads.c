#include "syscall.h"

volatile int i = 50;


void print(void* x)
{
  char* c = (char*) x;
  PutString(c);
  PutChar('\n');
  ThreadExit();
}

int  main() {
    char* c = "b";
    int z=0;
    for(z;z<i;z++){
      ThreadCreate(print,c);
    }
    PutString("Petit test\n");
    ThreadExit();
    return 0;
}
