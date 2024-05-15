#include <iostream>
#include "PTSCipher.h"
#include "Key.h"


int main() {
    PTSCipher cipher;
    Key key;
    key.generateRandomKey();

    std::array<uint16_t, Key::subkeys> keyArray = key.getKey();
    for (uint8_t i = 0; i < 8; i++) {
        std::cout << keyArray[i] << ", ";
    }
    std::cout << '\n';

    Key keyInverse = key.getKeyInverse();
    std::array<uint16_t, Key::subkeys> keyInverseArray = keyInverse.getKey();
    for (uint8_t i = 0; i < 8; i++) {
        std::cout << keyInverseArray[i] << ", ";
    }
    std::cout << '\n';

    
    std::cout << "Done\n";

    
    std::string text = "A quick brown fox";

    std::cout << text << '\n';
    std::cout << text.length() << '\n';
    
    cipher.pad(text);

    std::cout << "\nAfter padding: \n";
    std::cout << text << '\n';
    std::cout << text.length() << '\n';

    cipher.substitute(text, key);

    std::cout << "\nAfter substitution: \n";
    std::cout << text << '\n';
    std::cout << text.length() << '\n';

    cipher.inverseSubstitute(text, key);

    std::cout << "\nAfter inverse substitution: \n";
    std::cout << text << '\n';
    std::cout << text.length() << '\n';


    
    return 0;
}