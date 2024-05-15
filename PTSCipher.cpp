#include "PTSCipher.h"
#include <cstring>
#include <cmath>



void PTSCipher::pad(std::string& text) 
{
    uint8_t paddingLength = text.length() % 2;
    text.insert(text.end(), paddingLength, '\0');
}

void PTSCipher::substitute(std::string& text, Key key) 
{
    size_t values = text.length() / sizeof(key[0]);
    uint8_t subkeyIndex = 0;
    uint16_t subkey;
    uint32_t y;
    uint16_t* valuePtr = (uint16_t*)text.data();

    for (size_t i = 0; i < values; i++) {
        subkey = key[subkeyIndex];
        // *valuePtr = plaintext value.
        y = *valuePtr ^ subkey;
        // Assigning ciphertext value.
        *valuePtr = y * subkey % (UINT16_MAX + 1);
        valuePtr++;
        subkeyIndex = (subkeyIndex + 1) % Key::subkeys;
    }
}

void PTSCipher::inverseSubstitute(std::string& text, Key key) 
{
    Key keyInverse = key.getKeyInverse();
    size_t values = text.length() / sizeof(key[0]);
    uint8_t subkeyIndex = 0;
    uint16_t subkey, subkeyInverse;
    uint32_t y;
    uint16_t* valuePtr = (uint16_t*)text.data();

    for (size_t i = 0; i < values; i++) {
        subkey = key[subkeyIndex];
        subkeyInverse = keyInverse[subkeyIndex];
        // *valuePtr = ciphertext value.
        y = *valuePtr * subkeyInverse;
        // Assigning plaintext value.
        *valuePtr = y ^ subkey;
        valuePtr++;
        subkeyIndex = (subkeyIndex + 1) % Key::subkeys;
    }
}





