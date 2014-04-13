add_executable(dcc
  $<TARGET_OBJECTS:arch_mips>
  $<TARGET_OBJECTS:ast>
  $<TARGET_OBJECTS:decaf>)

target_link_libraries(dcc -ll)
