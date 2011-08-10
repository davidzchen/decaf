#ifndef _H_X86
#define _H_X86

#include <list.h>
#include "tac.h"

class Location;

class X86
{
  private:
    typedef enum
    {
      eax, ebx, ecx, edx,       // General purpose 32-bit regs
      cs, ds, ss, es, fs, gs,   // Segment registers
      ebp, esp,                 // Stack registers
      esi, edi,                 // Index registers
      eip, eflags,              // Instruction pointer and flags
      NumRegs                   // Total number of usable registers
    } Register;

    struct RegContents
    {
        bool isDirty;
        Location *var;
        const char *name;
        bool isGeneralPurpose;
    } regs[NumRegs];

    Register lastUsed;

    typedef enum { ForRead, ForWrite } Reason;

    Register GetRegister(Location *var, Reason reason,
                         Register avoid1, Register avoid2);
    Register GetRegister(Location *var, Register avoid1);
    Register GetRegisterForWrite(Location *var, Register avoid1,
                                 Register avoid2);
    bool FindRegisterWithContents(Location *var, Register& reg);
    Register SelectRegisterToSpill(Register avoid1, Register avoid2);
    void SpillRegister(Register reg);
    void SpillAllDirtyRegisters();
    void SpillForEndFunction();

    void EmitCallInstr(Location *dst, const char *fn, bool isL);

    static const char *x86Name[BinaryOp::NumOps];
    static const char *NameForTac(BinaryOp::OpCode code);

  public:

    X86();

    static void Emit(const char *fmt, ...);

    void EmitLoadConstant(Location *dst, int val);
    void EmitLoadStringConstant(Location *dst, const char *str);
    void EmitLoadLabel(Location *dst, const char *label);

    void EmitLoad(Location *dst, Location *reference, int offset);
    void EmitStore(Location *reference, Location *value, int offset);
    void EmitCopy(Location *dst, Location *src);

    void EmitBinaryOp(BinaryOp::OpCode code, Location *dst,
                            Location *op1, Location *op2);

    void EmitLabel(const char *label);
    void EmitGoto(const char *label);
    void EmitIfZ(Location *test, const char*label);
    void EmitReturn(Location *returnVal);

    void EmitBeginFunction(int frameSize);
    void EmitEndFunction();

    void EmitParam(Location *arg);
    void EmitLCall(Location *result, const char* label);
    void EmitACall(Location *result, Location *fnAddr);
    void EmitPopParams(int bytes);

    void EmitVTable(const char *label, List<const char*> *methodLabels);

    void EmitPreamble();
};

#endif
