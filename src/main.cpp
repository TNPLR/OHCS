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
#include "interface.hpp"

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

static const char *  version = "4.2.0";

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
