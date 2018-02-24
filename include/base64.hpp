#include <string>
#include <vector>
namespace Base64{
	std::string Base64Encode(const std::string input);
	std::string Base64Decode(const std::string input);
	std::string RmZero(std::string input);
};
