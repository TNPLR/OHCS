#include "OCSS.hpp"
#include "del.hpp"
#include "base64.h"
#ifndef SEOHCS
#define SEOHCS
#endif
#ifndef EXCEPTION
#define EXCEPTION

class Exception {
public:
	Exception() {
	
	}
	Exception(const char *message) : _message(message) {
	
	}

	virtual const char* message() {
		return _message;
	}
protected:
	const char *_message;
};
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
#ifndef SEOHCS
std::string Char_List = "\t0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ `-=[]\\;',./~!@#$%^&*()_+{}|:\"<>?";
const int last_key_init = 96;
#endif
#ifdef SEOHCS
std::string Char_List = "#*ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/=";
const int last_key_init = 67;
#endif
std::string OCSS::SafetyEncrypt(std::string Data,vector<char> Key)
{
	vector<char> backup_key = Key;
	std::string backup_data = Data;
	std::string encrypt_data;
	while(true){
		Encrypt(Data,Key);
		encrypt_data = Data;
		if(Key != backup_key){
			throw KeyChangeException("Error:KeyChangeException");
		}	
		reverse(Key.begin(), Key.end());
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
	// It won't be here
	return Data;
}
void OCSS::Encrypt(std::string& __restrict__ Data,vector<char>& __restrict__ Key)
{
	int last_key = last_key_init;
#ifdef DEBUG
	printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]);cout<<Data<<'\n';
#endif
	for(char plugin_key : Key)
        {
		int plugin_value = 0;
                //#pragma omp parallel for
                for (unsigned int values = 0; values < Char_List.length() ; ++values)
                {
                        if (Char_List[values] == plugin_key)
                        {
                                plugin_value = values;
                        }
                }
                ToBase(Data, last_key, plugin_value);
#ifdef DEBUG
                printf("Base %d-\"%c\"||", plugin_value, Char_List[plugin_value - 1]);cout<<Data<<'\n';
#endif
	    	unsigned int plugin_count = rand()%Data.length()/3+1;
                vector<unsigned int> plugin_location;
                while (plugin_count > 0)
                {
                        plugin_location.push_back(rand()%Data.length());
                        plugin_count--;
                }
                //#pragma omp parallel for
                for(unsigned int& this_location : plugin_location)
                {
                        string new_data = "";
                        //#pragma omp parallel for
                        for (unsigned int x = 0; x < Data.length(); ++x)
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
                printf("Base %d-\"%c\"||", plugin_value + 1, Char_List[plugin_value]); cout<<Data<<'\n';//Debug
#endif
	}
        ToBase(Data, last_key, last_key_init);
#ifdef DEBUG
        printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]); cout<<Data<<'\n';
#endif
	return;
}
void OCSS::Decrypt(string& Data,vector<char>& Key)
{
	int last_key = last_key_init;
#ifdef DEBUG
        printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]);cout<<Data<<'\n';
#endif
        for(char &remove_key : Key)
        {
                int remove_value = 0;
                //#pragma omp parallel for
                for (unsigned int values = 0; values < Char_List.length(); ++values)
                {
                        if (Char_List[values] == remove_key)
                        {
                                remove_value = values;
                                break;
                        }
                }
                ToBase(Data, last_key, (int)(remove_value + 1));
#ifdef DEBUG
                printf("Base %d-\"%c\"||", remove_value + 1, Char_List[remove_value]);cout<<Data<<'\n';
#endif
#ifdef UNIX
				del(Data, remove_key);
#endif
#ifdef WIN32
				char tmpRemove[] = {remove_key};
				dell::remove(tmpRemove,Data);
#endif // WIN32
#ifdef DEBUG
                printf("Base %d-\"%c\"||", remove_value, Char_List[remove_value - 1]);cout<<Data<<'\n';
#endif
                last_key = remove_value;
        }
        ToBase(Data, last_key, last_key_init);
#ifdef DEBUG
	printf("Base %d-\"%c\"||", last_key_init, Char_List[last_key_init-1]); cout<<Data<<'\n';
#endif
}
void OCSS::ToBase(string& Data,int Original_Base,int New_Base)
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
                //#pragma omp parallel for
                for (; values < Char_List.length(); ++values)
                {
                        if (Char_List[values] == data)
                        {
                                break;
                        }
                }
                total_value += values;
        }
        string return_value = "";
        while (total_value > 0) 
        {
                int left = (total_value % New_Base).toInt();
                return_value = Char_List[left] + return_value;
                total_value = (total_value - left) / New_Base;
        }
        return_value = return_value.erase(return_value.find_last_not_of('0')+1);
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
        string x = "ASC";
        string z = x;
        ToBase(x, 95, 23);
        ToBase(x, 23, 95);
        if (x == z)
        {
                return true;
        }
        return false;
}
#endif
