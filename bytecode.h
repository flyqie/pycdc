#include "pyc_code.h"
#include "pyc_module.h"
#include "data.h"

namespace Pyc {

enum Opcode {
    #define OPCODE(x) x,
    #define OPCODE_A_FIRST(x) PYC_HAVE_ARG, x##_A = PYC_HAVE_ARG,
    #define OPCODE_A(x) x##_A,
    #include "bytecode_ops.inl"
    #undef OPCODE_A
    #undef OPCODE_A_FIRST
    #undef OPCODE

    PYC_LAST_OPCODE,
    PYC_INVALID_OPCODE = -1,
};

enum DisassemblyFlags {
    DISASM_PYCODE_VERBOSE = 0x1,
    DISASM_SHOW_CACHES = 0x2,
};

const char* OpcodeName(int opcode);
int ByteToOpcode(int maj, int min, int opcode);

bool IsConstArg(int opcode);
bool IsNameArg(int opcode);
bool IsVarNameArg(int opcode);
bool IsCellArg(int opcode);
bool IsJumpOffsetArg(int opcode);
bool IsJumpArg(int opcode);
bool IsCompareArg(int opcode);

}

void print_const(std::ostream& pyc_output, PycRef<PycObject> obj, PycModule* mod,
                 const char* parent_f_string_quote = nullptr);
void bc_next(PycBuffer& source, PycModule* mod, int& opcode, int& operand, int& pos);
void bc_disasm(std::ostream& pyc_output, PycRef<PycCode> code, PycModule* mod,
               int indent, unsigned flags);
