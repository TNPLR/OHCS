#ifndef OCSS_H
#define OCSS_H
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include "BigIntegerLibrary.hh"
#ifndef __GNUC__
# define __attribute__(x) /*NOTHING*/
#endif
#ifdef WIN32
#include <omp.h>
#endif
#include <string.h>
using namespace std;
void Encrypt(std::string& __restrict__ Data,vector<char>& __restrict__ Key const);
void Decrypt(string& Data,vector<char>& Key);
void ToBase(string& Data,int Original_Base,int New_Base);
#ifdef DEBUG
int Char_Value(char chars);
bool check();
#endif
#endif // OCSS_H
