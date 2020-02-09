#include "del.hpp"
#include <string>
#include <string.h>
/*
void dell::del(char *src, char remove_key)
{
	char *fp = src;
	while (*src) {
		if (*src != remove_key) {
			*fp = *src;
			fp++;
		}
		src++;
	}
	*fp = '\0' ;
}
void dell::del(std::string &str, char remove_key)
{
	char tmp[str.size()+1];
	memcpy(&tmp, str.c_str(), str.size() + 1);
	del(tmp, remove_key);
	str = tmp;
}
*/
void dell::del(std::string &str, char remove_key)
{
	auto copy = str.begin();
	for (auto src = str.cbegin(); src < str.cend(); ++src) {
		if (*src != remove_key) {
			*copy++ = *src;
		}
	}
	str.erase(copy, str.end());
}
