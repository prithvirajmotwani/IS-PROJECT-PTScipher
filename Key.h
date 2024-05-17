#pragma once
#include <stdint.h>
#include <array>



class Key
{
public:
    constexpr static uint8_t subkeys = 8;

private:
    std::array<uint32_t, subkeys> key;

public:
    void generateRandomKey();
    void setKey(const std::array<uint32_t, subkeys>& key);
    std::array<uint32_t, subkeys> getKey();
    bool isMax();
    uint32_t operator[](uint8_t index);
    void operator++(int);
};