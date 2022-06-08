#pragma once
#include <iostream>
#include <string>

class CaesarsCipher
{
private:
	std::string m_message;
	int m_key;
public:
	CaesarsCipher() = default;
	CaesarsCipher(std::string message, int key);

	void setMessage(std::string message);
	void setKey(int key);

	std::string getMessage();
	int getKey();

	std::string encryptMessage();
	std::string decryptMessage();

	bool isLetter(int letterASCII);

	~CaesarsCipher() = default;
};

