#include <string>
namespace dell{
#ifdef UNIX
	void del(std::string &str, char remove_key);
	void del(char *src, char remove_key);
#endif
#ifdef WIN32
	void remove(char* charToRemove, std::string &str);

#endif
};
