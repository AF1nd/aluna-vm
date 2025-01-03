#include "vm.h"
#include <iostream>

using namespace std;

void* virtual_machine::rs_pop()
{
    void* top = this->runtime_stack.top();
    if (top)
    {
        this->runtime_stack.pop();
        return top;
    } else this->r_error("cannot pop from empty stack");

    return nullptr;
}

void virtual_machine::rs_push(void* data)
{
    this->runtime_stack.push(data);
}

void virtual_machine::r_error(string text)
{
    throw runtime_error("aluna error: " + text);
}

template<class T>
T* virtual_machine::as(void* data)
{
    T* casted_data = static_cast<T*>(data);
    if (!casted_data) this->r_error("cannot cast data");

    return casted_data;
}

string virtual_machine::to_mnemonic(aluna_opcode opcode)
{
    switch (opcode)
    {
        case push:
            return "push";
        case add:
            return "add";
        case sub:
            return "sub";
        case mul:
            return "mul";
        case divide:
            return "div";
        case read:
            return "read";
        case write:
            return "write";
        case print:
            return "print";
        case hlt:
            return "hlt";                                                                                          
        default:
            break;
    }

    return "unknown";
}

void virtual_machine::run_bytecode(vector<bytecode_instr> bc)
{
    for (bytecode_instr instr: bc)
    {
        string mnemonic = this->to_mnemonic(instr.opcode);
        string arg = instr.argument ? this->to_str(instr.argument) : "";
        
        cout << to_string(instr.opcode) + "      " + mnemonic + "      " + arg << endl;
    }

    cout << "[result]" << endl;

    while (this->ip < bc.size())
    {
        bytecode_instr instr = bc[this->ip];

        switch (instr.opcode)
        {
        case push:
            this->rs_push(instr.argument);
            break;
        case add:
            {           
                double* b = this->as<double>(this->rs_pop());
                double* a = this->as<double>(this->rs_pop());

                double* result = new double(*b + *a);

                this->rs_push(result);
            }
            break;
        case sub:
            {           
                double* b = this->as<double>(this->rs_pop());
                double* a = this->as<double>(this->rs_pop());

                double* result = new double(*b - *a);

                this->rs_push(result);
            }
            break;
        case mul:
            {           
                double* b = this->as<double>(this->rs_pop());
                double* a = this->as<double>(this->rs_pop());

                double* result = new double(*b * *a);

                this->rs_push(result);
            }
            break;
        case divide:
            {
                double* b = this->as<double>(this->rs_pop());
                double* a = this->as<double>(this->rs_pop());

                double* result = new double(*b / *a);

                this->rs_push(result);
            }

            break;
        case write:
            {
                void* data = this->rs_pop();

                string* address = this->as<string>(instr.argument);

                this->memory[*address] = data;
            }

            break;
        case read:
            {
                string* address = this->as<string>(instr.argument);

                this->rs_push(this->memory[*address]);
            }

            break;
        case print:
            {
                void* data = this->rs_pop();

                cout << this->to_str(data) << endl;
            }

            break;
        case hlt:
            return;
        default:
            break;
        }

        this->ip++;
    }
}

string virtual_machine::to_str(void* data)
{
    string* to_print = this->as<string>(data);

    if (to_print->empty())
    {
        double* d = static_cast<double*>(data);
        if (d)
        {
            string str = to_string(*d);
            to_print = &str;
        }
    }

    return *to_print;
}