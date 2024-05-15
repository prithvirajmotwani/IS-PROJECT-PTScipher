#pragma once
#include <iostream>
#include <stdint.h>
#include "Key.h"



class PTSCipher
{
public:
    void pad(std::string& text, Key key);
    void substitute(std::string& text, Key key);
    void permute(std::string& text, Key key);
    void inverser_permute(std::string& text, Key key);

    void inverseSubstitute(std::string& text, Key key);


};