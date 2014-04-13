/* File: codegen.cc
 * ----------------
 * Implementation for the CodeGenerator class. The methods don't do anything
 * too fancy, mostly just create objects of the various Tac instruction
 * classes and append them to the list.
 */

#include <string.h>

#include "codegen/codegen.h"
#include "decaf/errors.h"

#include "arch/mips/tac.h"
#include "arch/mips/mips.h"

CodeGenerator::CodeGenerator() {
  code = new List<Instruction*>();
  mainFound = false;
}

char *CodeGenerator::NewLabel() {
  static int nextLabelNum = 0;
  char temp[10];
  sprintf(temp, "_L%d", nextLabelNum++);
  return strdup(temp);
}

char *CodeGenerator::NewClassLabel(char *className) {
  int len = strlen(className) + 3;
  char *label = (char *) malloc(len);
  if (label == NULL) {
    Failure("CodeGenerator::NewClassLabel(): Malloc out of memory");
  }

  sprintf(label, "C_%s", className);
  return label;
}

char *CodeGenerator::NewFunctionLabel(char *functionName) {
  int len = strlen(functionName) + 3;
  char *label = NULL;
  if (strcmp(functionName, "main") == 0) {
    return functionName;
  }

  label = (char *) malloc(len);
  if (label == NULL) {
    Failure("CodeGenerator::NewFunctionLabel(): Malloc out of memory");
  }
  sprintf(label, "F_%s", functionName);
  return label;
}

Location *CodeGenerator::GenTempVar(FrameAllocator *falloc) {
  static int nextTempNum;
  char temp[10];
  Location *result = NULL;
  sprintf(temp, "_tmp%d", nextTempNum++);
  result = falloc->Alloc(temp, VarSize);
  Assert(result != NULL);
  return result;
}

Location *CodeGenerator::GenLoadConstant(FrameAllocator *falloc, int value) {
  Location *result = GenTempVar(falloc);
  code->Append(new LoadConstant(result, value));
  return result;
}

Location *CodeGenerator::GenLoadConstant(FrameAllocator *falloc,
    const char *s) {
  Location *result = GenTempVar(falloc);
  code->Append(new LoadStringConstant(result, s));
  return result;
}

Location *CodeGenerator::GenLoadLabel(FrameAllocator *falloc,
    const char *label) {
  Location *result = GenTempVar(falloc);
  code->Append(new LoadLabel(result, label));
  return result;
}

void CodeGenerator::GenAssign(Location *dst, Location *src) {
  code->Append(new Assign(dst, src));
}

Location *CodeGenerator::GenLoad(FrameAllocator *falloc, Location *ref,
    int offset) {
  Location *result = GenTempVar(falloc);
  code->Append(new Load(result, ref, offset));
  return result;
}

void CodeGenerator::GenStore(Location *dst, Location *src, int offset) {
  code->Append(new Store(dst, src, offset));
}

Location *CodeGenerator::GenBinaryOp(FrameAllocator *falloc,
    const char *opName, Location *op1, Location *op2) {
  Location *result = NULL;
  if (strcmp(opName, "!=") == 0) {
    // !(op1 == op2)
    Location *eq = GenBinaryOp(falloc, "==", op1, op2);
    result = GenUnaryOp(falloc, "!", eq);
  } else if (strcmp(opName, ">") == 0) {
    // !(op1 < op2) && !(op1 == op2)
    Location *eq = GenBinaryOp(falloc, "==", op1, op2);
    Location *lt = GenBinaryOp(falloc, "<", op1, op2);
    Location *neq = GenUnaryOp(falloc, "!", eq);
    Location *nlt = GenUnaryOp(falloc, "!", lt);
    result = GenBinaryOp(falloc, "&&", neq, nlt);
  } else if (strcmp(opName, "<=") == 0) {
    // (op1 == op2) || (op1 < op2)
    Location *eq = GenBinaryOp(falloc, "==", op1, op2);
    Location *lt = GenBinaryOp(falloc, "<", op1, op2);
    result = GenBinaryOp(falloc, "||", eq, lt);
  } else if (strcmp(opName, ">=") == 0) {
    // !(op1 < op2)
    Location *lt = GenBinaryOp(falloc, "<", op1, op2);
    result = GenUnaryOp(falloc, "!", lt);
  } else {
    BinaryOp::OpCode opcode;
    if (strcmp(opName, "|") == 0) {
      opcode = BinaryOp::Or;
    } else if (strcmp(opName, "&") == 0) {
      opcode = BinaryOp::And;
    } else {
      opcode = BinaryOp::OpCodeForName(opName);
    }

    result = GenTempVar(falloc);
    code->Append(new BinaryOp(opcode, result, op1, op2));
    return result;
  }
}

