#include "eq_extract.h"

const char *Abc_ObjType_str[] = {"NONE",  "CONST1",   "PI",       "PO",
                                 "BI",    "BO",       "NET",      "NODE",
                                 "LATCH", "WHITEBOX", "BLACKBOX", "NUMBER"};

Abc_Obj_t *FindNodeByName(const char *nodeName, Abc_Ntk_t *pNtk) {
    Abc_Obj_t *pNode;
    int i;

    Abc_NtkForEachNode(pNtk, pNode, i) {
        if (!strcmp(Abc_ObjName(pNode), nodeName))
            return pNode;
    }

    return NULL;
}

int HasName(Abc_Obj_t *pNode, Abc_Ntk_t *pNtk) {
    return Nm_ManTableLookupId(pNtk->pManName, pNode->Id) ? true : false;
}

int HasCorrNode(Abc_Obj_t *pNode) { return pNode->fMarkC ? true : false; }

void PrintAllObj(Abc_Ntk_t *pNtk, int fVerbose) {
    Abc_Obj_t *pObj;
    int i;

    Abc_NtkForEachObj(pNtk, pObj, i) {
        printf("Node: %s, Id: %d, Level: %d, Type: %s. \n", Abc_ObjName(pObj),
               pObj->Id, pObj->Level, Abc_ObjType_str[pObj->Type]);

        if (fVerbose) {
            Abc_Obj_t *pFanin;
            int j;
            printf("\t Fanins: ");
            Abc_ObjForEachFanin(pObj, pFanin, j) { printf("%d, ", pFanin->Id); }
            printf("\n");

            Abc_Obj_t *pFanout;
            int k;
            printf("\t Fanouts: ");
            Abc_ObjForEachFanout(pObj, pFanout, k) {
                printf("%d, ", pFanout->Id);
            }
            printf("\n");
        }
    }
}
