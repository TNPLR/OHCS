#include "del.hpp"
#include <string>
#include <string.h>
using namespace std;
#ifdef UNIX
void dell::del(char *src, char remove_key)
{
        char * fp = src;
        while (*src) {
                if (*src != remove_key) {
                        *fp = *src;
                        fp++;
                }
                src++;
        }
        *fp = '\0' ;
}
void dell::del(string &str, char remove_key)
{
        char tmp[str.size()+1];
        memcpy(&tmp, str.c_str(), str.size() + 1);
        del(tmp, remove_key);
        str = tmp;
}
#endif
#ifdef WIN32
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;
void dell::remove(char* charToRemove, string &str) {
	//string s = "Pineapple";
	//char chars[] = "p";
	for (unsigned int i = 0; i < strlen(charToRemove); ++i)
	{
		str.erase(remove(str.begin(), str.end(), charToRemove[i]), str.end());
	}

}

#endif // WIN32
