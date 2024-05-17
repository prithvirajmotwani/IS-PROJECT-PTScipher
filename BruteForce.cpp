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
   //key.setKey({ 0, 0, 0, 0, 0, 0, 0, 0 });

   std::cout << "Key:\n";
   for (uint8_t i = 0; i < Key::subkeys; i++) {
       std::cout << key[i] << ", ";
   }
   std::cout << "\n\n";


   std::string plaintext = "A quick brown fox jumps over the lazy dog.";
   std::string ciphertext = plaintext;
   cipher.encrypt(ciphertext, key);


   key.setKey({ 0, 0, 0, 0, 0, 0, 0, 0 });
   
   std::cout << "Plaintext: \n";
   std::cout << plaintext << "\n\n";


   std::string decryptedText;
   std::string testWord = "the";
   size_t found;

   while (!key.isMax())
   {
       decryptedText = ciphertext;
       cipher.decrypt(decryptedText, key);
       found = decryptedText.find(testWord);

       if (found != std::string::npos) {
           std::cout << "\n\nDecrypted.\n";
           std::cout << "Key:\n";
           for (uint8_t i = 0; i < Key::subkeys; i++) {
               std::cout << key[i] << ", ";
           }
           std::cout << "\n\nDecrypted text: \n";
           std::cout << decryptedText << '\n';
           break;
       }
       for (uint8_t i = 0; i < Key::subkeys; i++) {
           if (key[i] == 10) {
               std::cout << key[i] << ", ";
           }
           else if (key[i] == 32000) {
               std::cout << key[i] << ", ";
           }
       }
       std::cout << '\r';

       key++;
   }






}