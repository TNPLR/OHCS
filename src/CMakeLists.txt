INCLUDE_DIRECTORIES (${OHCS_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (/usr/include/boost)
ADD_EXECUTABLE (
	ohcs
	main.cpp
	del.cpp 
	OCSS.cpp 
	base64.cpp

)
