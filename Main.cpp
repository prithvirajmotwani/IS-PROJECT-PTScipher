#include <iostream>
#include "PTSCipher.h"
#include "Key.h"


int main() {
    PTSCipher cipher;
    Key key;

    key.generateRandomKey();
    std::array<uint32_t, 8> keyArray = key.getKey();
    for (uint8_t i = 0; i < 8; i++) {
        std::cout << keyArray[i] << ", ";
    }
    std::cout << '\n';

    
    std::string text = "A quick brown x";
    std::cout << text.length() << '\n';
    
    cipher.pad(text,key);
    std::cout << "after padding" << '\n';
    std::cout << text.length() << '\n';

    cipher.permute(text,key);

    std::cout << text << '\n';

    cipher.inverser_permute(text,key);
    std::cout<< text << '\n';



    
    return 0;
}