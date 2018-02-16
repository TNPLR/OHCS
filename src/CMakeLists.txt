set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
INCLUDE_DIRECTORIES (${OHCS_SOURCE_DIR}/include)
ADD_EXECUTABLE (
	ohcs
	main.cpp
	BigIntegerAlgorithms.cc 
	BigUnsigned.cc 
	del.cpp 
	OCSS.cpp 
	BigInteger.cc 
	BigUnsignedInABase.cc
       	BigIntegerUtils.cc

)
install(TARGETS ohcs
	RUNTIME DESTINATION bin
)

