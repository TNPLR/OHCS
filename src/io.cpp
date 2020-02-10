#include "io.hpp"
#include <fstream>
#include <iterator>
#include <cstdint>

std::vector<ocss_t> get_data(std::string const& input_filename)
{
	std::ifstream in(input_filename);
	std::vector<ocss_t> result{std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
	in.close();
	return result;
}

void write_data(std::string const& output_filename, std::vector<ocss_t> const& data)
{
	std::ofstream out(output_filename, std::ios::binary);
	std::copy(data.cbegin(), data.cend(), std::ostreambuf_iterator<char>(out));
	out.close();
}

std::vector<std::vector<ocss_t> > get_ohformat(std::string const& input_filename)
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

void write_ohformat(std::string const& output_filename, std::vector<std::vector<ocss_t> > const& data)
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

