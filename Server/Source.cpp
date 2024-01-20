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

					std::string string1, string2, string3;
					PNet::Packet packet;
					while (true)
					{
						
						PNet::PResult result = newConnection.Recv(packet);
						if (result != PNet::PResult::P_Success)
							break;

						try
						{
							packet >> string1 >> string2 >> string3;
						}
						catch (PNet::PacketException& exception)
						{
							std::cout << exception.what() << std::endl;
							break;
						}
						std::cout << string1 << std::endl;
						std::cout << string2 << std::endl;
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