#ifdef CHANGED
#include "forkexec.h"
#include "system.h"


static void StartForkExec(void *) {
  currentThread->space->InitRegisters ();	// set the initial register values
  currentThread->space->RestoreState ();	// load page table register

  machine->Run();
}

int do_ForkExec(const char* s) {
  OpenFile *executable = fileSystem->Open (s);
  AddrSpace *space;

  if (executable == NULL)
    {
      printf ("Unable to open file %s\n", s);
      return -1;
    }
  space = new AddrSpace (executable);
  if (!space->isUsable()) {
    delete space;
    return -1;
  }
  delete executable;	// close file
  Thread* newThread = new Thread("UserThread 1", -1);
  newThread->space = space;
  newThread->Start(StartForkExec,(void *) NULL);

  return 0;
}

#endif // CHANGED
