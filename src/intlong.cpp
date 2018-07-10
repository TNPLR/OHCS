/*
 *	Int 64 bits written by Hsiaosvideo.
 *	The program is to store 64 bits unsigned interger
 *	in 32 bits computer.
 */

#include <ostream>
#include <iostream>
class intlong{
public:
	intlong();
	intlong(unsigned int init);
	unsigned int ToUint();
	unsigned long long ToULLong();
	void block(const int);
	void operator=(const intlong&);
	void operator=(const int);
	void operator=(const long int);
	void operator=(const unsigned int);
	unsigned int GetBigEnd();
	unsigned int GetLittleEnd();
	void operator<<=(const int);
	void operator>>=(const int);
	intlong operator<<(const int);
	intlong operator>>(const int);
	intlong operator&(const int);
	intlong operator|(const int);
	intlong operator&(const intlong&);
	intlong operator|(const intlong&);
	void operator&=(const int);
	void operator|=(const int);
	void operator&=(const intlong&);
	void operator|=(const intlong&);
	void operator^=(const intlong&);
	//~intlong();
	friend std::ostream& operator<<(std::ostream& os, const intlong& il);
private:
	unsigned int* intarray;
	int length;
};
unsigned long long intlong::ToULLong(){
	return ((unsigned long long)(this->intarray[0])<<32|this->intarray[1]);
}
void intlong::block(const int a){
	if (a == 32){
		this->intarray[0] &= (0xFFFFFFFF);
	}
	else{
		this->intarray[0] = 0;
	}
}
intlong::intlong(unsigned int init){
	this->intarray = new unsigned[2];
	this->intarray[0] = 0;
	this->intarray[1] = init;
}
unsigned int intlong::ToUint(){
	return this->intarray[1];
}
void intlong::operator^=(const intlong& in){
	this->intarray[0] ^= in.intarray[0];
	this->intarray[1] ^= in.intarray[1];
}
void intlong::operator&=(const intlong& in){
	this->intarray[0] &= in.intarray[0];
	this->intarray[1] &= in.intarray[1];
}
void intlong::operator|=(const intlong& in){
	this->intarray[0] |= in.intarray[0];
	this->intarray[1] |= in.intarray[1];
}
void intlong::operator&=(const int in){
	this->intarray[1] &= in;
	this->intarray[0] = 0;
}

void intlong::operator|=(const int in){	
	this->intarray[1] |= in;
}
intlong intlong::operator&(const intlong& in){
	intlong tmp;
	tmp = *this;
	tmp &= in;
	return tmp;
}
intlong intlong::operator|(const intlong& in){
	intlong tmp;
	tmp = *this;
	tmp |= in;
	return tmp;
}
intlong intlong::operator&(const int in){
	intlong tmp;
	tmp.intarray[0] = 0;
	tmp.intarray[1] = this->intarray[1] & in;
	return tmp;
}
intlong intlong::operator|(const int in){
	intlong tmp;
	tmp = *this;
	tmp.intarray[1] |= in;
	return tmp;
}
intlong intlong::operator<<(const int ls){
	intlong tmp;
	tmp.intarray[0] = this->intarray[0] << ls;
	tmp.intarray[0] |= this->intarray[1]>>(32-ls);
	tmp.intarray[1] = this->intarray[1] << ls;
	return tmp;
}
intlong intlong::operator>>(const int rs){
	intlong tmp;
	tmp.intarray[1] = this->intarray[1] >> rs;
	tmp.intarray[1] |= this->intarray[0]<<(32-rs);
	tmp.intarray[0] = this->intarray[0] >> rs;
	return tmp;
}
void intlong::operator<<=(const int ls){
	this->intarray[0] <<= ls;
	this->intarray[0] |= this->intarray[1]>>(32-ls);
	this->intarray[1] <<= ls;
}
void intlong::operator>>=(const int rs){	
	this->intarray[1] >>= rs;
	this->intarray[1] |= this->intarray[0]<<(32-rs);
	this->intarray[0] >>= rs;
}

unsigned int intlong::GetBigEnd(){
	return this->intarray[0];
}
unsigned int intlong::GetLittleEnd(){
	return this->intarray[1];
}
void intlong::operator=(const int in){
	this->intarray[0] = 0;
	this->intarray[1] = in;
}
void intlong::operator=(const unsigned int in){
	this->intarray[0] = 0;
	this->intarray[1] = in;
}
void intlong::operator=(const long int in){
	this->intarray[0] = (unsigned int)(in>>32);
	this->intarray[1] = (unsigned int)(in&0xFFFFFFFF);
}
intlong::intlong(){
	this->intarray = new unsigned[2];
}
/*
intlong::~intlong(){
	delete [] this->intarray;
}
*/
void intlong::operator=(const intlong& input){
	this->intarray[0] = input.intarray[0];
	this->intarray[1] = input.intarray[1];
}
std::ostream& operator<<(std::ostream& os, const intlong& il){
	os << ((unsigned long long)(il.intarray[0])<<32|il.intarray[1]);
	return os;
}
/*
int main(){
	intlong a;
	a = 12;
	std::cout<<a<<std::endl;
	return 0;
}
*/
