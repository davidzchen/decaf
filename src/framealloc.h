#ifndef _H_FRAMEALLOC
#define _H_FRAMEALLOC

#include <tac.h>

typedef enum
{
  FRAME_UP,
  FRAME_DOWN
} FrameDirection;

class FrameAllocator
{
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
    int GetOff()               { return off; }
    int GetInitOff()           { return initOff; }
    FrameDirection GetGrowth() { return growth; }
    Segment GetSegment()       { return segment; }
};

#endif /* _H_FRAMEALLOC */
