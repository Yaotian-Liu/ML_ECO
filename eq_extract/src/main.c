#include "eco.h"

int main(int argc, char **argv) {
    int i, j;
    Abc_Start();
    // Cmd_CommandExecute(Abc_FrameGetGlobalFrame(), "read ../unit1/G.v;
    // print_stats;");
    char F[] = "/home/henry/repos/abc/unit1/F.v";
    char G[] = "/home/henry/repos/abc/mytb/tri.v";

    // char F[] = "/home/henry/repos/abc/ECO_benchmarks/old_verilog/design10.v";
    // char G[] = "/home/henry/repos/abc/ECO_benchmarks/new_verilog/design10.v";

    Abc_Ntk_t *pF = Io_Read(F, IO_FILE_VERILOG, 1, 0);
    Abc_Ntk_t *pG = Io_Read(G, IO_FILE_VERILOG, 1, 0);

    assert(Abc_NtkIsDfsOrdered(pG));

    Vec_Ptr_t *vNodes = Abc_NtkDfsReverse(pG);

    Abc_Obj_t *pNode;
    Vec_PtrForEachEntry(Abc_Obj_t *, vNodes, pNode, i) {
        printf("Name: %s ,\tLevel: %d, \t type: %d \n", Abc_ObjName(pNode), pNode->Level, pNode->Type);
    }

    // printf("Po num: %d \n", Abc_NtkPoNum(pNtk));
    // printf("Po num: %d \n", Abc_NtkCoNum(pNtk));

    return 0;
}