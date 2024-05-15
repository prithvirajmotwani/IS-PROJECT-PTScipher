#include "PTSCipher.h"
#include <vector>
#include <stdint.h>
#include <cmath>
#include <string>
#include <cstring>
#include <cmath>



void PTSCipher::pad(std::string& text, Key key) {
    size_t paddinglength;

    uint32_t first_element = key[0];
    uint32_t last_element = key[7];
    uint8_t row = *((uint8_t *) &first_element) + 3; //last byte of first element
    uint8_t column = *((uint8_t *) &last_element); //first byte of last element
    uint8_t height = ceil((long double)text.length() / (row * column)); 

    // std::cout << "height: " << (int)height << std::endl;
    // std::cout<< (int)row << std::endl;
    // std::cout<< (int)column << std::endl;
    paddinglength = (row * column * height) - text.length();
    // std::cout << "padding length: " << (int)paddinglength << std::endl;
    text.insert(text.end(), paddinglength, 'b');
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

void PTSCipher::permute(std::string& text, Key key) {
    std::cout<< "check 1" << std::endl;

    std::string cipher_text = "";
    uint32_t first_element = key[0];
    uint32_t last_element = key[7];
    uint8_t row = *((uint8_t *) &first_element) + 3; //last byte of first element
    uint8_t column = *((uint8_t *) &last_element); //first byte of last element
    uint8_t height = text.length() / (row * column); 

    std::cout<< "check 2" << std::endl;
    std::cout<< (int)row << std::endl;
    std::cout<< (int)column << std::endl;
    std::cout<< text.length() << std::endl;



    std::vector<std::vector<std::vector<char>>> box(row, std::vector<std::vector<char>>(column, std::vector<char>(height, 0)));
    // std::cout << box.size() << std::endl;
    // std::cout << box[0].size() << std::endl;
    // std::cout << box[0][0].size() << std::endl;


    std::cout<< "check 3" << std::endl;
    //writing text into box
    size_t text_char_count = 0;
    for(size_t h = 0; h < height; h++) {
        for(size_t row1 = 0; row1 < row; row1++) {
            for(size_t col = 0; col< column; col++) {
                box[row1][col][h] = text[text_char_count++];
            }
        }
    }


    // for(size_t h = 0; h < height; h++) {
    //     for(size_t row1 = 0; row1 < row; row1++) {
    //         for(size_t col = 0; col< column; col++) {
    //             std::cout<<box[row1][col][h]<<std::endl;
    //         }
    //     }
    // }

    std::cout<< "check 4" << std::endl;


    //reading text from box
    
    for(size_t h = height-1; h >= 0; h--) {
        for(size_t row = row -1; row >= 0; row--) {
            for(size_t col = 0; col< column; col++) {
                std::cout << box[row][col][h] << std::endl;
                cipher_text += box[row][col][h];
                std::cout << "check 6" << std::endl;
            }
        }
    }

    std::cout<< "check 5" << std::endl;

    text = cipher_text;

}

void PTSCipher::inverser_permute(std::string& text, Key key) {

    std::string plain_text = "";
    uint32_t first_element = key[0];
    uint32_t last_element = key[7];
    uint8_t row = *((uint8_t *) &first_element) + 3; //last byte of first element
    uint8_t column = *((uint8_t *) &last_element); //first byte of last element
    uint8_t height = ceil(text.length() / (row * column)); 

    std::vector<std::vector<std::vector<char>>> box(row, std::vector<std::vector<char>>(column, std::vector<char>(height, 0)));

    // writing cipher text into box
    int text_char_count = 0;
    for(size_t h = height -1; h >= 0; h--) {
        for(size_t row = column -1; row >= 0; row--) {
            for(size_t col = 0; col< column; col++) {
                box[row][col][h] = text[text_char_count++];
            }
        }
    }
    
    //reading plain text from box
    for(size_t h = 0; h < height; h++) {
        for(size_t row = 0; row < column; row++) {
            for(size_t col = 0; col< row; col++) {
                plain_text += box[row][col][h];
            }
            
        }
    }

    text = plain_text;
}


void PTSCipher::permute(std::string& text, Key key) {
    std::cout<< "check 1" << std::endl;

    std::string cipher_text = "";
    uint32_t first_element = key[0];
    uint32_t last_element = key[7];
    uint8_t row = *((uint8_t *) &first_element) + 3; //last byte of first element
    uint8_t column = *((uint8_t *) &last_element); //first byte of last element
    uint8_t height = text.length() / (row * column); 

    std::cout<< "check 2" << std::endl;
    std::cout<< (int)row << std::endl;
    std::cout<< (int)column << std::endl;
    std::cout<< text.length() << std::endl;



    std::vector<std::vector<std::vector<char>>> box(row, std::vector<std::vector<char>>(column, std::vector<char>(height, 0)));
    // std::cout << box.size() << std::endl;
    // std::cout << box[0].size() << std::endl;
    // std::cout << box[0][0].size() << std::endl;


    std::cout<< "check 3" << std::endl;
    //writing text into box
    size_t text_char_count = 0;
    for(size_t h = 0; h < height; h++) {
        for(size_t row1 = 0; row1 < row; row1++) {
            for(size_t col = 0; col< column; col++) {
                box[row1][col][h] = text[text_char_count++];
            }
        }
    }


    // for(size_t h = 0; h < height; h++) {
    //     for(size_t row1 = 0; row1 < row; row1++) {
    //         for(size_t col = 0; col< column; col++) {
    //             std::cout<<box[row1][col][h]<<std::endl;
    //         }
    //     }
    // }

    std::cout<< "check 4" << std::endl;


    //reading text from box
    
    for(size_t h = height-1; h >= 0; h--) {
        for(size_t row = row -1; row >= 0; row--) {
            for(size_t col = 0; col< column; col++) {
                std::cout << box[row][col][h] << std::endl;
                cipher_text += box[row][col][h];
                std::cout << "check 6" << std::endl;
            }
        }
    }

    std::cout<< "check 5" << std::endl;

    text = cipher_text;

}

void PTSCipher::inverser_permute(std::string& text, Key key) {

    std::string plain_text = "";
    uint32_t first_element = key[0];
    uint32_t last_element = key[7];
    uint8_t row = *((uint8_t *) &first_element) + 3; //last byte of first element
    uint8_t column = *((uint8_t *) &last_element); //first byte of last element
    uint8_t height = ceil(text.length() / (row * column)); 

    std::vector<std::vector<std::vector<char>>> box(row, std::vector<std::vector<char>>(column, std::vector<char>(height, 0)));

    // writing cipher text into box
    int text_char_count = 0;
    for(size_t h = height -1; h >= 0; h--) {
        for(size_t row = column -1; row >= 0; row--) {
            for(size_t col = 0; col< column; col++) {
                box[row][col][h] = text[text_char_count++];
            }
        }
    }
    
    //reading plain text from box
    for(size_t h = 0; h < height; h++) {
        for(size_t row = 0; row < column; row++) {
            for(size_t col = 0; col< row; col++) {
                plain_text += box[row][col][h];
            }
            
        }
    }

    text = plain_text;
}






