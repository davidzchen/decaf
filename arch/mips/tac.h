/* File: tac.h
 * -----------
 * This module contains the Instruction class (and its various
 * subclasses) that represent Tac instructions and the Location
 * class used for operands to those instructions.
 *
 * Each instruction is mostly just a little struct with a
 * few fields, but each responds polymorphically to the methods
 * Print and Emit, the first is used to print out the TAC form of
 * the instruction (helpful when debugging) and the second to
 * convert to the appropriate MIPS assembly.
 *
 * The operands to each instruction are of Location class.
 * A Location object is a simple representation of where a variable
 * exists at runtime, i.e. whether it is on the stack or global
 * segment and at what offset relative to the current fp or gp.
 *
 * You may need to make changes/extensions to these classes
 * if you are working on IR optimization.
 */

#ifndef _H_tac
#define _H_tac

#include "decaf/list.h" // for VTable

class Mips;

// A Location object is used to identify the operands to the
// various TAC instructions. A Location is either fp or gp
// relative (depending on whether in stack or global segemnt)
// and has an offset relative to the base of that segment.
// For example, a declaration for integer num as the first local
// variable in a function would be assigned a Location object
// with name "num", segment fpRelative, and offset -8.

// DZC: I added the classRelative segment to the Segment enum.
// Even though this is not really a segment, it is useful for my
// FrameAllocator to keep track of offsets of class fields. The
// layout of the class is similar to that of an array except the
// first element is the pointer to the vTable. Fields begin at
// classRelative + 4.

typedef enum {
  fpRelative,
  gpRelative,
  classRelative
} Segment;

class Location {
 public:
  Location(Segment seg, int offset, const char *name);

  const char *GetName() { return variableName; }
  Segment GetSegment() { return segment; }
  int GetOffset() { return offset; }

 protected:
  const char *variableName;
  Segment segment;
  int offset;
};

// base class from which all Tac instructions derived
// has the interface for the 2 polymorphic messages: Print & Emit

class Instruction {
 public:
  virtual ~Instruction() {}
	virtual void Print();
	virtual void EmitSpecific(Mips *mips) = 0;
	virtual void Emit(Mips *mips);

 protected:
  char printed[128];
};

// for convenience, the instruction classes are listed here.
// the interfaces for the classes follows below

class LoadConstant;
class LoadStringConstant;
class LoadLabel;
class Assign;
class Load;
class Store;
class BinaryOp;
class Label;
class Goto;
class IfZ;
class BeginFunc;
class EndFunc;
class Return;
class PushParam;
class RemoveParams;
class LCall;
class ACall;
class VTable;

class LoadConstant : public Instruction {
 public:
  LoadConstant(Location *dst, int val);
  void EmitSpecific(Mips *mips);

 private:
  Location *dst;
  int val;
};

class LoadStringConstant : public Instruction {
 public:
  LoadStringConstant(Location *dst, const char *s);
  void EmitSpecific(Mips *mips);

 private:
  Location *dst;
  char *str;
};

class LoadLabel : public Instruction {
 public:
  LoadLabel(Location *dst, const char *label);
  void EmitSpecific(Mips *mips);
 private:
  Location *dst;
  const char *label;
};

class Assign : public Instruction {
 public:
  Assign(Location *dst, Location *src);
  void EmitSpecific(Mips *mips);
 private:
  Location *dst;
  Location *src;
};

class Load : public Instruction {
 public:
  Load(Location *dst, Location *src, int offset = 0);
  void EmitSpecific(Mips *mips);
 private:
  Location *dst, *src;
  int offset;
};

class Store : public Instruction {
 public:
  Store(Location *d, Location *s, int offset = 0);
  void EmitSpecific(Mips *mips);
 private:
  Location *dst, *src;
  int offset;
};

class BinaryOp : public Instruction {
 public:
  typedef enum {
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Eq,
    Less,
    And,
    Or,
    Xor,
    Shl,
    Shr,
    NumOps
  } OpCode;
  static const char* const opName[NumOps];
  static OpCode OpCodeForName(const char *name);

 protected:
  OpCode code;
  Location *dst, *op1, *op2;

 public:
  BinaryOp(OpCode c, Location *dst, Location *op1, Location *op2);
  void EmitSpecific(Mips *mips);
};

class Label : public Instruction {
 public:
  Label(const char *label);
  void Print();
  void EmitSpecific(Mips *mips);

 private:
  const char *label;
};

class Goto : public Instruction {
 public:
  Goto(const char *label);
  void EmitSpecific(Mips *mips);

 private:
  const char *label;
};

class IfZ : public Instruction {
 public:
  IfZ(Location *test, const char *label);
  void EmitSpecific(Mips *mips);

 private:
  Location *test;
  const char *label;
};

class BeginFunc : public Instruction {
 public:
  BeginFunc();
  // used to backpatch the instruction with frame size once known
  void SetFrameSize(int numBytesForAllLocalsAndTemps);
  void EmitSpecific(Mips *mips);

 private:
  int frameSize;
};

class EndFunc : public Instruction {
 public:
  EndFunc();
  void EmitSpecific(Mips *mips);
};

class Return : public Instruction {
 public:
  Return(Location *val);
  void EmitSpecific(Mips *mips);

 private:
  Location *val;
};

class PushParam : public Instruction {
 public:
  PushParam(Location *param);
  void EmitSpecific(Mips *mips);

 private:
  Location *param;
};

class PopParams : public Instruction {
 public:
  PopParams(int numBytesOfParamsToRemove);
  void EmitSpecific(Mips *mips);

 private:
  int numBytes;
};

class LCall : public Instruction {
 public:
  LCall(const char *labe, Location *result);
  void EmitSpecific(Mips *mips);

 private:
  const char *label;
  Location *dst;
};

class ACall: public Instruction {
 public:
  ACall(Location *meth, Location *result);
  void EmitSpecific(Mips *mips);

 private:
  Location *dst;
  Location *methodAddr;
};

class VTable: public Instruction {
 public:
  VTable(const char *labelForTable, List<const char *> *methodLabels);
  void Print();
  void EmitSpecific(Mips *mips);

 private:
  List<const char *> *methodLabels;
  const char *label;
};

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif
