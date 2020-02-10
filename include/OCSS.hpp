#ifndef OCSS_H
#define OCSS_H
#include <vector>
typedef unsigned char ocss_t;

namespace OCSS {
std::vector<ocss_t> Encrypt(std::vector<ocss_t> Data,std::vector<ocss_t> const& Key);
void Decrypt(std::vector<ocss_t>& Data,std::vector<ocss_t> const& Key);
}
#endif // OCSS_H
