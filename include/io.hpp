#ifndef IO_H_
#define IO_H_
#include "OCSS.hpp"
#include <vector>
#include <string>
std::vector<ocss_t> get_data(std::string const& input_filename);
void write_data(std::string const& output_filename, std::vector<ocss_t> const& data);
void write_ohformat(std::string const& output_filename, std::vector<std::vector<ocss_t> > const& data);
std::vector<std::vector<ocss_t> > get_ohformat(std::string const& input_filename);
#endif // IO_H_
