#include "syscall.h"

void print(void* x)
{
  char* c = (char*) x;
  PutChar(*c);
  PutChar('\n');
  ThreadExit();
}

int  main() {
    char c = 'b';
    char* k;
    ThreadCreate(print,&c);
    GetChar(k); //necessaire pour attendre que StartUserThread excute la fonction print
    return 0;
}
