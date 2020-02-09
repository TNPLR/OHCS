#AM_CXXFLAGS=-static -static-libstdc++ -static-libgcc -fopenmp -Wall -DWIN32 -std=gnu++11 -I/usr/include/boost -I${top_srcdir}/include -Wno-deprecated
AM_CXXFLAGS=-lboost_system -lrt -lncurses -fopenmp -Wall -DUNIX -lpthread -std=gnu++11 -I/usr/include/boost -I${top_srcdir}/include -Wno-deprecated -static -ltinfo -lgmpxx -lgmp
bin_PROGRAMS=ohcs
ohcs_SOURCES=main.cpp OCSS.cpp del.cpp OCSS.hpp base64.cpp
