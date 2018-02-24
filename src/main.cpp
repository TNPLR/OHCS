/*
	Copyright (C) 2017 CHAW-HUNG, HSIAO

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
#include <locale>
#include <vector>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <thread>
#include "BigIntegerLibrary.hh"
#include <cstring>
#include "omp.h"
#ifndef __GNUC__
# define __attribute__(x) /*NOTHING*/
#endif
/*
char file = 0;
char R[100];
char *ReadFile = R;
*/
#include "del.hpp"
#include <fstream>
#include "OCSS.hpp"
#include "base64.hpp"
using Base64::Base64Encode;
using Base64::Base64Decode;
using Base64::RmZero;
//#include <thread>
#ifdef UNIX
#include <ncurses.h>
#include <getopt.h>
#endif
const char *  version = "3.0.1";
#ifdef UNIX

const char* program_name;
void file_in_cs(int mode,std::string input_filename, std::string key, std::string output_filename) __attribute__ ((const));
void print_usage(FILE* stream,int exit_code) __attribute__ ((__noreturn__));
void print_usage(FILE* stream, int exit_code)
{
	fprintf(stream, "Usage: %s [-e | -d] options [-i input-file]\n", program_name);
	fprintf(stream,
		"\t-h\t--help\t\t\tDisplay this help page.\n"
		"\t-e\t--encrypt\t\tEncrypt mode.\n"
		"\t-d\t--decrypt\t\tDecrypt mode.\n"
		"\t-D\t--data [input-data]\tImport Data.\n"
		"\t-i\t--input [input-file]\tSelect input file.\n"
		"\t-k\t--key [key]\t\tImport the key.\n"
		"\t-v\t--version\t\tShow the Version.\n"
		"\t-t\t--tui\t\t\tTUI mode\n");
	exit(exit_code);
}
#endif
std::vector<std::string> base64_read_file(std::string input_filename)
{
	std::ifstream fin(input_filename, std::ios::in);
	if(!fin) {
		std::cerr << "Error:Can not input this file.\n";
		exit(-1);
	}
	std::string inputStr;
	std::vector<std::string> inputContent;
	while(getline(fin, inputStr)){
		if(inputStr == "") continue;
		inputContent.push_back(inputStr);
	}
#ifdef DEBUG
	for(unsigned int i=0; i < inputContent.size();i++){
		std::cout<<inputContent[i]<<std::endl;	
	}
#endif
	fin.close();
	return inputContent;
}
std::vector<std::string> read_file(std::string input_filename)
{
	std::ifstream fin(input_filename, std::ios::in | std::ios::binary);
	if(!fin) {
		std::cerr << "Error:Can not input this file.\n";
		exit(-1);
	}
	char inputChar;
	std::string inputStr;
	std::vector<std::string> inputContent;
	unsigned int i = 0;	
	while(!fin.eof()){
		fin.get(inputChar);
		inputStr.push_back(inputChar);
		++i;
		if(i == 128){
			inputContent.push_back(inputStr);
			inputStr = "";
			i = 0;
		}
	}
	inputContent.push_back(inputStr);
	inputStr = "";
#ifdef DEBUG
	for(unsigned int i=0; i < inputContent.size();i++){
		std::cout<<inputContent[i]<<std::endl;	
	}
#endif
	fin.close();
	return inputContent;
}
inline void base64_write_file(std::string output_filename, std::vector<std::string> inputContent)
{
#ifdef DEBUG
	auto cout_data = [=](std::vector<std::string> inputContent)->void
			{
				for(unsigned int i=0; i < inputContent.size(); i++){
					std::cout << inputContent[i];
				}
			};
	std::thread mThread(cout_data,inputContent);
#endif
	std::ofstream out(output_filename);		
	for(unsigned int i=0; i < inputContent.size(); i++){
		out << inputContent[i] << std::endl;
	}
	out.close();
#ifdef DEBUG
	mThread.join();
#endif
}
inline void write_file(std::string output_filename, std::vector<std::string> inputContent)
{
#ifdef DEBUG
	auto cout_data = [=](std::vector<std::string> inputContent)->void
			{
				for(unsigned int i=0; i < inputContent.size(); i++){
					std::cout << inputContent[i];
				}
			};
	std::thread mThread(cout_data,inputContent);
#endif
	std::ofstream out(output_filename, std::ios::out | std::ios::binary);
	for(unsigned int i=0; i < inputContent.size(); i++){
		out << inputContent[i];
	}
	out.close();
#ifdef DEBUG
	mThread.join();
#endif
}
void file_in_cs(int mode,std::string input_filename, std::string key, std::string output_filename)
{
	std::vector<char> keys;
	for (char &x : key) {
		keys.push_back(x);
	}
	if(mode){
		std::vector<std::string>&& inputContent = base64_read_file(input_filename);
		std::reverse(keys.begin(), keys.end());
		#pragma omp parallel for num_threads(4)
		for(unsigned int i=0; i < inputContent.size(); i++){
			OCSS::Decrypt(inputContent[i], keys);
			inputContent[i].erase(0,3);
			inputContent[i] = Base64::Base64Decode(inputContent[i]);
			std::cout << "Line:"<< i+1<<std::endl;
			if(inputContent[i] != ""){
				inputContent[i] = Base64::RmZero(inputContent[i]);
			}
		}
		inputContent[inputContent.size() - 1].pop_back();
		write_file(output_filename, inputContent);
	}
	else{
		std::vector<std::string>&& inputContent = read_file(input_filename);
		#pragma omp parallel for num_threads(4)
		for(unsigned int i=0; i < inputContent.size(); i++){
#ifdef DEBUG
			std::cout << inputContent[i] << std::endl;
#endif
			inputContent[i] = Base64Encode(inputContent[i]);
			inputContent[i].insert(0,"aaa");
			std::cout << "Line:"<< i+1<<std::endl;
			inputContent[i] = OCSS::Encrypt(inputContent[i], keys);
		}
		base64_write_file(output_filename, inputContent);
	}
	exit(0);
}
inline void version_show()
{
#ifdef WIN32
	std::cout<<"OH Crytoservice System on Windows\n Vesion "<<version<<'\n';
	return;
#endif
#ifdef UNIX
	std::cout<<"OH Crytoservice System on Unix\nVesion "<<version<<'\n';
#endif
#ifdef Unknown
	std::cout<<"OH Crytoservice Systems\n Vesion "<<version<<'\n';
#endif
	exit(0);
}
#ifdef UNIX
void tui_main()
{
	char* data = new char[1024];
	char* key = new char[256];
	initscr();
	printw("OH Crytoservice System on Unix\nVesion %s\n", version);
	refresh();
	printw("Data: ");
	refresh();
	getnstr( data, 10231 );
	printw("Key: ");
	getnstr( key, 255);	
	std::vector<char> keys;
	std::string Key = key;
	for (char x : Key) {
		keys.push_back(x);
	}
	std::string Select;
	printw("Encrypt or Decrypt");
	refresh();
	auto ch = getch();
	switch(ch){
		case 'D':
			Select = "D";
			printw("Decrypt mode\n");
			break;
		case 'E':
			Select = "E";
			printw("Encrypt mode\n");
			break;
		default:
			Select = "E";
			printw("Using defaault: Encrypt mode\n");
	}
	refresh();
	if(Select == "E"){
		std::string Data = data;
		Data = Base64Encode(Data);
		Data.insert(0,"aaa");
		Data = OCSS::Encrypt(Data,keys);
		data = &Data[0];
		printw("%s\n", data);
		refresh();
	}
	else{
		std::string Data = data;
		std::reverse(keys.begin(), keys.end());
		OCSS::Decrypt(Data, keys);
		Data.erase(0,3);
		Data = Base64Decode(Data);
		Data = RmZero(Data);
		data = &Data[0];
		printw("%s\n", data);
		refresh();
	}
	delete(data);
	delete(key);
	getch();
	endwin();
	exit(0);
}
#endif
int main(int argc, char* argv[]){
	std::string key;
	std::string data;
	srand(time(NULL));
#ifdef UNIX
	int next_option;
	const char* const short_options = "o:vhedi:k:t";
	const struct option long_options[] = {
		{"help",0,NULL,'h'},
		{"encrypt",0,NULL,'e'},
		{"decrypt",0,NULL,'d'},
		//{"data",1,NULL,'D'},
		{"input",1,NULL,'i'},
		{"key",1,NULL,'k'},
		{"version",0,NULL,'v'},
		{"output",1,NULL,'o'},
		{"tui",0,NULL,'t'},
		{NULL,0,NULL,0}
	};
	std::string input_filename = "";
	std::string output_filename = "";
	int mode = 0; // Encrypt:0, Decrypt 1
	program_name = argv[0];
	do {
		next_option = getopt_long (argc, argv, short_options,
				long_options, NULL);
		switch (next_option){
			case 'h':
				print_usage (stdout, 0);
			case 'i':
				input_filename = optarg;
				break;
			case 'd':
				mode = 1;
				break;
			/*
			case 'D':
				data_mode = 0;
				data = optarg;
				data[0] = '\0';
				data[data.length()] = '\0';
				break;
			*/
			case 'e':
				mode = 0;
				break;
			case 'k':
				key = optarg;
				break;
			case 'v':
				version_show();
			case 'o':
				output_filename = optarg;
				break;
			case 't':
				tui_main();
			case '?': /* The user specified an invalid option. */
				print_usage (stderr, 1);
			case -1:
				break;
			default:
				abort();
		}
	}while(next_option != -1);
	if(!(input_filename.compare("")) || !(output_filename.compare("")))
	{
		std::cerr<<"ERROR: Input file or output file undefine."<<std::endl;
		exit(0);
	}
	file_in_cs(mode,input_filename,key,output_filename);
#endif
#ifdef WIN32
	using namespace std;
	ios_base::sync_with_stdio(false);
	std::string new_data = "";
	version_show();
	std::cout<<" File:\n";
	getline(cin,data);
	std::cout<<" Key:"<<'\n';
	getline(cin,key);
	std::string Select;
	std::cout<<"[E]ncrypt or [D]ecrypt?\n";
	std::cin>>Select;
	if(Select == "E"){
		file_in_cs(0,data,key,data);	
	}
	else{
		file_in_cs(1,data,key,data);
	}
#endif
	return 0;
}
