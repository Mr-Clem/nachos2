#ifdef CHANGED
#include "pageprovider.h"
#include "synch.h"
#include "bitmap.h"
#include "system.h"

PageProvider::PageProvider(int NbPages) {
  ASSERT(initialized == 0);
  sizeBitMap = NbPages;
  nbPages = new BitMap(NbPages);
  lockPages = new Semaphore("lockPages", 1);
  initialized = 1;
}

PageProvider::~PageProvider(){
  delete nbPages;
  delete lockPages;
}

int PageProvider::GetEmptyPage() {
  lockPages->P();
  int emptyPage = nbPages->Find();
  if (emptyPage != -1) {
    nbPages->Mark(emptyPage);
    bzero(&(machine->mainMemory[emptyPage*PageSize]),PageSize);
  }
  lockPages->V();
  return emptyPage;
}

void PageProvider::ReleasePage(int Page) {
  lockPages->P();
  nbPages->Clear(Page);
  lockPages->V();
}

int PageProvider::NumAvailPage() {
  int numAvailP = nbPages->NumClear();
  return numAvailP;
}

int PageProvider::SizePageProvider() {
  return sizeBitMap;
}

#endif // CHANGED
