/*
	Copyright (C) 2017,2020 CHAW-HUNG, HSIAO

---------------------------------------------------------------------------------------------------------------
	This file is part of OH Cryptography System.

	OH Cryptography System is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	OH Cryptography System is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with OH Cryptography System.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
This is the main file of OHCS
Made by Hsiaosvideo
  2017/07/21
*/
#include "OCSS.hpp"

#include <boost/program_options.hpp>

#include <cstdint>

#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

static const char *  version = "4.1.0";
static constexpr const unsigned long int blk_size = 1024;

static std::vector<ocss_t> gen_subkey(std::string const& key)
{
	std::vector<ocss_t> keys;
	for (char const x : key) {
		keys.push_back(static_cast<ocss_t>(x));
	}
	return keys;
}

static std::vector<ocss_t> get_data(std::string const& input_filename)
{
	std::ifstream in(input_filename);
	std::vector<ocss_t> result{std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
	in.close();
	return result;
}

static void write_data(std::string const& output_filename, std::vector<ocss_t> const& data)
{
	std::ofstream out(output_filename, std::ios::binary);
	std::copy(data.cbegin(), data.cend(), std::ostreambuf_iterator<char>(out));
	out.close();
}

static std::vector<std::vector<ocss_t> > get_ohformat(std::string const& input_filename)
{
	std::ifstream in;
	in.open(input_filename, std::ios::in | std::ios::binary);
	if (in.fail()) {
		throw;
	}
	std::vector<std::vector<ocss_t> >result;
	while(1) {
		uint64_t size;
		in.read(reinterpret_cast<char *>(&size), sizeof(size));
		if (in.eof()) {
			break;
		}
		ocss_t *buf = new ocss_t[size];
		in.read(reinterpret_cast<char *>(buf), size);
		result.push_back(std::vector<ocss_t>(buf, buf+size));
		delete []buf;
	}
	return result;
}

static void write_ohformat(std::string const& output_filename, std::vector<std::vector<ocss_t> > const& data)
{
	std::ofstream out;
	out.open(output_filename, std::ios::out | std::ios::binary);
	if (out.fail()) {
		throw;
	}
	for (auto const &vec : data) {
		uint64_t size = vec.size();
		out.write(reinterpret_cast<const char *>(&size), sizeof(size));
		out.write(reinterpret_cast<const char *>(&vec[0]), vec.size() * sizeof(vec[0]));
	}
	out.close();
}

static void encrypt_mode(std::string const& input_filename, std::string key, std::string output_filename)
{
	std::vector<ocss_t> keys(gen_subkey(key));
	std::vector<ocss_t> data(get_data(input_filename));

	std::vector<std::vector<ocss_t> >result;
	for (auto it = data.begin(); it < data.end(); it += blk_size) {
		std::vector<ocss_t> subvec(it, (it + blk_size) < data.end() ? it + blk_size : data.end());
		result.push_back(OCSS::Encrypt(subvec, keys));
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

static void file_in_cs(int mode,std::string input_filename, std::string key, std::string output_filename)
{
	if (mode) {
		encrypt_mode(input_filename, key, output_filename);
	} else{
		decrypt_mode(input_filename, key, output_filename);
	}
	exit(0);
}

static void version_show()
{
	std::cout<<"OH Crytoservice System\nVesion "<<version<<'\n';
}

int main(int argc, char* argv[]){
	std::string key;
	std::string input_filename;
	std::string output_filename;
	bool encryption = false; // default:decrypt

	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("key,k", po::value<std::string>(&key), "set key")
		("output,o", po::value<std::string>(&output_filename), "set output file")
		("version", "produce version message")
		("input,i", po::value<std::string>(&input_filename), "set input file")
		("encrypt,e", "set operating mode: encrypt")
		("decrypt,d", "set operating mode: decrypt");

	po::positional_options_description p;
	p.add("input", -1);

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
	po::notify(vm); 

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 0;
	}
	if (vm.count("version")) {
		version_show();
		return 0;
	}
	if (key.size() == 0) {
		std::cerr << "FATAL: No Key.\n";
		return 1;
	}
	if (vm.count("encrypt") && vm.count("decrypt")) {
		std::cerr << "FATAL: CANNOT do encryption and decryption at the same time.\n";
		return 1;
	} else if (vm.count("encrypt")) {
		if (input_filename.size() == 0) {
			std::cerr << "FATAL: No Input File.\n";
			return 1;
		}
		if (output_filename.size() == 0) {
			output_filename = input_filename + ".ohcs";
		}
		encryption = true;
	} else if (vm.count("decrypt")) {
		if (input_filename.size() == 0) {
			std::cerr << "FATAL: No Input File.\n";
			return 1;
		}
		if (output_filename.size() == 0) {
			std::size_t sz;
			output_filename = input_filename;
			if ((sz = input_filename.rfind(".ohcs")) == input_filename.size() - 5) {
				output_filename.erase(sz, 5);
			} else {
				output_filename += ".dec";
			}
		}
		encryption = false;
	}
	file_in_cs(encryption, input_filename, key, output_filename);
	return 0;
}
