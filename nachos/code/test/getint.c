#include "syscall.h"

int main()
{
  int i;
  GetInt(&i);
  PutInt(i);

  return 0;
}
