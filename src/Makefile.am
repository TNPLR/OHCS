AUTOMAKE_OPTIONS = foreign

AM_CXXFLAGS=-Wall -std=c++11 -I${top_srcdir}/include -Wextra -Wpedantic

bin_PROGRAMS=ohcs
ohcs_SOURCES=main.cpp OCSS.cpp $(top_srcdir)/include/del.hpp $(top_srcdir)/include/OCSS.hpp
ohcs_LDADD=-lboost_system -lgmpxx -lgmp -lboost_program_options
