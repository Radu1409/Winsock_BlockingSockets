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

				std::string buffer = "";
				buffer.resize(PNet::g_MaxPacketSize + 1);
				memset(&buffer[0], 'A', PNet::g_MaxPacketSize + 1);
				while (true)
				{
					uint32_t bufferSize = buffer.size();
					bufferSize = htonl(bufferSize);
					int result = socket.SendAll(&bufferSize, sizeof(uint32_t));
					if (result != PNet::PResult::P_Success)
						break;

					
					result = socket.SendAll(buffer.data(), buffer.size());
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