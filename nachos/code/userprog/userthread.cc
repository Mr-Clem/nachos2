#ifdef CHANGED
#include "system.h"
#include "userthread.h"
#include "copyright.h"
#include "thread.h"
#include "addrspace.h"

//static Semaphore *threads = new Semaphore("threads", currentThread->space->MAX_THREAD);

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


  machine->WriteRegister(4, arg);
  DEBUG('x', "arg %d, reading register 4 : %d", arg, machine->ReadRegister(4));
  machine->WriteRegister (PCReg, f);
  DEBUG('x', "f: %d, reading register: %d", f, machine->ReadRegister(PCReg));
  machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
  DEBUG('x', "reading PCReg+4: %d, reading NextPCReg: %d", machine->ReadRegister(PCReg) + 4, machine->ReadRegister(NextPCReg));
  int stackTop = currentThread->space->AllocateUserStack(currentThread->space->nb_thread);
  machine->WriteRegister(StackReg, stackTop);
  DEBUG('x', "stacktop: %d, reading StackReg: %d", stackTop, machine->ReadRegister(StackReg));
  machine->Run();
}

int do_ThreadCreate(int f, int arg){

  if(currentThread->space->nb_thread>=currentThread->space->MAX_THREAD){
    return -1;
  }

  currentThread->space->nb_thread++;

  Thread* newThread = new Thread("newThread");
  DEBUG('w', "création\n");
  int* schmurtz = new int[2];
  schmurtz[0]=f;
  schmurtz[1]=arg;
  DEBUG('x',"f vaut: %d\narg vaut: %d\n", schmurtz[0], schmurtz[1]);
  newThread->Start(StartUserThread, schmurtz);

  return 0;
}

void do_ThreadExit(){
  DEBUG('w', "namyst <3");
  if(currentThread->space->nb_thread>0){

    currentThread->space->nb_thread --;
    DEBUG('w', "destruction\n");
  }else{
    DEBUG('w', "au revoir ta mere la guermouche");
    interrupt->Halt();
  }
  currentThread->Finish();
}

#endif //CHANGED
