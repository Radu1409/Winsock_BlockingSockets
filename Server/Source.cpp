// Server Code

#include "IncludeMe.h"
#include <iostream>

int main()
{
	if (PNet::Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
	}
	PNet::Network::Shutdown();
	system("pause");
	return 0;

}