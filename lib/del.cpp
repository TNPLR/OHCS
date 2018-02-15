#include "del.hpp"
#include <string>
#include <string.h>
using namespace std;
void del(char *src, char remove_key)
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
void del(string &str, char remove_key)
{
        char tmp[str.size()+1];
        memcpy(&tmp, str.c_str(), str.size() + 1);
        del(tmp, remove_key);
        str = tmp;
}
