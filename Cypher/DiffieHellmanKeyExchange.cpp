#include "DiffieHellmanKeyExchange.h"

DiffieHellmanKeyExchange::DiffieHellmanKeyExchange(int x, int y, int number, int root):
    m_X{x}, m_Y{y}, m_number{number}, m_root{root}
{
}

int DiffieHellmanKeyExchange::getX()
{
    return m_X;
}

int DiffieHellmanKeyExchange::getY()
{
    return m_Y;
}

int DiffieHellmanKeyExchange::getNumber()
{
    return m_number;
}

int DiffieHellmanKeyExchange::getRoot()
{
    return m_root;
}

void DiffieHellmanKeyExchange::setX(int x)
{
    m_X = x;
}

void DiffieHellmanKeyExchange::setY(int y)
{
    m_Y = y;
}

void DiffieHellmanKeyExchange::setNumber(int number)
{
    m_number = number;
}

void DiffieHellmanKeyExchange::setRoot(int root)
{
    m_root = root;
}

void DiffieHellmanKeyExchange::generateRandomX()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(1, m_number-1);

    setX(distr(gen));
}

void DiffieHellmanKeyExchange::calculateY()
{
    generateRandomX();
    int power = pow(m_root, m_X);
    setY(power % m_number);
}

int DiffieHellmanKeyExchange::calculateKey(int y)
{
    int power = pow(y, m_Y);
    return power % m_number;
}

bool DiffieHellmanKeyExchange::validateNumberAndRoot(int number, int root)
{
    std::vector<bool> results;
    for (int index=1; index<=number; index++)
    {
        results.push_back(false);
    }
    int power = 1;
    while (power<number)
    {
        int result = (int)pow(root, power) % number;
        if (results[result] == false)
        {
            results[result] = true;
        }
        else
        {
            return false;
        }
        power++;
    }
    if (std::find(results.begin(), results.end(), false) != results.end())
    {
        return true;
        setNumber(number);
        setRoot(root);
    }
    return false;
}
