#include "ServerRosh.h"

void ServerRosh::srv_nmb_rnd()
{

	kn::socket<kissnet::protocol::tcp> server(kn::endpoint(NMB_RND_ENDPOINT));
	kn::buffer<64> static_buffer;
	kn::endpoint endpnt;
	std::string ip_client;
	std::string d;
	int magic_rand;
	std::stringstream ss;
	server.bind();
	server.listen();

	while (1)
	{
		kn::socket client = server.accept();

		const auto [data_size, status_code] = client.recv(static_buffer);

		if (data_size < static_buffer.size())
			static_buffer[data_size] = std::byte{ '\0' };

		endpnt = client.get_bind_loc();
		ip_client = endpnt.address;
		d = reinterpret_cast<const char*>(static_buffer.data());
		ss << d;
		ss >> magic_rand;

		rndNmb[ip_client] = magic_rand;

		client.close();
	}

}


int ServerRosh::decrypt_packet(kn::buffer<9216> static_buffer, std::string ipv4)
{

	c_decrypter_mamarra decryptor;
	std::vector<int> buffRecv;
	std::vector<int> plain_text;
	int a3_max_len = decryptor.get_len_max();
	int a1_max_len = a3_max_len - 0x5;

	decryptor.set_bytes_recv(buffRecv);
	decryptor.rand(rndNmb[ipv4]);
	decryptor.decrypt_data();
	plain_text = decryptor.get_plain_text();

	return 0x0;
}


void ServerRosh::srv_real_server()
{
	// Setup socket
	kn::socket<kissnet::protocol::tcp> server(kn::endpoint(REAL_ENDPOINT));
	server.bind();
	server.listen();

	// Buffer vectors
	kn::buffer<9216> recv_pack_1;
	kn::buffer<9216> recv_pack_2;
	kn::buffer<9216> recv_pack_3;
	kn::buffer<9216> recv_pack_4;
	kn::buffer<9216> recv_pack_5;
	kn::buffer<9216> recv_pack_6;
	kn::buffer<9216> recv_pack_7;
	kn::buffer<9216> recv_pack_8;
	kn::buffer<9216> recv_pack_9;
	kn::buffer<9216> recv_pack_A;

	/*
	std::string test_first_auth_client = "C:\\Users\\opensylar\\Desktop\\karos\\dump-net\\recv\\tests\\first_resend_package.raw";
	std::string first_response_server = "C:\\Users\\opensylar\\Desktop\\karos\\dump-net\\recv\\first_resend_package_from_axeso5.raw";

	std::string test_second_response_client = "C:\\Users\\opensylar\\Desktop\\karos\\dump-net\\recv\\tests\\second_resend_package_from_client.raw";
	std::string second_response_server = "C:\\Users\\opensylar\\Desktop\\karos\\dump-net\\recv\\second_resend_package_from_axeso5.raw";
	*/

	while (1)
	{
		kn::socket client = server.accept();

		// Recv first package
		const auto [data_size1, status_code1] = client.recv(recv_pack_1);
		client.send(reinterpret_cast<const std::byte*>(payload_1.data()), payload_1.size());

		// Recv second package
		const auto [data_size2, status_code2] = client.recv(recv_pack_2);
		client.send(reinterpret_cast<const std::byte*>(payload_2.data()), payload_2.size());

		// Recv thrid package
		const auto [data_size3, status_code3] = client.recv(recv_pack_3);
		client.send(reinterpret_cast<const std::byte*>(payload_3.data()), payload_3.size());

		// Recv ??? package
		const auto [data_size4, status_code4] = client.recv(recv_pack_4);
		client.send(reinterpret_cast<const std::byte*>(payload_4.data()), payload_4.size());

		// Recv ??? package
		const auto [data_size5, status_code5] = client.recv(recv_pack_5);
		client.send(reinterpret_cast<const std::byte*>(payload_5.data()), payload_5.size());

		// Recv ??? package
		const auto [data_size6, status_code6] = client.recv(recv_pack_6);
		client.send(reinterpret_cast<const std::byte*>(payload_6.data()), payload_6.size());

		// Recv ??? package
		// const auto [data_size7, status_code7] = client.recv(recv_pack_7);
		// client.send(reinterpret_cast<const std::byte*>(payload_7.data()), payload_7.size());

		// Recv ??? package
		// const auto [data_size8, status_code8] = client.recv(recv_pack_8);
		// client.send(reinterpret_cast<const std::byte*>(payload_8.data()), payload_8.size());

	} // end while

}


void ServerRosh::proxy()
{
	// Setup socket
	kn::socket<kissnet::protocol::tcp> server(kn::endpoint(REAL_ENDPOINT));
	server.bind();
	server.listen();
	std::vector<uint8_t> out_buffer;
	int flagPacket;
	kn::buffer<9216> static_buffer;
	std::string str_ipv4;
	std::string first_resend_package = "C:\\Users\\opensylar\\Desktop\\karos\\dump-net\\recv\\first_resend_package.raw";

	while (1)
	{
		kn::socket client = server.accept();

		// Recv first_resend_package from client Rosh
		const auto [data_size, status_code] = client.recv(static_buffer);

		// Save first_resend_package from client Rosh
		std::ofstream(first_resend_package, std::ios::binary).write(reinterpret_cast<const char*>(static_buffer.data()), data_size);

		// Create a kissnet tcp to resend packet to Axeso5
		kn::tcp_socket a_socket(kn::endpoint("34.197.184.173:10012"));
		a_socket.connect();

		kn::buffer<4096> static_buffer;

		Sleep(1000);

		if (a_socket.bytes_available() == 0x0)
		{
			a_socket.close();
			return;
		}

		// Send first_resend_package to Axeso5 server
		a_socket.send(reinterpret_cast<const std::byte*>(static_buffer.data()), static_buffer.size());

		// Recv response first_resend_package from Axeso5 server
		kn::buffer<9096> static_buffer1;
		const auto [data_size1, status_code1] = a_socket.recv(static_buffer1);

		// Save response first_resend_package from Axeso5 server
		std::string first_resend_package_from_axeso5 = "C:\\Users\\opensylar\\Desktop\\karos\\dump-net\\recv\\first_resend_package_from_axeso5.raw";
		std::ofstream(first_resend_package_from_axeso5, std::ios::binary).write(reinterpret_cast<const char*>(static_buffer1.data()), data_size1);

		// Recv response second_resend_package from Axeso5 server
		kn::buffer<9096> static_buffer2;
		const auto [data_size2, status_code2] = a_socket.recv(static_buffer2);

		// Save response second_resend_package from Axeso5 server
		std::string second_resend_package_from_axeso5 = "C:\\Users\\opensylar\\Desktop\\karos\\dump-net\\recv\\second_resend_package_from_axeso5.raw";
		std::ofstream(second_resend_package_from_axeso5, std::ios::binary).write(reinterpret_cast<const char*>(static_buffer2.data()), data_size2);

		// Send first_resend_package to client Rosh
		client.send(reinterpret_cast<const std::byte*>(static_buffer2.data()), static_buffer2.size());

		return;
	}
}
