#ifndef ABC_EXT__H
#define ABC_EXT__H

#include "base/main/main.h"
#include "base/main/mainInt.h"
// #include "base/wlc/wlc.h"
// #include "base/wln/wln.h"
#include "misc/nm/nmInt.h"
#include "sat/bsat/satSolver.h"
#include "sat/cnf/cnf.h"

extern void Abc_NtkDress2(Abc_Ntk_t* pNtk1, Abc_Ntk_t* pNtk2,
                          int nConflictLimit, int fVerbose);
extern Vec_Ptr_t* Abc_NtkDressComputeEquivs(Abc_Ntk_t* pNtk1, Abc_Ntk_t* pNtk2,
                                            int nConflictLimit, int fVerbose);

extern void Abc_NtkDressPrintStats(Vec_Ptr_t* vRes, int nNodes0, int nNodes1,
                                   abctime Time);

extern void Abc_NtkDress2Transfer(Abc_Ntk_t* pNtk0, Abc_Ntk_t* pNtk1,
                                  Vec_Ptr_t* vRes, int fVerbose);

#endif