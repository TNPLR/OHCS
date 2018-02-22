#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include "base64.hpp"
#include "exception.hpp"
#include <string>
#include <iostream>
#include <sstream>
class DataKeyNCException : public Exception {
public:
	DataKeyNCException(const char *message) {
		_message = message;
	}
	virtual const char* message() {
		return _message;
	}
};
std::string Base64::Base64Encode(const std::string input)
{
	typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<std::string::const_iterator,6,8> > Base64EncodeIterator;
	std::stringstream result;
	std::copy(Base64EncodeIterator(input.begin()), Base64EncodeIterator(input.end()),std::ostream_iterator<char>(result));
	size_t equal_count = (3 - input.length() % 3) % 3;
	for(size_t i = 0; i < equal_count; ++i){
		result.put('=');
	}
	return result.str();
}
std::string Base64::Base64Decode(const std::string input)
{
	try{
		
		typedef boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<std::string::const_iterator>,8,6 > Base64DecodeIterator;
		std::stringstream result;
		std::copy(Base64DecodeIterator(input.begin()), Base64DecodeIterator(input.end()),std::ostream_iterator<char>(result));
		return result.str();
	}
	catch(...){
		throw DataKeyNCException("Data or Key Not Correct");
	}
}
std::string Base64::RmZero(std::string input)
{
	for(;;){
		if(input.back() == '\0'){
			input = input.substr(0,input.length()-1);
		}
		else return input;
	}
	return input;
}
