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
#ifdef WIN32
#include <omp.h>
#endif
#include <string.h>
using namespace std;
void Encrypt(string& Data,vector<char>& Key);
void Decrypt(string& Data,vector<char>& Key);
void ToBase(string& Data,int Original_Base,int New_Base);
int Char_Value(char chars);
bool check();
void del(char *src, char remove_key);
void del(string &str, char remove_key);

#endif // OCSS_H
