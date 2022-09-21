cmake_minimum_required (VERSION 3.16)
project ("HWC" VERSION 1.0 LANGUAGES CXX) 

set(QQ_EX qq.out)
set(PERF_EX perf.out)
set(ALL_EX all.out)

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

foreach(EX IN LISTS QQ_EX PERF_EX ALL_EX)

	add_executable (${EX} ${SOURCES})
	target_include_directories (${EX} PRIVATE ${INCLUDE})
	if (EX STREQUAL QQ_EX)
		set(ADDITIONAL -DQQ)
	endif()
	if (EX STREQUAL PERF_EX)
		set(ADDITIONAL -DPERF)
	endif()
	if (EX STREQUAL ALL_EX)
		set(ADDITIONAL -DQQ -DPERF)
	endif()
	target_compile_options (${EX} PRIVATE ${COMPILE_SETTINGS} ${ADDITIONAL})

endforeach()