Location *CodeGenerator::GenUnaryOp(FrameAllocator *falloc,
                                    const char *opName, Location *op) {
  Location *result = NULL;
  if (strcmp(opName, "!") == 0) {
    // Currently, logical negation is implemented as:
    //   _tmp0 = 1
    //   _tmp1 = _tmp0 - op
    // We can do this because bool literals are implemented as integer 0 or 1
    //
    // We could instead extend Tac and Mips classes to include the xor
    // operator, in which case we can instead, do this (assuming op
    // is in $t1):
    //   addi $t0, $zero, -1        # -1 is all 1's in two's complement
    //   xor  $t1, $t1, $t0

    Location *tmp1 = GenLoadConstant(falloc, 1);
    result = GenBinaryOp(falloc, "-", tmp1, op);
  } else if (strcmp(opName, "-") == 0) {
    // _tmp0 = 0
    // _tmp1 = _tmp0 - op
    Location *tmp0 = GenLoadConstant(falloc, 0);
    result = GenBinaryOp(falloc, "-", tmp0, op);
  } else if (strcmp(opName, "~") == 0) {
    // _tmp0 = -1
    // _tmp1 = _tmp0 ^ op
    Location *tmp0 = GenLoadConstant(falloc, -1);
    result = GenBinaryOp(falloc, "^", tmp0, op);
  } else if (strcmp(opName, "++") == 0) {
    // _tmp0 = 1
    // _tmp1 = _tmp0 + op
    Location *tmp1 = GenLoadConstant(falloc, 1);
    result = GenBinaryOp(falloc, "+", tmp1, op);
  } else if (strcmp(opName, "--") == 0) {
    // _tmp0 = 1
    // _tmp1 = _tmp0 + op
    Location *tmp1 = GenLoadConstant(falloc, 1);
    result = GenBinaryOp(falloc, "-", tmp1, op);
  }

  return result;
}

void CodeGenerator::GenLabel(const char *label) {
  if (strcmp(label, "main") == 0) {
    mainFound = true;
  }
  code->Append(new Label(label));
}

void CodeGenerator::GenIfZ(Location *test, const char *label) {
  code->Append(new IfZ(test, label));
}

void CodeGenerator::GenGoto(const char *label) {
  code->Append(new Goto(label));
}

void CodeGenerator::GenReturn(Location *val) {
  code->Append(new Return(val));
}

BeginFunc *CodeGenerator::GenBeginFunc() {
  BeginFunc *result = new BeginFunc;
  code->Append(result);
  return result;
}

void CodeGenerator::GenEndFunc() {
  code->Append(new EndFunc());
}

void CodeGenerator::GenPushParam(Location *param) {
  code->Append(new PushParam(param));
}

void CodeGenerator::GenPopParams(int numBytesOfParams) {
  Assert(numBytesOfParams >= 0 && numBytesOfParams % VarSize == 0); // sanity check
  if (numBytesOfParams > 0) {
    code->Append(new PopParams(numBytesOfParams));
  }
}

Location *CodeGenerator::GenLCall(FrameAllocator *falloc, const char *label,
    bool fnHasReturnValue) {
  Location *result = fnHasReturnValue ? GenTempVar(falloc) : NULL;
  code->Append(new LCall(label, result));
  return result;
}

Location *CodeGenerator::GenACall(FrameAllocator *falloc, Location *fnAddr,
    bool fnHasReturnValue) {
  Location *result = fnHasReturnValue ? GenTempVar(falloc) : NULL;
  code->Append(new ACall(fnAddr, result));
  return result;
}

static struct _builtin {
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
    Location *arg1, Location *arg2) {
  Assert(bn >= 0 && bn < NumBuiltIns);
  struct _builtin *b = &builtins[bn];
  Location *result = NULL;

  // verify appropriate number of non-NULL arguments given
  if (b->hasReturn) {
    result = GenTempVar(falloc);
  }

  Assert((b->numArgs == 0 && !arg1 && !arg2)
      || (b->numArgs == 1 && arg1 && !arg2)
      || (b->numArgs == 2 && arg1 && arg2));

  if (arg2) {
    code->Append(new PushParam(arg2));
  }

  if (arg1) {
    code->Append(new PushParam(arg1));
  }

  code->Append(new LCall(b->label, result));
  GenPopParams(VarSize*b->numArgs);

  return result;
}

void CodeGenerator::GenPrintError(FrameAllocator *falloc,
    const char * const message) {
  Location *errString = GenLoadConstant(falloc, message);
  GenBuiltInCall(falloc, PrintString, errString, NULL);
  GenBuiltInCall(falloc, Halt, NULL, NULL);
}


void CodeGenerator::GenVTable(const char *className,
    List<const char *> *methodLabels) {
  code->Append(new VTable(className, methodLabels));
}


void CodeGenerator::DoFinalCodeGen() {
  if (!mainFound) {
    ReportError::NoMainFound();
  }

  // if debug don't translate to mips, just print Tac
  if (IsDebugOn("tac")) {
    for (int i = 0; i < code->NumElements(); i++) {
      code->Nth(i)->Print();
    }
  } else {
    Mips mips;
    mips.EmitPreamble();
    for (int i = 0; i < code->NumElements(); i++) {
      code->Nth(i)->Emit(&mips);
    }
  }
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
