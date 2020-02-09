#include "del.hpp"
#include <string>
#include <string.h>
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
