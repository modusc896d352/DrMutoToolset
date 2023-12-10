#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "1.hpp"

/*
char r_ffunc::read_s8(long offset, std::ifstream &input_file)
{
    input_file.seekg(offset, std::ios_base::beg);
    std::vector<char> btr1(1);
    input_file.read(reinterpret_cast<char*>(btr1.data()), 1);
    return (char)btr1[0];
}
*/

unsigned char r_ffunc::read_u8(long offset, std::ifstream &input_file)
{
	input_file.seekg(offset, std::ios_base::beg);
	std::vector<char> btr1(1);
	input_file.read(reinterpret_cast<char*>(btr1.data()), 1);
	return (unsigned char)btr1[0];
}

unsigned char r_ffunc::read_u8_from_mem(long offset, std::vector<char> input_data)
{
    return (unsigned char)input_data.at(offset);
}

void r_ffunc::put_u8_to_mem(unsigned char target_var, long offset, std::vector<char>& input_data)
{
    std::vector<char>::iterator id_iter;
    id_iter = input_data.begin();
    input_data.emplace(id_iter + offset, target_var);
    input_data.pop_back();
}

short r_ffunc::read_s16le_from_mem(long offset, std::vector<char> input_data)
{
    unsigned char a1 = input_data.at(offset + 0);
    char a2 = input_data.at(offset + 1);
    short a3 = (a1) | (a2 << 8);
    return a3;
}

unsigned short r_ffunc::read_u16le_from_mem(long offset, std::vector<char> input_data)
{
    unsigned char a1 = input_data.at(offset + 0);
    unsigned char a2 = input_data.at(offset + 1);
    unsigned a3 = (a1) | (a2 << 8);
    return a3;
}

short r_ffunc::read_s16be_from_mem(long offset, std::vector<char> input_data)
{
    char a1 = input_data.at(offset + 0);
    unsigned char a2 = input_data.at(offset + 1);
    short a3 = (a1 << 8) | (a2);
    return a3;
}

unsigned short r_ffunc::read_u16be_from_mem(long offset, std::vector<char> input_data)
{
    unsigned char a1 = input_data.at(offset + 0);
    unsigned char a2 = input_data.at(offset + 1);
    unsigned a3 = (a1 << 8) | (a2);
    return a3;
}

long r_ffunc::read_s32le_from_mem(long offset, std::vector<char> input_data)
{
    unsigned char a1 = input_data.at(offset + 0);
    unsigned char a2 = input_data.at(offset + 1);
    unsigned char a3 = input_data.at(offset + 2);
    char a4 = input_data.at(offset + 3);
    long a5 = (a1) | (a2 << 8) | (a3 << 16) | (a4 << 24);
    return a5;
}

unsigned long r_ffunc::read_u32le_from_mem(long offset, std::vector<char> input_data)
{
    unsigned char a1 = input_data.at(offset + 0);
    unsigned char a2 = input_data.at(offset + 1);
    unsigned char a3 = input_data.at(offset + 2);
    unsigned char a4 = input_data.at(offset + 3);
    unsigned long a5 = (a1) | (a2 << 8) | (a3 << 16) | (a4 << 24);
    return a5;
}
