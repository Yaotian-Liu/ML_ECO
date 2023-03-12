#include "eq_extract.h"

int main(int argc, char **argv) {
    Abc_Start();

    char tri[] = "../mytb/tri.v";
    char tri_m[] = "../mytb/tri_modified.v";

    Abc_Ntk_t *pTri = Io_Read(tri, IO_FILE_VERILOG, 1, 0);
    Abc_Ntk_t *pTriM = Io_Read(tri_m, IO_FILE_VERILOG, 1, 0);

    // PrintAllObj(pTri, 1);

    // printf("For %s: \n", tri_m);
    // PrintAllObj(pTriM, 1);

    UnEq_SubNtk_t UnEqSubNtk = RunEqExtract(pTri, pTriM);

    printf("OUT: \n");
    PrintAllObj(UnEqSubNtk.pSubNtk1, 1);

    Abc_Ntk_t *pOut = Abc_NtkToNetlist(UnEqSubNtk.pSubNtk1);
    printf("Netlist: \n");
    PrintAllObj(pOut, 1);

    Io_WriteVerilog(pOut, "out.v", 0);

    return 0;
}