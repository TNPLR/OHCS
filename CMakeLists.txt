cmake_minimum_required (VERSION 3.1)
project (OHCS)
# The version number.
SET (CMAKE_AR      "/usr/bin/llvm-ar")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
SET (CMAKE_NM      "/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -Wall -I/usr/lib/gcc/x86_64-redhat-linux/7/include/ -I./include -I./bigint")
set (OHCS_VERSION_MAJOR 0)
set (OHCS_VERSION_MINOR 1)
add_executable(
	ohcs
	bigint/BigIntegerAlgorithms.cc
	bigint/BigUnsigned.cc
	bigint/BigUnsignedInABase.cc
	bigint/BigInteger.cc
	bigint/BigIntegerUtils.cc
	main/OCSS.cpp
	main/argv.cpp
	main/main.cpp
)
find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
