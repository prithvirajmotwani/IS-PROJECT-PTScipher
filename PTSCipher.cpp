#include "PTSCipher.h"
#include <vector>



template <typename T>
T rightRotate(T num, uint8_t bits)
{
    // Calculate the number of bits in the data type
    uint8_t numBits = sizeof(T) * 8;

    // Adjust the rotation count to avoid rotating by more than the number of bits
    bits = bits % numBits;

    // Perform the rotation
    return (num >> bits) | (num << (numBits - bits));
}


template <typename T>
T leftRotate(T num, uint8_t bits)
{
    // Calculate the number of bits in the data type
    uint8_t numBits = sizeof(T) * 8;

    // Adjust the rotation count to avoid rotating by more than the number of bits
    bits = bits % numBits;

    // Perform the rotation
    return (num << bits) | (num >> (numBits - bits));
}


template<typename T>
T getBits(T num, int startBit, int numBits)
{
    // Mask with 'numBits' set bits
    T mask = (static_cast<T>(1) << numBits) - static_cast<T>(1);
    return (num >> startBit) & mask;
}


void PTSCipher::substitute(std::string& text, Key key) 
{
    size_t values = text.length() / sizeof(key[0]);
    uint8_t subkeyIndex = 0;
    uint32_t subkeyForRotation;
    // Bits to to use for rotation.
    uint8_t subkeyBits = 4;
    uint8_t rounds = Key::subkeys;
    uint8_t bits;
    // 4 bytes pointer type is used to read and write 4 bytes at a time.
    uint32_t* valuePtr = (uint32_t*)text.data();

    for (size_t i = 0; i < values; i++) {
        subkeyForRotation = key[subkeyIndex];

        for (uint8_t j = 0; j < rounds; j++) {
            bits = getBits(subkeyForRotation, subkeyBits * j, subkeyBits);
            // *valuePtr = plaintext value.
            // Assigning ciphertext value after left rotating and performing xor.
            *valuePtr = leftRotate(*valuePtr, bits) ^ key[j];
        }

        // Move pointer to the next 4 bytes.
        valuePtr++;
        subkeyIndex = (subkeyIndex + 1) % Key::subkeys;
    }
}


void PTSCipher::inverseSubstitute(std::string& text, Key key) 
{
    size_t values = text.length() / sizeof(key[0]);
    uint8_t subkeyIndex = 0;
    uint32_t subkeyForRotation;
    // Bits to to use for rotation.
    uint8_t subkeyBits = 4;
    uint8_t rounds = Key::subkeys;
    uint8_t bits;
    uint32_t* valuePtr = (uint32_t*)text.data();

    for (size_t i = 0; i < values; i++) {
        subkeyForRotation = key[subkeyIndex];

        for (uint8_t j = 0; j < rounds; j++) {
            bits = getBits(subkeyForRotation, subkeyBits * (rounds - j) - subkeyBits, subkeyBits);
            // *valuePtr = ciphertext value.
            // Assigning plaintext value after performing xor and right rotating.
            *valuePtr = rightRotate(*valuePtr ^ key[rounds - j - 1], bits);
        }

        // Move pointer to the next 4 bytes.
        valuePtr++;
        subkeyIndex = (subkeyIndex + 1) % Key::subkeys;
    }
}
