#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *m_getstring;
static Semaphore *m_putstring;
static Lock *mutex_w;
static Lock *mutex_r;
static Lock *mutex_ws;
static Lock *mutex_rs;


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
  mutex_r = new Lock("mutex_r");
  mutex_w = new Lock("mutex_w");
  mutex_rs = new Lock("mutex_rs");
  mutex_ws = new Lock("mutex_ws");
}

SynchConsole::~SynchConsole()
{
  delete console;
  delete writeDone;
  delete readAvail;
}

void SynchConsole::SynchPutChar(int ch)
{
  mutex_w->Acquire();
  console->PutChar (ch);
  writeDone->P();
  mutex_w->Release();
}

int SynchConsole::SynchGetChar()
{
  int ch;
  readAvail->P ();
  mutex_r->Acquire();
  ch = console->GetChar();
  mutex_r->Release();
  return ch;
}

void SynchConsole::SynchPutString(const char s[])
{
    mutex_ws->Acquire();
    if (s == NULL){
        return;
    }

    int i = 0;
    m_putstring->P();
    while(s[i]!='\0'){
        SynchPutChar(s[i]);
        i++;
    }
    mutex_ws->Release();
}

void SynchConsole::SynchGetString(char *s, int n)
{
  char ch;
  int i=0;
  mutex_rs->Acquire();
  if(s==NULL)
    return;

  m_getstring->P();
  while(i<n-1){
    ch=SynchGetChar();
    if(ch == '\n'){
      s[i]=ch;
      i++;
      break;
    }
    if(ch=='\0'){
      break;
    }
    s[i]=ch;
    i++;
  }
  s[i]='\0';
  mutex_rs->Release();
}

void SynchConsole::SynchPutInt(int n)
{
  int k = 10; //entier codés sur 16 bits donc si on fixe k=10 chiffres pour un nombre n, nous avons suffisemment de marge
  char s[k];
  snprintf(s, k, "%d", n);
  SynchPutString(s);
}

void SynchConsole::SynchGetInt(int* n)
{
  int k=10;
  char s[k];
  SynchGetString(s, k);
  sscanf(s,"%d",n);
}

#endif // CHANGED
