#pragma once

#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <Windows.h>
#include <fstream>

#pragma comment(lib, "Winmm.lib")

class util
{

public:
    std::map<char, int> idiv(int num, int denom);
	int gen_random(int max);
	void sleep(int milis);
	bool load_bin(const std::string& file_path, std::vector<uint8_t>* out_buffer);
	int block_despues_rand(int val_rand);
	int print_vector(std::vector<int> arg0);
	int get_data_len(std::vector<uint8_t> data);

	inline int Movzx8(int dat) { return ((dat & 0x80) << 0) | (dat & 0x7F); }
};

