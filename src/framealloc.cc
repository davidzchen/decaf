#include "framealloc.h"

FrameAllocator::FrameAllocator(Segment s, FrameDirection d)
{
  off = 0;
  growth = d;
  segment = s;
}

Location *FrameAllocator::Alloc(char *name, int size)
{
  if (growth == FRAME_UP)
    off += size;
  else
    off -= size;

  return new Location(segment, off, name);
}

int FrameAllocator::GetSize()
{
  return (off < 0) ? (off * -1) : off;
}
