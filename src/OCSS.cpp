#include "OCSS.hpp"
#include "del.hpp"

#include <gmpxx.h>

#include <stdexcept>
#include <vector>
#include <algorithm> // std::reverse
#include <random>

constexpr const unsigned int key_max = 256;
constexpr const unsigned int insert_time = 16;

static void ToBase(std::vector<ocss_t>& Data, unsigned int Original_Base, unsigned int New_Base)
{
	if (Original_Base == 0) {
		throw std::invalid_argument("Original_Base should not be zero");
	} else if (Original_Base == 1) {
		throw std::invalid_argument("Original_Base should not be one");
	} else if (New_Base == 0) {
		throw std::invalid_argument("New_Base should not be zero");
	} else if (New_Base == 1) {
		throw std::invalid_argument("New_Base should not be one");
	} else if (Data.size() == 0) {
		throw std::invalid_argument("Size of Data should not be zero");
	}

	mpz_class total_value = 0;
	for(unsigned char const data : Data) {
		total_value *= Original_Base;
		total_value += data;
	}
	Data.clear();
	while (total_value > 0) {
		mpz_class left = total_value % New_Base;
		Data.push_back(static_cast<ocss_t>(left.get_ui()));
		total_value = (total_value - left) / New_Base;
	}
	std::reverse(Data.begin(), Data.end());
}

std::vector<ocss_t> OCSS::Encrypt(std::vector<ocss_t> Data,std::vector<ocss_t> const& Key)
{
	unsigned int last_key = key_max;
	std::random_device rd;
	std::mt19937_64 generator(rd());

	for(ocss_t plugin_key : Key) {
		ToBase(Data, last_key, plugin_key);

		for (unsigned long int i = 0; i < insert_time; ++i) {
			std::uniform_int_distribution<unsigned long int> unif(0, Data.size());
			Data.insert(Data.begin() + unif(generator), plugin_key);
		}

		last_key = static_cast<unsigned int>(plugin_key) + 1;
	}
	ToBase(Data, last_key, key_max);
	return Data;
}

void OCSS::Decrypt(std::vector<ocss_t>& Data,std::vector<ocss_t> const& Key)
{
	unsigned int last_key = key_max;
	for (ocss_t const remove_key : Key) {
		ToBase(Data, last_key, static_cast<unsigned int>(remove_key) + 1);
		dell::del(Data, remove_key);
		last_key = remove_key;
	}
	ToBase(Data, last_key, key_max);
}
