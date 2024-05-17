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


void PTSCipher::permute(std::string& text, Key key)
{
    uint32_t first_element = key[0];
    uint32_t last_element = key[7];
    uint8_t rows = getBits(first_element, 24, 8);
    uint8_t columns = getBits(last_element, 0, 8);
    if (rows == 0) {
        rows = 1;
    }
    if (columns == 0) {
        columns = 1;
    }
    size_t height = text.length() / (rows * columns);
    if (text.length() % (rows * columns) != 0) {
        height++;
    }

    size_t paddingLength = (rows * columns * height) - text.length();
    text.insert(text.end(), paddingLength, '\0');

    std::string cipher_text;
    cipher_text.reserve(text.length());

    std::vector<std::vector<std::vector<char>>> box(rows, std::vector<std::vector<char>>(columns, std::vector<char>(height, 0)));
    //writing text into box
    size_t text_char_count = 0;
    for (size_t h = 0; h < height; h++) {
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < columns; c++) {
                box[r][c][h] = text[text_char_count++];
            }
        }
    }

    //reading text from box
    for (size_t r = rows; r >= 1; r--) {
        for (size_t c = 0; c < columns; c++) {
            for (size_t h = height; h >= 1; h--) {
                cipher_text += box[r - 1][c][h - 1];
            }
        }
    }
    text = cipher_text;
}


void PTSCipher::inversePermute(std::string& text, Key key)
{
    uint32_t first_element = key[0];
    uint32_t last_element = key[7];
    uint8_t rows = getBits(first_element, 24, 8);
    uint8_t columns = getBits(last_element, 0, 8);
    if (rows == 0) {
        rows = 1;
    }
    if (columns == 0) {
        columns = 1;
    }
    size_t height = text.length() / (rows * columns);


    std::string plain_text;
    plain_text.reserve(text.length());
    std::vector<std::vector<std::vector<char>>> box(rows, std::vector<std::vector<char>>(columns, std::vector<char>(height, 0)));

    // writing cipher text into box
    int text_char_count = 0;
    for (size_t r = rows; r >= 1; r--) {
        for (size_t c = 0; c < columns; c++) {
            for (size_t h = height; h >= 1; h--) {
                box[r - 1][c][h - 1] = text[text_char_count++];
            }
        }
    }

    //reading plain text from box
    for (size_t h = 0; h < height; h++) {
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < columns; c++) {
                plain_text += box[r][c][h];
            }

        }
    }

    // Find the position of the first null character
    size_t null_pos = plain_text.find('\0');

    // If a null character is found, erase from that position till the end
    if (null_pos != std::string::npos) {
        plain_text.erase(null_pos);
    }

    text = plain_text;
}



void PTSCipher::encrypt(std::string& text, Key key)
{
    permute(text, key);
    substitute(text, key);
}


void PTSCipher::decrypt(std::string& text, Key key)
{
    inverseSubstitute(text, key);
    inversePermute(text, key);
}
