#ifndef OCSS_H
#define OCSS_H
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include "../bigint/BigIntegerLibrary.hh"
#include <omp.h>
#include <cstring>
using namespace std;
class OCSS
{
    public:
        OCSS();
        virtual ~OCSS();
        void Encrypt(string& Data,vector<char>& Key);
        void Decrypt(string& Data,vector<char>& Key);
        void ToBase(string& Data,int Original_Base,int New_Base);
        int Char_Value(char chars);
        bool check();
        bool DMode;
	void del(char *src, char remove_key);
	void del(string &str, char remove_key);
};

#endif // OCSS_H
