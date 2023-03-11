#include "eq_extract.h"

void TraverseNtk1(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2, Vec_Ptr_t *vNamedNodes,
                  Vec_Ptr_t *vColNodes_1) {
    Abc_Obj_t *pNode;
    int i;

    Vec_Ptr_t *vNodes = Abc_NtkDfsIter(pNtk1, 0);
    int lastLevel = -1;
    int fNormalCollect = 1;  // flag for the red loop and green loop
    int fSkip = 0;           // flag for the blue loop

    Vec_PtrForEachEntryReverse(Abc_Obj_t *, vNodes, pNode, i) {
        int nodeLevel = pNode->Level;

        // Blue loop
        if (fSkip) {
            if (nodeLevel < lastLevel)
                continue;
            else {
                // Jump out
                fSkip = 0;
                fNormalCollect = 1;
            }
        }

        // Do not has name
        if (!HasName(pNode, pNtk1)) {
            // Red loop
            if (fNormalCollect) {
                Vec_PtrPush(vColNodes_1, pNode);
                continue;
            } else {
                Vec_PtrPush(vColNodes_1, pNode);
                if (nodeLevel < lastLevel)
                    // Jump out
                    fSkip = 1;
            }
        }

        // Has name
        else {
            // update last named level & collect
            lastLevel = nodeLevel;
            Vec_PtrPush(vNamedNodes, pNode);

            // Set cp of both nodes.
            pNode->pCopy = FindNodeByName(Abc_ObjName(pNode), pNtk2);
            pNode->pCopy->pCopy = pNode;

            fNormalCollect = 0;
        }
    }
}

void TraverseNtk2(Abc_Ntk_t *pNtk1, Abc_Ntk_t *pNtk2, Vec_Ptr_t *vCpNodes,
                  Vec_Ptr_t *vColNodes_2) {
    Abc_Obj_t *pNode;
    int i;

    Vec_Ptr_t *vNodes = Abc_NtkDfsIter(pNtk2, 0);
    int lastLevel = -1;
    int fNormalCollect = 1;  // flag for the red loop and green loop
    int fSkip = 0;           // flag for the blue loop

    Vec_PtrForEachEntryReverse(Abc_Obj_t *, vNodes, pNode, i) {
        int nodeLevel = pNode->Level;

        // Blue loop
        if (fSkip) {
            if (nodeLevel < lastLevel)
                continue;
            else {
                // Jump out
                fSkip = 0;
                fNormalCollect = 1;
            }
        }

        // Do not has cp
        if (!HasCp(pNode)) {
            // Red loop
            if (fNormalCollect) {
                Vec_PtrPush(vColNodes_2, pNode);
                continue;
            } else {
                Vec_PtrPush(vColNodes_2, pNode);
                if (nodeLevel < lastLevel)
                    // Jump out
                    fSkip = 1;
            }
        }

        // Has cp
        else {
            // update last named level & collect
            lastLevel = nodeLevel;
            Vec_PtrPush(vCpNodes, pNode);

            fNormalCollect = 0;
        }
    }
}