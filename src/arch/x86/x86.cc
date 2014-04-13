
#include <stdarg.h>
#include <string.h>
#include "x86.h"


/* Method: GetRegister
 * -------------------
 * Given a location for a current var, a reason (ForRead or ForWrite)
 * and up to two registers to avoid, this method will assign
 * to a var to register trying these alternatives in order:
 *  1) if that var is already in a register ("same" is determined
 *     by matching name and same scope), we use that one
 *  2) find an empty register to use for the var
 *  3) find an in-use register that is not dirty.  We don't need
 *     to write value back to memory since it's clean, so we just
 *     replace with the new var
 *  4) spill an in-use, dirty register, by writing its contents to
 *     memory and then replace with the new var
 * For steps 3 & 4, we respect the registers given to avoid (ie the
 * other operands in this operation). The register descriptors are
 * updated to show the new state of the world. If for read, we
 * load the current value from memory into the register. If for
 * write, we mark the register as dirty (since it is getting a
 * new value).
 */
X86::Register X86::GetRegister(Location *var, Reason reason,
                               Register avoid1, Register avoid2)
{
  Register reg;

    return reg;
}

// Two covers for the above method to make it slightly more
// convenient to call it
X86::Register X86::GetRegister(Location *var, Register avoid1)
{
  Register reg;

    return reg;
}

X86::Register X86::GetRegisterForWrite(Location *var, Register avoid1,
                                                     Register avoid2)
{
  Register reg;

    return reg;
}

// Helper to check if two variable locations are one and the same
// (same name, segment, and offset)
static bool LocationsAreSame(Location *var1, Location *var2)
{
  return true;
}

/* Method: FindRegisterWithContents
 * --------------------------------
 * Searches the descriptors for one with contents var. Assigns
 * register by reference, and returns true/false on whether match found.
 */
bool X86::FindRegisterWithContents(Location *var, Register& reg)
{
  return true;
}

/* Method: SelectRegisterToSpill
 * -----------------------------
 * Chooses an in-use register to replace with a new variable. We
 * prefer to replace a non-dirty once since we would not have to
 * write its contents back to memory, so the first loop searches
 * for a clean one. If none found, we take a dirty one.  In both
 * loops we deliberately won't choose either of the registers we
 * were asked to avoid.  We track the last dirty register spilled
 * and advance on each subsequent spill as a primitive means of
 * trying to not throw out things we just loaded and thus are likely
 * to need.
 */
X86::Register X86::SelectRegisterToSpill(Register avoid1, Register avoid2)
{
  Register reg;

  return reg;
}

/* Method: SpillRegister
 * ---------------------
 * "Empties" register.  If variable is currently slaved in this register
 * and its contents are out of synch with memory (isDirty), we write back
 * the current contents to memory. We then clear the descriptor so we
 * realize the register is empty.
 */
void X86::SpillRegister(Register reg)
{

}

/* Method: SpillAllDirtyRegisters
 * ------------------------------
 * Used before flow of control change (branch, label, jump, etc.) to
 * save contents of all dirty registers. This synchs the contents of
 * the registers with the memory locations for the variables.
 */
void X86::SpillAllDirtyRegisters()
{

}

/* Method: SpillForEndFunction
 * ---------------------------
 * Slight optimization on the above method used when spilling for
 * end of function (return/fall off). In such a case, we do not
 * need to save values for locals, temps, and parameters because the
 * function is about to exit and those variables are going away
 * immediately, so no need to bother with updating contents.
 */
void X86::SpillForEndFunction()
{

}

/* Method: Emit
 * ------------
 * General purpose helper used to emit assembly instructions in
 * a reasonable tidy manner.  Takes printf-style formatting strings
 * and variable arguments.
 */
void X86::Emit(const char *fmt, ...)
{

}

/* Method: EmitLoadConstant
 * ------------------------
 * Used to assign variable an integer constant value.  Slaves dst into
 * a register (using GetRegister above) and then emits an li (load
 * immediate) instruction with the constant value.
 */
void X86::EmitLoadConstant(Location *dst, int val)
{

}

/* Method: EmitLoadStringConstant
 * ------------------------------
 * Used to assign a variable a pointer to string constant. Emits
 * assembly directives to create a new null-terminated string in the
 * data segment and assigns it a unique label. Slaves dst into a register
 * and loads that label address into the register.
 */
