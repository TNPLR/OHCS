#include "interface.hpp"
#include "OCSS.hpp"
#include "io.hpp"
#include <algorithm>
#include <vector>

static constexpr const unsigned long int blk_size = 256;

static std::vector<ocss_t> gen_subkey(std::string const& key)
{
	std::vector<ocss_t> keys;
	for (char const x : key) {
		keys.push_back(static_cast<ocss_t>(x));
	}
	return keys;
}

static void encrypt_mode(std::string const& input_filename, std::string key, std::string output_filename)
{
	std::vector<ocss_t> keys(gen_subkey(key));
	std::vector<ocss_t> data(get_data(input_filename));

	std::vector<std::vector<ocss_t> >result;
	for (auto it = data.begin(); it < data.end(); it += blk_size) {
		result.push_back(OCSS::Encrypt(std::vector<ocss_t>(it, (it + blk_size) < data.end() ? it + blk_size : data.end()), keys));
	}

	write_ohformat(output_filename, result);
}

static void decrypt_mode(std::string const& input_filename, std::string key, std::string output_filename)
{
	std::vector<ocss_t> keys(gen_subkey(key));
	std::vector<ocss_t> result;

	std::vector<std::vector<ocss_t> >data;
	data = get_ohformat(input_filename);

	std::reverse(keys.begin(), keys.end());
	for (auto &vec : data) {
		OCSS::Decrypt(vec, keys);
		result.insert(result.end(), vec.cbegin(), vec.cend());
	}
	write_data(output_filename, result);
}

void file_in_cs(int mode,std::string input_filename, std::string key, std::string output_filename)
{
	if (mode) {
		encrypt_mode(input_filename, key, output_filename);
	} else{
		decrypt_mode(input_filename, key, output_filename);
	}
}

