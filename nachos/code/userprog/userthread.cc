#ifdef CHANGED
#include "system.h"
#include "userthread.h"
#include "copyright.h"
#include "synch.h"

Lock* m_t = new Lock("m_t");

static void StartUserThread(void *schmurtz){
  DEBUG('x', "startuserthread\n");
  if(schmurtz==NULL)
    return;

  DEBUG('x', "Qu'y a t il dans schmurtz?\n réponse:%d\n", schmurtz);

  int* t = (int *) schmurtz;
  int f = t[0];
  int arg = t[1];

  for (int i = 0; i < NumTotalRegs; i++)
    machine->WriteRegister (i, 0);

  machine->WriteRegister (PCReg, f);
  DEBUG('x', "\nf: %d, reading register: %d\n", f, machine->ReadRegister(PCReg));
  machine->WriteRegister(4, arg);
  DEBUG('x', "arg %d, reading register 4 : %d\n", arg, machine->ReadRegister(4));
  machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
  DEBUG('x', "reading PCReg+4: %d, reading NextPCReg: %d\n", machine->ReadRegister(PCReg) + 4, machine->ReadRegister(NextPCReg));

  DEBUG('x', "nb_thread %d\n", currentThread->space->nb_thread);
  
  int stackTop = -1;
  int placeInBitMap;
  int* tab;
  while(stackTop ==-1){
    tab = currentThread->space->AllocateUserStack();
    placeInBitMap = tab[0];
    stackTop = tab[1];
  }
  machine->WriteRegister(StackReg, stackTop);
  DEBUG('x', "stacktop: %d, reading StackReg: %d\n\n", stackTop, machine->ReadRegister(StackReg));
  
  machine->Run();
}

int do_ThreadCreate(int f, int arg){
  
  if(currentThread->space->nb_thread>=currentThread->space->MAX_THREAD){
    return -1;
  }
  m_t->Acquire();
  currentThread->space->nb_thread++;
  m_t->Release();
  Thread* newThread = new Thread("newThread");
  DEBUG('w', "création\n");
  int* schmurtz = new int[2];
  schmurtz[0]=f;
  schmurtz[1]=arg;
  DEBUG('x',"f vaut: %d\narg vaut: %d\n", schmurtz[0], schmurtz[1]);
  DEBUG('x', "Qu'y a t il dans schmurtz?\n réponse:%d\n", schmurtz);
  newThread->Start(StartUserThread, schmurtz);
  return 0;
}

void do_ThreadExit(){
  m_t->Acquire();
  currentThread->space->nb_thread --;
  m_t->Release();
  if(currentThread->space->nb_thread==0)
    interrupt->Halt();
  currentThread->Finish();
}

#endif //CHANGED
