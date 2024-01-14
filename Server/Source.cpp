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
			if (socket.Bind(PNet::IPEndpoint("127.0.0.1", 4790)) == PNet::PResult::P_Success)
			{
				std::cout << "Socket successfully bound to port 4790" << std::endl;
			}
			else
			{
				std::cerr << "Failed to bind socket to port 4790." << std::endl;
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