#include "OCSS.hpp"
#include <array>
#include "del.hpp"
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include "BigIntegerLibrary.hh"
#include <cstring>
#include "exception.hpp"
#include "omp.h"
#ifdef DEBUG
#include "DebugTimer.hpp"
#endif
class KeyChangeException : public Exception {
public:
	KeyChangeException(int);

	KeyChangeException(const char *message) {
		_message = message;
	}

	virtual const char* message() {
		return _message;
	}
};
KeyChangeException::KeyChangeException(int index) {
	std::string str1;
	std::stringstream sstr;
	sstr << index;
	sstr >> str1;
	std::string str2("KeyChangeException:");
	str2.append(str1);
	_message = str2.c_str();
}
class BaseZeroOneException : public Exception {
public:
	BaseZeroOneException(const char *message) {
		_message = message;
	}
	virtual const char* message() {
		return _message;
	}
};
std::string Char_List = "#*ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/=!";
const int last_key_init = 68;
#ifdef SEOHCS
std::string OCSS::SafetyEncrypt(std::string Data,std::vector<char> Key)
{
	std::vector<char> backup_key = Key;
	std::string backup_data = Data;
	std::string encrypt_data;
	while(true){
		encrypt_data = Encrypt(Data,Key);
		if(Key != backup_key){
			throw KeyChangeException("Error:KeyChangeException");
		}
		std::reverse(Key.begin(), Key.end());
		Decrypt(Data,Key);
		if(Data == backup_data){
			return encrypt_data;
		}
		else{
#ifdef DEBUG
			std::cout<<"Try agian:";
#endif
			Key = backup_key;
			Data = backup_data;
			continue;
		}
	}
}
#endif	
std::string OCSS::Encrypt(std::string Data,std::vector<char> Key)
{
	int last_key = last_key_init;
#ifdef DEBUG
	printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]);std::cout<<Data<<'\n';
#endif
	for(char plugin_key : Key)
        {
		unsigned int datalength = Data.length();
		int plugin_value = 0;
                for (unsigned int values = 0; values < Char_List.length() ; ++values)
                {
                        if (Char_List[values] == plugin_key)
                        {
                                plugin_value = values;
                        }
                }
                ToBase(Data, last_key, plugin_value);
#ifdef DEBUG
                printf("Base %d-\"%c\"||", plugin_value, Char_List[plugin_value - 1]);
		std::cout<<Data<<'\n';
#endif

	    	unsigned int plugin_count = rand()%datalength/3+1;
                std::vector<unsigned int> plugin_location;
		plugin_location.reserve(plugin_count);
                for (int i = 0;plugin_count > 0; --plugin_count,++i)
                {
                        plugin_location[i] = rand()%datalength;
                }

/*	
		const unsigned int plugin_count = rand()%datalength/3;
		std::array<unsigned int, plugin_count> plugin_location = {0};
		for(unsigned *ptr = plugin_location.data; plugin_count >= 0; --plugin_count, ++ptr){
			*ptr = rand()%datalength;
		}
*/
                //#pragma omp parallel for
                for(unsigned int& this_location : plugin_location)
                {
                        std::string new_data = "";
                        for (unsigned int x = 0; x < datalength; ++x)
                        {
                                if (x == this_location)
                                {
                                        new_data += Char_List[plugin_value];
                                }
                                new_data += Data[x];
                        }
                        Data = new_data;
                }
                last_key = (int)(plugin_value + 1);
#ifdef DEBUG
                printf("Base %d-\"%c\"||", plugin_value + 1, Char_List[plugin_value]); std::cout<<Data<<'\n';//Debug
#endif
	}
        ToBase(Data, last_key, last_key_init);
#ifdef DEBUG
        printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]); std::cout<<Data<<'\n';
#endif
	return Data;
}
void OCSS::Decrypt(std::string& Data,std::vector<char>& Key)
{
	int last_key = last_key_init;
#ifdef DEBUG
        printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]);std::cout<<Data<<'\n';
#endif
        for(char &remove_key : Key)
        {
                int remove_value = 0;
                for (unsigned int values = 0; values < Char_List.length(); ++values)
                {
                        if (Char_List[values] == remove_key)
                        {
                                remove_value = values;
                        }
                }
                ToBase(Data, last_key, (int)(remove_value + 1));
#ifdef DEBUG
                printf("Base %d-\"%c\"||", remove_value + 1, Char_List[remove_value]);std::cout<<Data<<'\n';
#endif
#ifdef UNIX
				dell::del(Data, remove_key);
#endif
#ifdef WIN32
				char tmpRemove[] = {remove_key};
				dell::remove(tmpRemove,Data);
#endif // WIN32
#ifdef DEBUG
                printf("Base %d-\"%c\"||", remove_value, Char_List[remove_value - 1]);std::cout<<Data<<'\n';
#endif
                last_key = remove_value;
        }
        ToBase(Data, last_key, last_key_init);
#ifdef DEBUG
	printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]); std::cout<<Data<<'\n';
#endif
}
void OCSS::ToBase(std::string& Data,int Original_Base,int New_Base)
{
        if (Original_Base == 0 || Original_Base == 1 || New_Base == 0 || New_Base == 1 || Data == "")
        {
		throw BaseZeroOneException("ERROR: BaseZeroOneException");
                return;
        }
        BigInteger total_value = 0;
        for(char& data : Data)
        {
                total_value *= Original_Base;
                unsigned int values = 0;
                for (; values < Char_List.length(); ++values)
                {
                        if (Char_List[values] == data)
                        {
                                break;
                        }
                }
                total_value += values;
        }
        std::string return_value = "";
        while (total_value > 0) 
        {
                int left = (total_value % New_Base).toInt();
                // return_value = Char_List[left] + return_value;
		return_value += Char_List[left];
                total_value = (total_value - left) / New_Base;
        }
	reverse(return_value.begin(),return_value.end());
        Data = return_value;
        return;
}
#ifdef DEBUG
int OCSS::Char_Value(char chars)
{
        unsigned int values;
        //#pragma omp parallel for
        for (values = 0; values < Char_List.length() ; ++values)
        {
                if (Char_List[values] == chars)
                {
                        break;
                }
        }
        return values;
}
bool OCSS::check()
{
        std::string x = "ASC";
        std::string z = x;
        OCSS::ToBase(x, 95, 23);
        OCSS::ToBase(x, 23, 95);
        if (x == z)
        {
                return true;
        }
        return false;
}
#endif
