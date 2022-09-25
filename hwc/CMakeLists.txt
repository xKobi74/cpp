cmake_minimum_required (VERSION 3.16)
project ("HWC" VERSION 1.0 LANGUAGES CXX) 

set (INCLUDE 
  include
)

set (SOURCES 
  source/main.cc
)

set (COMPILE_SETTINGS
  -O2
  -DNDEBUG
)

set (OUTS
  qq.out
  perf.out
  all.out
)

set (OPTS
  -DQQ
  -DPERF
  -DQQ -DPERF
)

list(LENGTH OUTS len1)
math(EXPR len2 "${len1} - 1")

foreach(val RANGE ${len2})
  list(GET OUTS ${val} EX)
  list(GET OPTS ${val} OPT)
  message(STATUS "${EX}  ${OPT}")
  add_executable (${EX} ${SOURCES})
  target_include_directories (${EX} PRIVATE ${INCLUDE})
  set(ADDITIONAL ${OPT})
  target_compile_options (${EX} PRIVATE ${COMPILE_SETTINGS} ${ADDITIONAL})
endforeach()

set(TEST test.out)
set(TEST_SR source/tester.cc)

add_executable(${TEST} ${TEST_SR})
target_include_directories (${TEST} PRIVATE ${INCLUDE})
target_link_libraries(${TEST} gtest gmock pthread)
target_compile_options (${TEST} PRIVATE ${COMPILE_SETTINGS})
