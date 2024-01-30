// Client Code

#include "Client.h"
#include <iostream>

int main()
{
	Client client;
	if (client.Connect(IPEndpoint("::1", 6112)))
	{
		while (client.IsConnected())
		{
			client.Frame();
		}
	}
	PNet::Network::Shutdown();
	system("pause");
	return 0;

}