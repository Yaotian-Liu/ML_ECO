#include "eq_extract.h"

int main(int argc, char **argv) {
    Abc_Start();

    char tri[] = "../mytb/tri.v";
    char tri_m[] = "../mytb/tri_modified.v";

    Abc_Ntk_t *pTri = Io_Read(tri, IO_FILE_VERILOG, 1, 0);
    Abc_Ntk_t *pTriM = Io_Read(tri_m, IO_FILE_VERILOG, 1, 0);

    UnEq_SubNtk_t UnEqSubNtk = RunEqExtract(pTri, pTriM);

    WriteVerilog(UnEqSubNtk.pSubNtk1, "sub1.v");
    WriteVerilog(UnEqSubNtk.pSubNtk2, "sub2.v");

    return 0;
}