// addrspace.h
//      Data structures to keep track of executing user programs
//      (address spaces).
//
//      For now, we don't keep any information about address spaces.
//      The user level CPU state is saved and restored in the thread
//      executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"
#include "translate.h"
#include "noff.h"
#include "list.h"
#include "bitmap.h"

#ifdef CHANGED
#define UserStacksAreaSize		4096	// increase this as necessary!
class BitMap;


#endif//CHANGED
class AddrSpace:dontcopythis
{
public:
#ifdef CHANGED
int MAX_THREAD = (UserStacksAreaSize/256);
int nb_thread = 1;
int actual_Thread;
#endif //CHANGED
AddrSpace (OpenFile * executable);	// Create an address space,
// initializing it with the program
// stored in the file "executable"
~AddrSpace ();		// De-allocate an address space

void InitRegisters ();	// Initialize user-level CPU registers,
// before jumping to user code

void SaveState ();		// Save/restore address space-specific
void RestoreState ();	// info on a context switch

unsigned Dump(FILE *output, unsigned virtual_x, unsigned virtual_width,
		unsigned physical_x, unsigned virtual_y, unsigned y,
		unsigned blocksize);
// Dump program layout as SVG
unsigned NumPages() { return numPages; }
#ifdef CHANGED
int AllocateUserStack(int NOT);
BitMap* threadTable;

#endif //CHANGED
private:
NoffHeader noffH;		// Program layout

TranslationEntry * pageTable; // Page table
unsigned int numPages;	// Number of pages in the page table
};

extern List AddrspaceList;

#endif // ADDRSPACE_H
