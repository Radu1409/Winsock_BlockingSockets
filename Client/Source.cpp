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
				char buffer[256];
				strcpy_s(buffer, "Hello world from client!\0");
				int result = PNet::PResult::P_Success;
				while (result == PNet::PResult::P_Success)
				{
					result = socket.SendAll(buffer, 256);
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