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
	base64.cpp

)