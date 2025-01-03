#include "src/vm.h"

int main()
{
    virtual_machine vm;

    double* arg = new double(1);
    double* arg2 = new double(2);

    string* adr = new string("0x01");

    vector<bytecode_instr> bc = {
        bytecode_instr(aluna_opcode(push), arg),
        bytecode_instr(aluna_opcode(push), arg2),

        bytecode_instr(aluna_opcode(add)),

        bytecode_instr(aluna_opcode(write), adr),

        bytecode_instr(aluna_opcode(read), adr),

        bytecode_instr(aluna_opcode(print)),
    };

    vm.run_bytecode(bc);

    return 0;
}