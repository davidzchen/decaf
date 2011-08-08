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
    FrameDirection growth;
    Segment segment;

  public:
    FrameAllocator(Segment s, FrameDirection d);
    Location *Alloc(char *name, int size);
    int GetSize();
    Segment GetSegment() { return segment; }
};

#endif /* _H_FRAMEALLOC */
