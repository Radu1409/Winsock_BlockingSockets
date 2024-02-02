// Server Code

#include "MyServer.h"
#include <iostream>



int main()
{
	MyServer server;
	if (server.Initialize(IPEndpoint("::", 6112)))
	{
		while (true)
		{
			server.Frame();
		}
	}
	PNet::Network::Shutdown();
	system("pause");
	return 0;

}