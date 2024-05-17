#pragma once
#include <iostream>
#include <stdint.h>
#include "Key.h"



class PTSCipher
{
public:
    void substitute(std::string& text, Key key);
    void permute(std::string& text, Key key);

    void inverseSubstitute(std::string& text, Key key);
    void inversePermute(std::string& text, Key key);

    void encrypt(std::string& text, Key key);
    void decrypt(std::string& text, Key key);
};