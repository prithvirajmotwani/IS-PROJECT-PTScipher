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

    
    std::string text = "A quick brown fox";

    std::cout << text << '\n';
    std::cout << text.length() << '\n';
    
    cipher.pad(text);

    std::cout << "After padding: \n";
    std::cout << text << '\n';
    std::cout << text.length() << '\n';

    cipher.substitute(text, key);

    std::cout << "After substitution: \n";
    std::cout << text << '\n';
    std::cout << text.length() << '\n';

    cipher.inverseSubstitute(text, key);

    std::cout << "After inverse substitution: \n";
    std::cout << text << '\n';
    std::cout << text.length() << '\n';


    
    return 0;
}