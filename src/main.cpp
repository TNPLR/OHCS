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
#ifndef __GNUC__
# define __attribute__(x) /*NOTHING*/
#endif
#pragma once
#include <cstdio>
char file = 0;
char R[100];
char *ReadFile = R;
#include <cstdlib>
#include "del.hpp"
#include <fstream>
#include "OCSS.hpp"
//#include <thread>
#ifdef UNIX
#include <getopt.h>
#endif
#ifdef UNIX
const std::string version = "1.6";
const char* program_name;
void file_in_cs(int mode,std::string input_filename, std::string key, std::string output_filename) __attribute__ ((const));
void print_usage(FILE* stream,int exit_code) __attribute__ ((__noreturn__));
void print_usage(FILE* stream, int exit_code)
{
	fprintf(stream, "Usage: %s [-e | -d] options [-i input-file]\n", program_name);
	fprintf(stream,
		"\t-h\t--help\t\tDisplay this help page.\n"
		"\t-e\t--encrypt\t\tEncrypt mode.\n"
		"\t-d\t--decrypt\t\tDecrypt mode.\n"
		"\t-D\t--data [input-data]\tImport Data.\n"
		"\t-i\t--input [input-file]\tSelect input file.\n"
		"\t-k\t--key [key]\tImport the key.\n"
		"\t-v\t--version\tShow the Version.\n");
	exit(exit_code);
}
void file_in_cs(int mode,std::string input_filename, std::string key, std::string output_filename)
{
	std::vector<char> keys;
	for (char &x : key) {
		keys.push_back(x);
	}
	ifstream fin;
	fin.open(input_filename);
	if(!fin) {
		cerr << "Error:Can not input this file.\n";
	       	exit(-1);
	}
	std::string inputStr;
	std::vector<string> inputContent;
	while(getline(fin, inputStr)){
		inputContent.push_back(inputStr);
	}
#ifdef DEBUG
	for(int i=0; i < inputContent.size();i++){
		cout<<inputContent[i]<<endl;
	}
#endif
	fin.close();
	ofstream out(output_filename);
	if(mode){
        	reverse(keys.begin(), keys.end());
		for(int i=0; i < inputContent.size(); i++){
			Decrypt(inputContent[i], keys);
			out << inputContent[i] << endl;
		}
	}
	else{
		for(int i=0; i < inputContent.size(); i++){
			Encrypt(inputContent[i], keys);
			out << inputContent[i] << endl;
		}
	}
	out.close();
	exit(0);
}
#endif
using namespace std;
void version_show()
{
#ifdef WIN32
	cout<<"OH Crytoservice System on Windows\n Vesion "<<version<<'\n';
	return;
#endif
#ifdef UNIX
	cout<<"OH Crytoservice System on Unix\nVesion "<<version<<'\n';
#endif
#ifdef Unknown
	cout<<"OH Crytoservice Systems\n Vesion "<<version<<'\n';
#endif
	exit(0);
}
int main(int argc, char* argv[]){
	string key;
	string data;
	srand(time(NULL));
#ifdef UNIX
	int next_option;
	const char* const short_options = "o:vhedi:k:";
	const struct option long_options[] = {
		{"help",0,NULL,'h'},
		{"encrypt",0,NULL,'e'},
		{"decrypt",0,NULL,'d'},
		//{"data",1,NULL,'D'},
		{"input",1,NULL,'i'},
		{"key",1,NULL,'k'},
		{"version",0,NULL,'v'},
		{"output",1,NULL,'o'},
		{NULL,0,NULL,0}
	};
	string input_filename = "";
	string output_filename = "";
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
		cerr<<"ERROR: Input file or output file undefine."<<endl;
		exit(0);
	}
	file_in_cs(mode,input_filename,key,output_filename);
#endif
	/*
	int _checkAlpha = 1;
	for(int a = 0;a < argc;a++){
		argvCheck(argv[a]);
	}
	if(ReadFile[0] == '\0'){
		_checkAlpha = 0;
	}
	if(_checkAlpha){
		FILE *file2 = fopen(ReadFile, "r");
		if(!file2) {
			printf("Error: Can not read the file.");
			return 1;
		}
		char dataINPUT[128];
		int gg__gg = 0;
		char ch;
		while((ch = fgetc(file2)) != EOF) {
			dataINPUT[gg__gg] = ch;
			++gg__gg;
		}
		data = dataINPUT;
	}
	*/
	//threadtest(version);
#ifdef WIN32
	ios_base::sync_with_stdio(false);
	string new_data = "";
	version_show();
	cout<<" Data:\n";
	getline(cin,data);
	cout<<" Key:"<<'\n';
	getline(cin,key);

	vector<char> keys;
	for (char &x : key) {
		keys.push_back(x);
	}
#endif
#ifdef UNIX
	/*
	if(mode){
		x.Decrypt(data, keys);
		cout<<data<<endl;
	}
	else{
		x.Encrypt(data, keys);
		cout<<data<<endl;
	}
	*/
#endif
#ifdef WIN32
	string Select;
	cout<<"[E]ncrypt or [D]ecrypt?\n";
	cin>>Select;

	if(Select == "E"){
		Encrypt(data, keys);
		printf("\nResult:\n");
		cout<<data<<endl;
	}
	else{
		reverse(keys.begin(), keys.end());
		Decrypt(data, keys);
		printf("\nResult:\n");
		cout<<data<<endl;
	}
	system("pause");
#endif


	//x.Decrypt(data, keys);
	//a.Encrypt("Hello",);

	return 0;
}
