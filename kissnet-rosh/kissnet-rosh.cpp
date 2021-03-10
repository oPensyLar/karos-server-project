#include "ServerRosh.h"
#include <Windows.h>
#include <hazekaros.h>

void deploy_proxy()
{
	ServerRosh srv_rosh;
	srv_rosh.proxy();
}

DWORD WINAPI deploy_nmb_rnd_server(LPVOID lpThreadParameter)
{

	ServerRosh srv_rosh;
	srv_rosh.srv_nmb_rnd();

	return 0x0;
}


DWORD WINAPI deploy_real_server(LPVOID lpThreadParameter)
{
	ServerRosh srv_rosh;
	util u;
	std::vector<uint8_t> p1, p2, p3, p4, p5, p6, p7, p8, p9, pa;
	
	u.load_bin("any_path\\dump-net\\pcaps\\raw\\2\\1.bin", &p1);
	u.load_bin("any_path\\dump-net\\pcaps\\raw\\2\\2.bin", &p2);
	u.load_bin("any_path\\dump-net\\pcaps\\raw\\2\\3.bin", &p3);
	u.load_bin("any_path\\dump-net\\pcaps\\raw\\2\\4.bin", &p4);
	u.load_bin("any_path\\dump-net\\pcaps\\raw\\2\\5.bin", &p5);
	u.load_bin("any_path\\dump-net\\pcaps\\raw\\2\\6.bin", &p6);

	// u.load_bin("any_path\\dump-net\\pcaps\\7.bin", &p7);
	// u.load_bin("any_path\\dump-net\\pcaps\\8.bin", &p8);
	// u.load_bin("any_path\\dump-net\\pcaps\\9.bin", &p9);
	// u.load_bin("any_path\\dump-net\\pcaps\\pa.bin", &pa);

	srv_rosh.set_payload(p1, 0x1);
	srv_rosh.set_payload(p2, 0x2);
	srv_rosh.set_payload(p3, 0x3);
	srv_rosh.set_payload(p4, 0x4);
	srv_rosh.set_payload(p5, 0x5);
	srv_rosh.set_payload(p6, 0x6);

	// srv_rosh.set_payload(p7, 0x7);
	// srv_rosh.set_payload(p8, 0x8);

	// srv_rosh.set_payload(p9, 0x9);
	// srv_rosh.set_payload(pa, 0xA);

	srv_rosh.srv_real_server();

	return 0x0;
}

/*
void open_binary_file(const std::string& file, std::vector<uint8_t>& data)
{
	std::ifstream file_stream(file, std::ios::binary);
	file_stream.unsetf(std::ios::skipws);
	file_stream.seekg(0, std::ios::end);

	const auto file_size = file_stream.tellg();

	file_stream.seekg(0, std::ios::beg);
	data.reserve(static_cast<uint32_t>(file_size));
	data.insert(data.begin(), std::istream_iterator<uint8_t>(file_stream), std::istream_iterator<uint8_t>());
}
 
*/

int deploy_client()
{
	//Create a kissnet tcp over ssl ipv4 socket
	kn::tcp_socket a_socket(kn::endpoint("34.197.184.173:10012"));
	a_socket.connect();

	kn::buffer<4096> static_buffer;

	// Useless wait, just to show how long the response was
	Sleep(1000);

	if (a_socket.bytes_available() == 0x0)
	{
		a_socket.close();
		return -1;
	}

	std::cout << "bytes available to read : " << a_socket.bytes_available() << '\n';

	// Recv before login
	const auto [data_size, status_code] = a_socket.recv(static_buffer);

	std::string f_name_recv = "any_path\\dump-net\\recv\\real-before-login-proof0xE.raw";
	std::ofstream(f_name_recv, std::ios::binary).write(reinterpret_cast<const char*>(static_buffer.data()), data_size);

	// Load auth0
	std::string f_name_snd1 = "any_path\\dump-net\\recv\\real-client-auth0xE.raw";
	std::ifstream file_ifstream(f_name_snd1, std::ios::binary);

	if (!file_ifstream)
		return false;

	std::vector<uint8_t> out_buffer;
	out_buffer.assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
	file_ifstream.close();

	// Send auth0
	a_socket.send(reinterpret_cast<const std::byte*>(out_buffer.data()), out_buffer.size());

	// Recv response after login
	kn::buffer<9096> static_buffer1;
	const auto [data_size1, status_code1] = a_socket.recv(static_buffer1);

	// Save response server after login
	std::string f_nam_after_login_packet = "any_path\\dump-net\\recv\\real-after-del-auth-proof0xE.raw";
	std::ofstream(f_nam_after_login_packet, std::ios::binary).write(reinterpret_cast<const char*>(static_buffer1.data()), data_size1);

	return 0x0;
}


int main()
{

	// deploy_offline_tests();
	// return 0x0;

	/*
		std::vector<uint8_t> rawResp;
		std::string file_path = "any_path\\wsarecv\\data\\hexa\\old\\09-21-20 14.20.09-clone.raw";
		OpenBinaryFile(file_path.c_str(), rawResp);
	*/

	// deploy_proxy();

	CreateThread(NULL, NULL, deploy_real_server, NULL, NULL, NULL);
	// CreateThread(NULL, NULL, deploy_nmb_rnd_server, NULL, NULL, NULL);	

	// deploy_client();

	while (1) 
		Sleep(10);

	return 0;

}
