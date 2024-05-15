#include "PTSCipher.h"
#include <cstring>



void PTSCipher::pad(std::string& text) 
{
    uint8_t paddingLength = text.length() % 4;
    text.insert(text.end(), paddingLength, '\0');
}

void PTSCipher::substitute(std::string& text, Key key) 
{
    size_t values = text.length() / 4;
    uint8_t subkeyIndex = 0;
    uint32_t subkey;
    uint64_t y;
    uint32_t* valuePtr = (uint32_t*)text.data();

    for (size_t i = 0; i < values; i++) {
        subkey = key[subkeyIndex];
        // *valuePtr = plaintext value.
        y = *valuePtr * subkey + *valuePtr + 1;
        // Assigning ciphertext value.
        *valuePtr = y * subkey % UINT16_MAX;
        valuePtr++;
        subkeyIndex++;
    }
}

void PTSCipher::inverseSubstitute(std::string& text, Key key) 
{
    Key keyInverse;
    
}





