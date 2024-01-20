// Server Code

#include "IncludeMe.h"
#include <iostream>


int main()
{
	if (PNet::Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;

		//Server to listen for connections on port 4790
		//Socket - bind to 4790

		/*PNet::IPEndpoint test("www.google.com", 8080);
		if (test.GetIPVersion() == PNet::IPVersion::IPv4)
		{
			std::cout << "Hostname: " << test.GetHostname() << std::endl;
			std::cout << "IP: " << test.GetIPString() << std::endl;
			std::cout << "Port: " << test.GetPort() << std::endl;
			std::cout << "IP Bytes.." << std::endl;
			for (auto& digit : test.GetIPBytes())
			{
				std::cout << (int)digit << std::endl;
			}
		}
		else
		{
			std::cerr << "This is not an ipv4 address." << std::endl;
		}*/
		PNet::Socket socket;
		if (socket.Create() == PNet::PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Listen(PNet::IPEndpoint("127.0.0.1", 4790)) == PNet::PResult::P_Success)
			{
				std::cout << "Socket successfully listening on port 4790" << std::endl;
				PNet::Socket newConnection;
				if (socket.Accept(newConnection) == PNet::PResult::P_Success)
				{
					std::cout << "New connection accepted." << std::endl;

					std::string buffer = "";
					int result = PNet::PResult::P_Success;
					while (result == PNet::PResult::P_Success)
					{
						uint32_t bufferSize = 0;
						result = newConnection.RecvAll(&bufferSize, sizeof(uint32_t));
						if (result != PNet::PResult::P_Success)
							break;

						bufferSize = ntohl(bufferSize);

						if (bufferSize > PNet::g_MaxPacketSize)
							break;


						buffer.resize(bufferSize);
						result = newConnection.RecvAll(&buffer[0], bufferSize);
						if (result != PNet::PResult::P_Success)
							break;

						std::cout << "[" << bufferSize << "] - " << buffer << std::endl;
					}

					newConnection.Close();
				}
				else
				{
					std::cerr << "Failed to accept new connection." << std::endl;
				}
			}
			else
			{
				std::cerr << "Failed to listen on port 4790." << std::endl;
			}
			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to created." << std::endl;
		}
	}
	PNet::Network::Shutdown();
	system("pause");
	return 0;

}