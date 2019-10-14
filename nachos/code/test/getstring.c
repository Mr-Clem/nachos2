
#include "syscall.h"

int main()
{
  char s[16];
  GetString(s,16);
  PutString(s);
  return 0;
}
