#pragma once

#include <kissnet.hpp>
#include <c_decrypter_mamarra.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

namespace kn = kissnet;

#define REAL_ENDPOINT "0.0.0.0:10012"
#define AXESO5_ENDPOINT "0.0.0.0:10012"
#define NMB_RND_ENDPOINT "0.0.0.0:10013"

class ServerRosh
{

private:
	std::map<std::string, int> rndNmb;
	std::vector<uint8_t> payload_1;
	std::vector<uint8_t> payload_2;
	std::vector<uint8_t> payload_3;
	std::vector<uint8_t> payload_4;
	std::vector<uint8_t> payload_5;
	std::vector<uint8_t> payload_6;
	std::vector<uint8_t> payload_7;
	std::vector<uint8_t> payload_8;
	std::vector<uint8_t> payload_9;
	std::vector<uint8_t> payload_A;


public:
	void srv_nmb_rnd();
	int decrypt_packet(kn::buffer<9216> static_buffer, std::string ipv4);
	
	void set_payload(std::vector<uint8_t> arg0, int flag)
	{
		switch (flag)
		{
			case 0x1:
				payload_1 = arg0;
			break;

			case 0x2:
				payload_2 = arg0;
			break;

			case 0x3:
				payload_3 = arg0;
			break;

			case 0x4:
				payload_4 = arg0;
			break;

			case 0x5:
				payload_5 = arg0;
			break;

			case 0x6:
				payload_6 = arg0;
			break;

			case 0x7:
				payload_7 = arg0;
			break;

			case 0x8:
				payload_8 = arg0;
			break;

			case 0x9:
				payload_9 = arg0;
			break;

			case 0xA:
				payload_A = arg0;
			break;
		}
	};

	void srv_real_server();
	void proxy();
};

