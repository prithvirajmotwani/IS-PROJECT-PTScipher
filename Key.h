#pragma once
#include <stdint.h>
#include <array>



class Key
{
private:
    std::array<uint32_t, 8> key;

public:
    void generateRandomKey();
    void setKey(const std::array<uint32_t, 8>& key);
    std::array<uint32_t, 8> getKey();
    uint32_t operator[](uint8_t index);
    void operator++(int);

};