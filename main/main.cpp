





/*
	Copyright (C) 2017 CHAW-HUNG, HSIAO

---------------------------------------------------------------------------------------------------------------
	This file is part of Ollolol and Hsiaosvideo Cryptography System.

	Ollolol and Hsiaosvideo Cryptography System is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	Ollolol and Hsiaosvideo Cryptography System is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Ollolol and Hsiaosvideo Cryptography System.  If not, see <http://www.gnu.org/licenses/>.
*/
/* 
  This is the main file of OHCS
  Made by Hsiaosvideo
  2017/07/21
*/
#include "main.hpp"
#include "argv.hpp"
char file = 0;
char R[100];
char *ReadFile = R;

#include <fstream>
#include "OCSS.hpp"
//#include <thread>
#include <unistd.h>
#include <getopt.h>
const char* program_name;
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
using namespace std;
void version_show(const string version)
{
	cout<<" Ollolol and Hsiaosvideo Crytoservice System\n Vesion "<<version<<'\n';
	exit(0);
}
int main(int argc, char* argv[]){
	string key;
	string data;
	int next_option;
	const char* const short_options = "vhedD:i:k:";
	const struct option long_options[] = {
		{"help",0,NULL,'h'},
		{"encrypt",0,NULL,'e'},
		{"decrypt",0,NULL,'d'},
		{"data",1,NULL,'D'},
		{"input",1,NULL,'i'},
		{"key",1,NULL,'k'},
		{"version",0,NULL,'v'},
		{NULL,0,NULL,0}
	};
	const string version = "1.1";
	const char* input_filename = NULL;
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
			case 'D':
				data = optarg;
				
				break;
			case 'e':
				mode = 0;
				break;
			case 'k':
				key = optarg;
				break;
			case 'v':
				version_show(version);
			case '?': /* The user specified an invalid option. */
				print_usage (stderr, 1);
			case -1:
				break;
			default:
				abort();
		}
	}while(next_option != -1);
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
	ios_base::sync_with_stdio(false);
	string new_data = "";
	OCSS x;

	//getline(cin,key);
	/*
	if(_checkAlpha)
		cout<<"data: "<<data<<'\n';
	else{
		cout<<" Data:\n";
		getline(cin,data);
	}
	cout<<" Key:"<<'\n';
	
	*/
	vector<char> keys;
	for (char &x : key) {
		keys.push_back(x);
	}
	if(mode){
		x.Decrypt(data, keys);
		cout<<data<<endl;
	}
	else{
		x.Encrypt(data, keys);
		cout<<data<<endl;
	}
	/*
	string Select;
	cout<<"[E]ncrypt or [D]ecrypt?\n";
	cin>>Select;

	if(Select == "E"){
		x.Encrypt(data, keys);
		printf("\nResult:\n");
		cout<<data<<endl;
	}
	else if(Select == "ED"){
		time_t start, end;
		start = time(NULL);
		x.Encrypt(data, keys);
		end = time(NULL);
		double diff = difftime(end, start);
		printf("\nResult:\n");

		printf("Time = %f\n", diff);
		cout<<data<<endl;
	}
	else if(Select == "DD"){
		x.Decrypt(data, keys);
		printf("\nResult:\n");
		cout<<data<<endl;
	}
	else{
		x.Decrypt(data, keys);
		printf("\nResult:\n");
		cout<<data<<endl;
	}
	*/


	//x.Decrypt(data, keys);
	//a.Encrypt("Hello",);

	return 0;
}
