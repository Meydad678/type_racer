#include "Color.h"

Colors::Color::Color(const std::string &code) : asii_code(code) {}

const std::string &Colors::Color::get_code() const { 
    return this->asii_code;
}