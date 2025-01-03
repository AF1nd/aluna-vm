#pragma once

#include <stack>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

enum aluna_opcode
{
    push = 0b10,

    add = 0b100,
    mul = 0b1000,
    divide = 0b10000,
    sub = 0b100000,

    write = 0b1000000,
    read = 0b10000000,

    print = 0b100000000,
    hlt = 0b10000000000,
};

struct bytecode_instr
{
    void* argument;
    aluna_opcode opcode;

    bytecode_instr(aluna_opcode opcode, void* argument = nullptr)
    {
        this->argument = argument;
        this->opcode = opcode;
    }
};


class virtual_machine 
{
    private:
        stack<void*> runtime_stack;
        map<string, void*> memory;

        void* rs_pop();
        void rs_push(void* data);

        void r_error(string text);

        int ip = 0;

        template<class T>
        T* as(void* data);

        string to_mnemonic(aluna_opcode opcode);
        string to_str(void* data);
    public:
        void run_bytecode(vector<bytecode_instr> bc);
};