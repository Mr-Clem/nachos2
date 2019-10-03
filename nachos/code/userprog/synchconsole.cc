#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvailHandler(void *arg){
  (void) arg; readAvail->V();
}

static void WriteDoneHandler(void *arg){
  (void) arg; writeDone->V();
}

SynchConsole::SynchConsole(const char *in, const char *out)
{
  readAvail = new Semaphore("read avail", 0);
  writeDone = new Semaphore("write done", 0);
  console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, NULL);
}

SynchConsole::~SynchConsole()
{
  delete console;
  delete writeDone;
  delete readAvail;
}

void SynchConsole::SynchPutChar(int ch)
{
  console->PutChar (ch);
  writeDone->P();
}

int SynchConsole::SynchGetChar()
{
  int ch;
  readAvail->P ();
  ch = console->GetChar ();
  return ch;
}

void SynchConsole::SynchPutString(const char s[])
{
    if (s == NULL){
        return;
    }

    int i = 0;
    while(s[i]!='\0'){
        SynchPutChar(s[i]);
        i++;
    }
}

void SynchConsole::SynchGetString(char *s, int n)
{
  // ...
}

#endif // CHANGED
