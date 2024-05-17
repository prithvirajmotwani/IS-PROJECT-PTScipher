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
        this->key[i] = key[i];
    }
}


std::array<uint32_t, Key::subkeys> Key::getKey() 
{
    return this->key;
}


bool Key::isMax()
{
    bool end = true;
    for (uint8_t i = 0; i < Key::subkeys; i++) {
        if (this->key[i] != UINT32_MAX) {
            end = false;
            break;
        }
    }
    return end;
}


uint32_t Key::operator[](uint8_t index)
{
    return this->key.at(index);
}


void Key::operator++(int)
{
    for (uint8_t i = 0; i < this->key.size(); i++) {
        if (++this->key[i] != 0) {
            break;  // Stop if carry-over is not needed
        }
    }
}

