#ifdef CHANGED
#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"
#include "synch.h"

class PageProvider:dontcopythis {
  public:
    PageProvider(int nbPages);
    ~PageProvider();
    int GetEmptyPage();
    void ReleasePage(int Page);
    int NumAvailPage();
    int SizePageProvider();
  private:
    BitMap* nbPages;
    Semaphore* lockPages;
    int sizeBitMap;
    int initialized = 0;
};

#endif // PAGEPROVIDER
#endif // CHANGED
