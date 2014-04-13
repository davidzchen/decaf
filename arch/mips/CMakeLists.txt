list(APPEND ARCH_MIPS_SOURCES
  tac.cc
  mips.cc)

add_library(arch_mips OBJECT ${ARCH_MIPS_SOURCES})
