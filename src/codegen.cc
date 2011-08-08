/* File: codegen.cc
 * ----------------
 * Implementation for the CodeGenerator class. The methods don't do anything
 * too fancy, mostly just create objects of the various Tac instruction
 * classes and append them to the list.
 */

#include <config.h>
#include <string.h>
#include "codegen.h"
#include <arch.h>
#include <tac.h>

#ifdef __TARGET_X86
# include <x86.h>
#endif
#ifdef __TARGET_MIPS
# include <mips.h>
#endif
  
CodeGenerator::CodeGenerator()
{
  code = new List<Instruction*>();
}

char *CodeGenerator::NewLabel()
{
  static int nextLabelNum = 0;
  char temp[10];
  sprintf(temp, "_L%d", nextLabelNum++);
  return strdup(temp);
}


Location *CodeGenerator::GenTempVar(FrameAllocator *falloc)
{
  static int nextTempNum;
  char temp[10];
  Location *result = NULL;
  sprintf(temp, "_tmp%d", nextTempNum++);

  result = falloc->Alloc(temp, VarSize);

  Assert(result != NULL);
  return result;
}

 
Location *CodeGenerator::GenLoadConstant(FrameAllocator *falloc, int value)
{
  Location *result = GenTempVar(falloc);
  code->Append(new LoadConstant(result, value));
  return result;
}

Location *CodeGenerator::GenLoadConstant(FrameAllocator *falloc, const char *s)
{
  Location *result = GenTempVar(falloc);
  code->Append(new LoadStringConstant(result, s));
  return result;
} 

Location *CodeGenerator::GenLoadLabel(FrameAllocator *falloc, const char *label)
{
  Location *result = GenTempVar(falloc);
  code->Append(new LoadLabel(result, label));
  return result;
} 


void CodeGenerator::GenAssign(Location *dst, Location *src)
{
  code->Append(new Assign(dst, src));
}


Location *CodeGenerator::GenLoad(FrameAllocator *falloc, Location *ref, int offset)
{
  Location *result = GenTempVar(falloc);
  code->Append(new Load(result, ref, offset));
  return result;
}

void CodeGenerator::GenStore(Location *dst, Location *src, int offset)
{
  code->Append(new Store(dst, src, offset));
}


Location *CodeGenerator::GenBinaryOp(FrameAllocator *falloc,
                                     const char *opName, Location *op1,
                                     Location *op2)
{
  Location *result = GenTempVar(falloc);
  code->Append(new BinaryOp(BinaryOp::OpCodeForName(opName), result, op1, op2));
  return result;
}


void CodeGenerator::GenLabel(const char *label)
{
  code->Append(new Label(label));
}

void CodeGenerator::GenIfZ(Location *test, const char *label)
{
  code->Append(new IfZ(test, label));
}

void CodeGenerator::GenGoto(const char *label)
{
  code->Append(new Goto(label));
}

void CodeGenerator::GenReturn(Location *val)
{
  code->Append(new Return(val));
}


BeginFunc *CodeGenerator::GenBeginFunc()
{
  BeginFunc *result = new BeginFunc;
  code->Append(result);
  return result;
}

void CodeGenerator::GenEndFunc()
{
  code->Append(new EndFunc());
}

void CodeGenerator::GenPushParam(Location *param)
{
  code->Append(new PushParam(param));
}

void CodeGenerator::GenPopParams(int numBytesOfParams)
{
  Assert(numBytesOfParams >= 0 && numBytesOfParams % VarSize == 0); // sanity check
  if (numBytesOfParams > 0)
    code->Append(new PopParams(numBytesOfParams));
}

Location *CodeGenerator::GenLCall(FrameAllocator *falloc, const char *label,
                                  bool fnHasReturnValue)
{
  Location *result = fnHasReturnValue ? GenTempVar(falloc) : NULL;
  code->Append(new LCall(label, result));
  return result;
}

Location *CodeGenerator::GenACall(FrameAllocator *falloc, Location *fnAddr,
                                  bool fnHasReturnValue)
{
  Location *result = fnHasReturnValue ? GenTempVar(falloc) : NULL;
  code->Append(new ACall(fnAddr, result));
  return result;
}
 
 
static struct _builtin
{
  const char *label;
  int numArgs;
  bool hasReturn;
} builtins[] = {
    { "_Alloc",       1, true  },
    { "_ReadLine",    0, true  },
    { "_ReadInteger", 0, true  },
    { "_StringEqual", 2, true  },
    { "_PrintInt",    1, false },
    { "_PrintString", 1, false },
    { "_PrintBool",   1, false },
    { "_Halt",        0, false }
};

Location *CodeGenerator::GenBuiltInCall(FrameAllocator *falloc, BuiltIn bn,
                                        Location *arg1, Location *arg2)
{
  Assert(bn >= 0 && bn < NumBuiltIns);
  struct _builtin *b = &builtins[bn];
  Location *result = NULL;

  // verify appropriate number of non-NULL arguments given
  if (b->hasReturn)
    result = GenTempVar(falloc);

  Assert((b->numArgs == 0 && !arg1 && !arg2)
	|| (b->numArgs == 1 && arg1 && !arg2)
	|| (b->numArgs == 2 && arg1 && arg2));

  if (arg2)
    code->Append(new PushParam(arg2));

  if (arg1)
    code->Append(new PushParam(arg1));

  code->Append(new LCall(b->label, result));
  GenPopParams(VarSize*b->numArgs);

  return result;
}


void CodeGenerator::GenVTable(const char *className,
                              List<const char *> *methodLabels)
{
  code->Append(new VTable(className, methodLabels));
}


void CodeGenerator::DoFinalCodeGen()
{
  // if debug don't translate to mips, just print Tac
  if (IsDebugOn("tac"))
    {
      for (int i = 0; i < code->NumElements(); i++)
	code->Nth(i)->Print();
    }
  else
    {
#ifdef __TARGET_X86
      X86 x86;
      x86.EmitPreamble();
      for (int i = 0; i < code->NumElements(); i++)
        code->Nth(i)->Emit(&x86);
#endif

#ifdef __TARGET_MIPS

      Mips mips;
      mips.EmitPreamble();
      for (int i = 0; i < code->NumElements(); i++)
        code->Nth(i)->Emit(&mips);
#endif
    }
}


