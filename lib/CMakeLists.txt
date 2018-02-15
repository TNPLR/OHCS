ADD_LIBRARY (del del.cpp)
ADD_LIBRARY (bigint BigInteger.cc BigIntegerUtils.cc BigUnsigned.cc BigUnsignedInABase.cc)
ADD_LIBRARY (OCSS OCSS.cpp BigInteger.cc BigIntegerUtils.cc BigUnsigned.cc BigUnsignedInABase.cc del)
