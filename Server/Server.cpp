#include "Server.h"
#include <iostream>

bool Server::Initialize(IPEndpoint ip)
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

		listeningSocket = PNet::Socket(ip.GetIPVersion());
		if (listeningSocket.Create() == PNet::PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (listeningSocket.Listen(ip) == PNet::PResult::P_Success)
			{
				std::cout << "Socket successfully listening." << std::endl;
				return true;
			}
			else
			{
				std::cerr << "Failed to listen." << std::endl;
			}
			listeningSocket.Close();
		}
		else
		{
			std::cerr << "Socket failed to created." << std::endl;
		}
	}
	return false;
}

void Server::Frame()
{
	WSAPOLLFD listeningSocketFD = {};
	listeningSocketFD.fd = listeningSocket.GetHandle();
	listeningSocketFD.events = POLLRDNORM;
	listeningSocketFD.revents = 0;

	// In Linux environment, instead using WSAPOLL, we use poll
	if (WSAPoll(&listeningSocketFD, 1, 1) > 0)
	{
		if (listeningSocketFD.revents & POLLRDNORM)
		{
			PNet::Socket newConnectionSocket;
			IPEndpoint newConnectionEndpoint;
			if (listeningSocket.Accept(newConnectionSocket, &newConnectionEndpoint) == PNet::PResult::P_Success)
			{
				TCPConnection acceptedConnection(newConnectionSocket, newConnectionEndpoint);
				std::cout << acceptedConnection.ToString() << " - New connection accepted." << std::endl;
				acceptedConnection.Close();
			}
			else
			{
				std::cerr << "Failed to accept new connection." << std::endl;
			}
		}
	}

}
