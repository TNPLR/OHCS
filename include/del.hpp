#include <string>
using namespace std;
#ifdef UNIX
void del(string &str, char remove_key);
void del(char *src, char remove_key);
#endif
#ifdef WIN32
namespace dell {
	void remove(char* charToRemove, string &str);
};

#endif