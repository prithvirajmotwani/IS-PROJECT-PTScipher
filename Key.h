#pragma once
#include <stdint.h>
#include <array>



class Key
{
public:
    constexpr static uint8_t subkeys = 16;

private:
    std::array<uint16_t, subkeys> key;

public:
    void generateRandomKey();
    void setKey(const std::array<uint16_t, subkeys>& key);
    std::array<uint16_t, subkeys> getKey();
    Key getKeyInverse();
    uint16_t operator[](uint8_t index);
    void operator++(int);

};