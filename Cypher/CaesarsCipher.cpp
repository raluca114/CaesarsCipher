#include "CaesarsCipher.h"

CaesarsCipher::CaesarsCipher(std::string message, int key):
    m_message{message}, m_key{key}
{
}

void CaesarsCipher::setMessage(std::string message)
{
    m_message = message;
}

void CaesarsCipher::setKey(int key)
{
    m_key = key;
}

std::string CaesarsCipher::getMessage()
{
    return m_message;
}

int CaesarsCipher::getKey()
{
    return m_key;
}

std::string CaesarsCipher::encryptMessage()
{
    std::string encryptedMessage;
    while (m_message.size())
    {
        int letter;
        letter = int(m_message[0]);
        if (isLetter(letter))
        {
            if (letter + m_key < 122)
            {
                letter += m_key;
            }
            else
            {
                letter = ((letter + m_key) - 122)+97;
            }
            encryptedMessage += (char)letter;
        }
        else
        {
            encryptedMessage += m_message[0];
        }
        m_message.erase(0, 1);
    }
    return encryptedMessage;
}

std::string CaesarsCipher::decryptMessage()
{
    std::string decrypedMessage;
    while (m_message.size())
    {
        int letter;
        letter = (int)m_message[0];
        if (isLetter(letter))
        {
            if (letter - m_key >= 97)
            {
                letter -= m_key;
            }
            else
            {
                letter =122-( 97 - (letter - m_key));
            }
            decrypedMessage += (char)letter;
        }
        else
        {
            decrypedMessage += m_message[0];
        }
        m_message.erase(0, 1);
    }
    return decrypedMessage;
}

bool CaesarsCipher::isLetter(int letterASCII)
{
    return letterASCII >= 97 && letterASCII <= 122? true: false;
}
