#pragma once
#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>

#pragma comment(lib, "Ws2_32.lib")
 
class DiffieHellmanKeyExchange
{
private:
	int m_X;
	int m_Y;
	int m_number;
	int m_root;
public:
	DiffieHellmanKeyExchange() = default;
	DiffieHellmanKeyExchange(int x, int y, int number, int root);

	int getX();
	int getY();
	int getNumber();
	int getRoot();

	void setX(int x);
	void setY(int y);
	void setNumber(int number);
	void setRoot(int root);

	void generateRandomX();
	void calculateY();
	int calculateKey(int y);

	bool validateNumberAndRoot(int number, int root);

	~DiffieHellmanKeyExchange() = default;
};

