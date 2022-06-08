#include "DiffieHellmanKeyExchange.h"
#include "CaesarsCipher.h"

#include <winsock2.h>	
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[])
{

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		std::cout << "WSAStartup failed: %d\n" << iResult;
		return 1;
	}

	SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): %ld\n" << WSAGetLastError();
		WSACleanup();
		return 1;
	}

	addrinfo* result = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;

#define DEFAULT_PORT "27015"

	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		std::cout << "getaddrinfo failed: %d\n" << iResult;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}


	iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return 1;
	}


#define DEFAULT_BUFLEN 512

	DiffieHellmanKeyExchange exchange;
	int number, root;
	bool validation = true;
	do 
	{
		std::cout << "Please insert the number: ";
		std::cin >> number;
		std::cout << "Please insert the root:";
		std::cin >> root;
		validation = exchange.validateNumberAndRoot(number, root);
	} while (!validation);

	exchange.setNumber(number);
	exchange.setRoot(root);
	exchange.calculateY();
	std::vector<std::string> elements;
	elements.emplace_back(std::to_string(number));
	elements.emplace_back(std::to_string(root));
	elements.emplace_back(std::to_string(exchange.getY()));


	std::cout << "Sending number: " << elements[0] << "\n";
	const char* sendbuf = elements[0].c_str(); 
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	std::cout << "Sending root: " << elements[1] << "\n";
	sendbuf = elements[1].c_str(); 
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	std::cout << "Sending Y: " << elements[2] << "\n";
	sendbuf = elements[2].c_str(); 
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);


	
	std::string message;
	int key,y;
	char recvbuf[DEFAULT_BUFLEN];
	int iRecvResult, iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;
	memset(recvbuf, 0, sizeof(recvbuf));
	iRecvResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	std::string recievedMessage = recvbuf;
	std::cout << "\nRecieved: "<<recievedMessage<<"\n";
	y = std::stoi(recievedMessage);
	std::cout << "X is: " << exchange.getX()<<std::endl;
	key = std::stoi(recievedMessage);
	std::cout << "The key is: "<<key<<std::endl;

	do
	{
		std::cout << "Please insert the message you want to be sent: ";
		std::getline(std::cin, message);
		if (message != "Close connection")
		{
			CaesarsCipher cipher;
			cipher.setKey(key);
			cipher.setMessage(message);
			std::string encryptedMessage = cipher.encryptMessage();
			const char* sendbuf = encryptedMessage.c_str(); 
			iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		}
		std::cout<<std::endl;
	} while (message != "Close connection");

	if (iResult == SOCKET_ERROR)
	{
		std::cout << "send failed: %d\n" << WSAGetLastError();
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "shutdown failed: %d\n" << WSAGetLastError();
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	closesocket(ConnectSocket);
	WSACleanup();

	return 0;

}