#ifndef OCSS_H
#define OCSS_H
#include <string>
#include <vector>
#ifndef __GNUC__
# define __attribute__(x) /*NOTHING*/
#endif
namespace OCSS{
#ifdef SEOHCS
	std::string SafetyEncrypt(std::string Data, std::vector<char> Key);
#endif
	std::string Encrypt(std::string Data,std::vector<char> Key);
	void Decrypt(std::string& Data,std::vector<char>& Key);
	void ToBase(std::string& Data,int Original_Base,int New_Base);
#ifdef DEBUG
	int Char_Value(char chars);
	bool check();
#endif
};
#endif // OCSS_H
