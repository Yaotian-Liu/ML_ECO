#ifndef EQ_EXTRACT__H
#define EQ_EXTRACT__H

#include "abc_ext.h"
#include "stdio.h"

typedef struct UnEq_SubNtk_t_ UnEq_SubNtk_t;

struct UnEq_SubNtk_t_ {
    Abc_Ntk_t *pSubNtk1;
    Abc_Ntk_t *pSubNtk2;
};

// ----- eq_extract.c -----
void DressRenameNtk(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2);

UnEq_SubNtk_t RunEqExtract(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2);
Abc_Ntk_t *BuildNtk(char *NtkName, Abc_Ntk_t *pOldNtk, Vec_Ptr_t *vPi,
                    Vec_Ptr_t *vNodes);

// ----- traverse.c -----
void TraverseNtk1(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2, Vec_Ptr_t *vNamedNodes,
                  Vec_Ptr_t *vColNodes_1);
void TraverseNtk2(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2, Vec_Ptr_t *vCpNodes,
                  Vec_Ptr_t *vColNodes_2);

// ----- utils.c -----
Abc_Obj_t *FindNodeByName(const char *nodeName, Abc_Ntk_t *pNtk);
int HasName(Abc_Obj_t *pNode, Abc_Ntk_t *pNtk);
int HasCp(Abc_Obj_t *pNode);
void PrintAllObj(Abc_Ntk_t *pNtk, int fVerbose);

#endif