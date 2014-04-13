#ifndef _H_FRAMEALLOC
#define _H_FRAMEALLOC

#include "arch/mips/tac.h"

typedef enum {
  FRAME_UP,
  FRAME_DOWN
} FrameDirection;

class FrameAllocator {
 protected:
  int off;
  int initOff;
  FrameDirection growth;
  Segment segment;

 public:
  FrameAllocator(Segment s, FrameDirection d);
  FrameAllocator(FrameAllocator *src);
  Location *Alloc(char *name, int size);
  int GetSize();

  // Getters
  int GetOff() { return off; }
  int GetInitOff() { return initOff; }
  FrameDirection GetGrowth() { return growth; }
  Segment GetSegment() { return segment; }
};

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif /* _H_FRAMEALLOC */