void X86::EmitLoadStringConstant(Location *dst, const char *str)
{

}

/* Method: EmitLoadLabel
 * ---------------------
 * Used to load a label (ie address in text/data segment) into a variable.
 * Slaves dst into a register and emits an la (load address) instruction
 */
void X86::EmitLoadLabel(Location *dst, const char *label)
{

}

/* Method: EmitCopy
 * ----------------
 * Used to copy the value of one variable to another.  Slaves both
 * src and dst into registers and then emits a move instruction to
 * copy the contents from src to dst.
 */
void X86::EmitCopy(Location *dst, Location *src)
{

}

/* Method: EmitLoad
 * ----------------
 * Used to assign dst the contents of memory at the address in reference,
 * potentially with some positive/negative offset (defaults to 0).
 * Slaves both ref and dst to registers, then emits a lw instruction
 * using constant-offset addressing mode y(rx) which accesses the address
 * at an offset of y bytes from the address currently contained in rx.
 */
void X86::EmitLoad(Location *dst, Location *reference, int offset)
{

}

/* Method: EmitStore
 * -----------------
 * Used to write value to  memory at the address in reference,
 * potentially with some positive/negative offset (defaults to 0).
 * Slaves both ref and dst to registers, then emits a sw instruction
 * using constant-offset addressing mode y(rx) which writes to the address
 * at an offset of y bytes from the address currently contained in rx.
 */
void X86::EmitStore(Location *reference, Location *value, int offset)
{

}

/* Method: EmitBinaryOp
 * --------------------
 * Used to perform a binary operation on 2 operands and store result
 * in dst. All binary forms for arithmetic, logical, relational, equality
 * use this method. Slaves both operands and dst to registers, then
 * emits the appropriate instruction by looking up the mips name
 * for the particular op code.
 */
void X86::EmitBinaryOp(BinaryOp::OpCode code, Location *dst,
                                 Location *op1, Location *op2)
{

}

/* Method: EmitLabel
 * -----------------
 * Used to emit label marker. Before a label, we spill all registers since
 * we can't be sure what the situation upon arriving at this label (ie
 * starts new basic block), and rather than try to be clever, we just
 * wipe the slate clean.
 */
void X86::EmitLabel(const char *label)
{

}

/* Method: EmitGoto
 * ----------------
 * Used for an unconditional transfer to a named label. Before a goto,
 * we spill all registers, since we don't know what the situation is
 * we are heading to (ie this ends current basic block) and rather than
 * try to be clever, we just wipe slate clean.
 */
void X86::EmitGoto(const char *label)
{

}

/* Method: EmitIfZ
 * ---------------
 * Used for a conditional branch based on value of test variable.
 * We slave test var to register and use in the emitted test instruction,
 * either beqz. See comments above on Goto for why we spill
 * all registers here.
 */
void X86::EmitIfZ(Location *test, const char *label)
{

}

/* Method: EmitParam
 * -----------------
 * Used to push a parameter on the stack in anticipation of upcoming
 * function call. Decrements the stack pointer by 4. Slaves argument into
 * register and then stores contents to location just made at end of
 * stack.
 */
void X86::EmitParam(Location *arg)
{

}

/* Method: EmitCallInstr
 * ---------------------
 * Used to effect a function call. All necessary arguments should have
 * already been pushed on the stack, this is the last step that
 * transfers control from caller to callee.  See comments on Goto method
 * above for why we spill all registers before making the jump. We issue
 * jal for a label, a jalr if address in register. Both will save the
 * return address in $ra. If there is an expected result passed, we slave
 * the var to a register and copy function return value from $v0 into that
 * register.
 */
void X86::EmitCallInstr(Location *result, const char *fn, bool isLabel)
{

}

// Two covers for the above method for specific LCall/ACall variants
void X86::EmitLCall(Location *dst, const char *label)
{

}

void X86::EmitACall(Location *dst, Location *fn)
{

}

/*
 * We remove all parameters from the stack after a completed call
 * by adjusting the stack pointer upwards.
 */
void X86::EmitPopParams(int bytes)
{

}

