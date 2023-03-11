#include "eq_extract.h"

/**
 * @brief Perform `dress` to rename Ntk 1
 *
 * @param pNtk1
 * @param pNtk2
 */
void DressRenameNtk(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2) {
    Abc_Obj_t *pNode;
    int i;

    // Delete all names in Ntk 1.
    Abc_NtkForEachNode(pNtk1, pNode, i)
        Nm_ManDeleteIdName(pNtk1->pManName, pNode->Id);

    Abc_NtkDress2(pNtk1, pNtk2, 1000, 0);
}

/**
 * @brief Main function.
 *
 * @param pNtk1
 * @param pNtk2
 * @return UnEq_SubNtk_t
 */
UnEq_SubNtk_t RunEqExtract(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2) {
    Vec_Ptr_t *vNamedNodes = Vec_PtrAlloc(100);
    Vec_Ptr_t *vCpNodes = Vec_PtrAlloc(100);
    Vec_Ptr_t *vColNodes1 = Vec_PtrAlloc(100);
    Vec_Ptr_t *vColNodes2 = Vec_PtrAlloc(100);

    TraverseNtk1(pNtk1, pNtk2, vNamedNodes, vColNodes1);
    TraverseNtk2(pNtk1, pNtk2, vCpNodes, vColNodes2);

    Abc_Ntk_t *pNtkNew1 = BuildNtk(pNtk1, vNamedNodes, vColNodes1);
    Abc_Ntk_t *pNtkNew2 = BuildNtk(pNtk2, vCpNodes, vColNodes2);

    UnEq_SubNtk_t UnEqSubNtk = {pNtkNew1, pNtkNew2};

    return UnEqSubNtk;
}

/**
 * @brief Build the network based on tranverse information.
 *
 * @param pNtkOld
 * @param vPi
 * @param vNodes
 * @return Abc_Ntk_t*
 */
Abc_Ntk_t *BuildNtk(Abc_Ntk_t *pNtkOld, Vec_Ptr_t *vPi, Vec_Ptr_t *vNodes) {
    Abc_Ntk_t *pNtkNew = Abc_NtkAlloc(ABC_NTK_LOGIC, ABC_FUNC_AIG, 1);

    Abc_Obj_t *pNode;
    int i;

    // Connect Pi to vPi nodes.
    Vec_PtrForEachEntry(Abc_Obj_t *, vPi, pNode, i) {
        Abc_Obj_t *pPi = Abc_NtkCreatePi(pNtkNew);
        Abc_Obj_t *pNodeNew = Abc_NtkDupObj(pNtkNew, pNode, 0);
        Abc_ObjRemoveFanins(pNodeNew);
        Abc_ObjAddFanin(pNodeNew, pPi);
    }

    // Duplicate all nodes.
    Vec_PtrForEachEntryReverse(Abc_Obj_t *, vNodes, pNode, i) {
        // This will set pNode->pCopy to the new DupObj.
        Abc_NtkDupObj(pNtkNew, pNode, 0);

        Abc_Obj_t *pFanin;
        int j;
        Abc_ObjForEachFanin(pNode, pFanin, j)
            Abc_ObjAddFanin(pNode->pCopy, pFanin->pCopy);
    }

    // Connect all PO.
    Abc_Obj_t *pCo;
    Abc_NtkForEachCo(pNtkOld, pCo, i) {
        Abc_NtkDupObj(pNtkNew, pCo, 0);
        Abc_ObjAddFanin(pCo->pCopy, Abc_ObjFanin0(pCo)->pCopy);
    }

    return pNtkNew;
}