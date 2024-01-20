// Server Code

#include "IncludeMe.h"
#include <iostream>

bool ProcessPacket(PNet::Packet& packet)
{
	switch (packet.GetPacketType())
	{
	case PNet::PacketType::PT_ChatMessage:
	{
		std::string chatmessage;
		packet >> chatmessage;
		std::cout << "ChatMessage: " << chatmessage << std::endl;
		break;
	}
	case PNet::PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		packet >> arraySize;
		std::cout << "Array Size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			packet >> element;
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	default:
		return false;
	}
	return true;
}

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
		PNet::Socket socket(PNet::IPVersion::IPv6);
		if (socket.Create() == PNet::PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Listen(PNet::IPEndpoint("::1", 4790)) == PNet::PResult::P_Success)
			{
				std::cout << "Socket successfully listening on port 4790" << std::endl;
				PNet::Socket newConnection;
				if (socket.Accept(newConnection) == PNet::PResult::P_Success)
				{
					std::cout << "New connection accepted." << std::endl;

					
					PNet::Packet packet;
					while (true)
					{
						
						PNet::PResult result = newConnection.Recv(packet);
						if (result != PNet::PResult::P_Success)
							break;

						if (!ProcessPacket(packet))
							break;
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