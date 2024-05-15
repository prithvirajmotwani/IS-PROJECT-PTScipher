#include "Key.h"
#include <array>
#include <random>
#include <stdexcept>
#include <stdint.h>



uint32_t randomUInt(uint32_t lowerLimit, uint32_t upperLimit)
{
    std::random_device rd;
    std::uniform_int_distribution<uint32_t> dist(lowerLimit, upperLimit);
    return dist(rd);
}



void Key::generateRandomKey() 
{
    for (uint8_t i = 0; i < this->key.size(); i++) {
        this->key[i] = randomUInt(1, UINT32_MAX);
    }
}


void Key::setKey(const std::array<uint32_t, Key::subkeys>& key) 
{
    for (uint8_t i = 0; i < this->key.size(); i++) {
        if (key[i] == 0) {
            throw std::invalid_argument("Each value in the key must be non-zero.");
        }
        this->key[i] = key[i];
    }
}


std::array<uint32_t, Key::subkeys> Key::getKey() 
{
    return this->key;
}


Key Key::getKeyInverse()
{
    Key keyInverse;
    bool foundInverse[Key::subkeys];
    double subkeyInverse;

    for (uint8_t i = 0; i < Key::subkeys; i++) {
        foundInverse[i] = false;
    }

    for (uint32_t n = 0; n <= UINT16_MAX; n++) {
        for (uint8_t i = 0; i < Key::subkeys; i++) {
            if (!foundInverse[i]) {
                if (((n * this->key[i]) % (UINT16_MAX + 1)) == 1) {
                    keyInverse[i] = n;
                    foundInverse[i] = true;
                }
            }
        }
    }

    return keyInverse;
}


uint32_t& Key::operator[](uint8_t index)
{
    return this->key.at(index);
}


void Key::operator++(int)
{

}

