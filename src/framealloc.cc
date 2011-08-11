#include <config.h>
#include "framealloc.h"


FrameAllocator::FrameAllocator(Segment s, FrameDirection d)
{
  off = initOff = 0;
  if (s == fpRelative && d == FRAME_DOWN)
    initOff = off = -4;
  if (s == classRelative)
    initOff = off = 4;

  growth = d;
  segment = s;
}

FrameAllocator::FrameAllocator(FrameAllocator *src)
{
  off     = src->GetOff();
  initOff = src->GetInitOff();
  growth  = src->GetGrowth();
  segment = src->GetSegment();
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
  int size = off - initOff;

  return (size < 0) ? (size * -1) : size;
}
