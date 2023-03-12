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
    // Run `dress`.
    DressRenameNtk(pNtk1, pNtk2);

    Vec_Ptr_t *vNamedNodes = Vec_PtrAlloc(100);
    Vec_Ptr_t *vCorrNodes = Vec_PtrAlloc(100);
    Vec_Ptr_t *vColNodes1 = Vec_PtrAlloc(100);
    Vec_Ptr_t *vColNodes2 = Vec_PtrAlloc(100);

    TraverseNtk1(pNtk1, pNtk2, vNamedNodes, vColNodes1);
    TraverseNtk2(pNtk1, pNtk2, vCorrNodes, vColNodes2);

    Abc_Ntk_t *pNtkNew1 = BuildNtk("NtkNew1", pNtk1, vNamedNodes, vColNodes1);
    Abc_Ntk_t *pNtkNew2 = BuildNtk("NtkNew2", pNtk2, vCorrNodes, vColNodes2);

    UnEq_SubNtk_t UnEqSubNtk = {pNtkNew1, pNtkNew2};

    Vec_PtrFree(vNamedNodes);
    Vec_PtrFree(vCorrNodes);
    Vec_PtrFree(vColNodes1);
    Vec_PtrFree(vColNodes2);

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
Abc_Ntk_t *BuildNtk(char *NtkName, Abc_Ntk_t *pNtkOld, Vec_Ptr_t *vPi,
                    Vec_Ptr_t *vNodes) {
    Abc_Ntk_t *pNtkNew = Abc_NtkAlloc(ABC_NTK_LOGIC, ABC_FUNC_AIG, 1);
    pNtkNew->pName = Extra_UtilStrsav(NtkName);

    Abc_Obj_t *pNode;
    int i;

    // Create Pis
    Vec_PtrForEachEntry(Abc_Obj_t *, vPi, pNode, i) {
        Abc_Obj_t *pPi = Abc_NtkCreatePi(pNtkNew);
        Abc_ObjAssignName(pPi, Abc_ObjName(pNode), NULL);
        pNode->pCopy = pPi;
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
        Abc_ObjAssignName(pCo->pCopy, Abc_ObjName(pCo), "_po");
        Abc_ObjAddFanin(pCo->pCopy, Abc_ObjFanin0(pCo)->pCopy);
    }

    if (!Abc_NtkCheck(pNtkNew))
        printf("BuildNtk(): Network check has failed.\n");

    return pNtkNew;
}