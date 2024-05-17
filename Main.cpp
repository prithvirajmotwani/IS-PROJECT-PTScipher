#include <iostream>
#include <fstream>
#include <string>
#include "PTSCipher.h"
#include "Key.h"



int main()
{
    PTSCipher cipher;
    Key key;
    key.generateRandomKey();

    std::cout << "Key:\n";
    for (uint8_t i = 0; i < Key::subkeys; i++) {
        std::cout << key[i] << ", ";
    }
    std::cout << '\n';

    std::string text;
    std::string line;
    std::fstream file;

    file.open("PlaintextFile.txt", std::ios::in);
    if (!file.is_open()) {
        std::cout << "PlaintextFile.txt does not exist.\n";
        exit(1);
    }
    while (std::getline(file, line)) {
        text += line + "\n";
    }
    file.close();


    cipher.encrypt(text, key);
    file.open("CiphertextFile.txt", std::ios::out);
    file << text;
    file.close();
    std::cout << "Encrypted.\n";


    cipher.decrypt(text, key);
    file.open("DecryptedFile.txt", std::ios::out);
    file << text;
    file.close();
    std::cout << "Decrypted.\n";

    
    return 0;
}