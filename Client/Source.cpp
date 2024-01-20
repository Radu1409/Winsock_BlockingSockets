// Client Code

#include "IncludeMe.h"
#include <iostream>


int main()
{
	if (PNet::Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
		PNet::Socket socket;
		if (socket.Create() == PNet::PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(PNet::IPEndpoint("127.0.0.1", 4790)) == PNet::PResult::P_Success)
			{
				std::cout << "Successfully connected to server!" << std::endl;

				PNet::Packet stringPacket(PNet::PacketType::PT_ChatMessage);
				stringPacket << std::string("This is my string packet!");

				PNet::Packet integersPacket(PNet::PacketType::PT_IntegerArray);
				uint32_t arraySize = 6;
				uint32_t integerArray[6] = { 2, 5, 7, 1, 2, 9 };
				integersPacket << arraySize;
				for (auto integer : integerArray)
				{
					integersPacket << integer;
				}
				while (true)
				{
					PNet::PResult result;

					if (rand() % 2 == 0)
					{
						result = socket.Send(stringPacket);
					}
					else
					{
						result = socket.Send(integersPacket);
					}
					if (result != PNet::PResult::P_Success)
						break;

					std::cout << "Attempting to send chunk of data..." << std::endl;
					Sleep(500);
				}
			}
			else
			{
				std::cerr << "Failed to connect to server." << std::endl;
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