/* Method: EmitReturn
 * ------------------
 * Used to emit code for returning from a function (either from an
 * explicit return or falling off the end of the function body).
 * If there is an expression to return, we slave that variable into
 * a register and move its contents to $v0 (the standard register for
 * function result).  Before exiting, we spill dirty registers (to
 * commit contents of slaved registers to memory, necessary for
 * consistency, see comments at SpillForEndFunction above). We also
 * do the last part of the callee's job in function call protocol,
 * which is to remove our locals/temps from the stack, remove
 * saved registers ($fp and $ra) and restore previous values of
 * $fp and $ra so everything is returned to the state we entered.
 * We then emit jr to jump to the saved $ra.
 */
void X86::EmitReturn(Location *returnVal)
{

}

/* Method: EmitBeginFunction
 * -------------------------
 * Used to handle the callee's part of the function call protocol
 * upon entering a new function. We decrement the $sp to make space
 * and then save the current values of $fp and $ra (since we are
 * going to change them), then set up the $fp and bump the $sp down
 * to make space for all our locals/temps.
 */
void X86::EmitBeginFunction(int stackFrameSize)
{

}

/* Method: EmitEndFunction
 * -----------------------
 * Used to end the body of a function. Does an implicit return in fall off
 * case to clean up stack frame, return to caller etc. See comments on
 * EmitReturn above.
 */
void X86::EmitEndFunction()
{

}

/* Method: EmitVTable
 * ------------------
 * Used to layout a vtable. Uses assembly directives to set up new
 * entry in data segment, emits label, and lays out the function
 * labels one after another.
 */
void X86::EmitVTable(const char *label, List<const char*> *methodLabels)
{


}

/* Method: EmitPreamble
 * --------------------
 * Used to emit the starting sequence needed for a program. Not much
 * here, but need to indicate what follows is in text segment and
 * needs to be aligned on word boundary. main is our only global symbol.
 */
void X86::EmitPreamble()
{

}

/* Method: NameForTac
 * ------------------
 * Returns the appropriate MIPS instruction (add, seq, etc.) for
 * a given BinaryOp:OpCode (BinaryOp::Add, BinaryOp:Equals, etc.).
 * Asserts if asked for name of an unset/out of bounds code.
 */
const char *X86::NameForTac(BinaryOp::OpCode code)
{

}

/* Constructor
 * ----------
 * Constructor sets up the mips names and register descriptors to
 * the initial starting state.
 */
X86::X86()
{
  x86Name[BinaryOp::Add]  = "add";
  x86Name[BinaryOp::Sub]  = "sub";
  x86Name[BinaryOp::Mul]  = "imul";
  x86Name[BinaryOp::Div]  = "idiv";
  x86Name[BinaryOp::Mod]  = "";
  x86Name[BinaryOp::Eq]   = "";
  x86Name[BinaryOp::Less] = "";
  x86Name[BinaryOp::And]  = "";
  x86Name[BinaryOp::Or]   = "";
  x86Name[BinaryOp::Xor]  = "";
  x86Name[BinaryOp::Shl]  = "";
  x86Name[BinaryOp::Shr]  = "";
  regs[eax]    = (RegContents) { false, NULL, "%eax",    true };
  regs[ebx]    = (RegContents) { false, NULL, "%ebx",    true };
  regs[ecx]    = (RegContents) { false, NULL, "%ecx",    true };
  regs[edx]    = (RegContents) { false, NULL, "%edx",    true };
  regs[cs]     = (RegContents) { false, NULL, "%cs",     false };
  regs[ds]     = (RegContents) { false, NULL, "%ds",     false };
  regs[ss]     = (RegContents) { false, NULL, "%ss",     false };
  regs[es]     = (RegContents) { false, NULL, "%es",     false };
  regs[fs]     = (RegContents) { false, NULL, "%fs",     false };
  regs[gs]     = (RegContents) { false, NULL, "%gs",     false };
  regs[ebp]    = (RegContents) { false, NULL, "%ebp",    false };
  regs[esp]    = (RegContents) { false, NULL, "%esp",    false };
  regs[esi]    = (RegContents) { false, NULL, "%esi",    false };
  regs[edi]    = (RegContents) { false, NULL, "%edi",    false };
  regs[eip]    = (RegContents) { false, NULL, "%eip",    false };
  regs[eflags] = (RegContents) { false, NULL, "%eflags", false };
  lastUsed = eax;
}

const char *X86::x86Name[BinaryOp::NumOps];
