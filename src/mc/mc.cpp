#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "des.h"

int main(int argc, char* argv[]){
	char ch;
	int count = 0;
	if(argc < 3 || argc > 4){
		std::cout << "OH DES" << std::endl
			 << " >> ohdes <enc/dec> <input filename> [output filename]" << std::endl;
		return 1;
	}
	int mode = 0;
	if(strcmp(argv[1],"enc") == 0){
		mode = 0;
	}
	else if(strcmp(argv[1],"dec") == 0){
		mode = 1;
	}
	else{
		std::cout << "FATAL: Mode Not Correct" << std::endl;
		return 2;
	}
	std::ifstream fin(argv[2], std::ios::binary);
	std::ofstream fout(argv[3], std::ios::binary);
	if(!fin){
		std::cout << "Cannot open the file" << std::endl;
		return -1;
	}
	if(!fout){
		std::cout << "Cannot open the file" << std::endl;
		return -1;
	}
	unsigned long long plaintext = 0;
	unsigned long long key;
	std::cout << "Enter Key: ";
	std::cin >> std::hex >> key;
	unsigned long long secret = 0;
	unsigned long long iv = 0;
	unsigned short int plaintextremain = 0;
	unsigned long long encrypedblocks = 0;
	des::cbc cbc(mode, key);
	if(mode == 1){
		fin.read((char*)&plaintextremain, sizeof(plaintextremain));
		fin.read((char*)&encrypedblocks, sizeof(encrypedblocks));
		fin.read((char*)&iv, sizeof(iv));
		cbc.setiv(iv);
	}
	else{
		iv = cbc.getiv();
		fout.write((char*)&plaintextremain, sizeof(plaintextremain));
		fout.write((char*)&encrypedblocks, sizeof(encrypedblocks));
		fout.write((char*)&iv, sizeof(iv));
		//Random iv
	}
	unsigned long long int count_while = 0;
	if(mode == 0){
		char* readpointer = (char*)&plaintext;
		while(fin.read(readpointer, sizeof(char))){
			count_while = (count_while + 1)%8;
			if(count_while == 0){
				++encrypedblocks;
				secret = cbc.Next(plaintext);
				readpointer -= 8;
				fout.write((char*)&secret, sizeof(secret));
				plaintext = 0;
			}
			secret = 0;
			++readpointer;	
		}

	}
	else if(mode == 1){
		while(fin.read((char*)&plaintext, sizeof(plaintext)) && count_while < encrypedblocks - 1 ){
			++count_while;
			secret = cbc.Next(plaintext);
			fout.write((char*)&secret, sizeof(secret));
		}
		secret = cbc.Next(plaintext);
		fout.write((char*)&secret, plaintextremain);
		
	}
	if(mode == 0 && count_while != 0){
		++encrypedblocks;
		secret = cbc.Next(plaintext);
		std::cout << std::setw(2) << std::hex << plaintext << std::endl;
		fout.write((char*)&secret, sizeof(secret));
	}
	plaintextremain = count_while;
	if(mode == 0){
		fout.seekp(0,std::ios::beg);
		fout.write((char*)&plaintextremain, sizeof(plaintextremain));
		fout.write((char*)&encrypedblocks, sizeof(encrypedblocks));
	}
	fin.close();
	fout.close();
	return 0;
}
