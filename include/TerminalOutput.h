#pragma once

#include "Color.h"
#include "IOutput.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace Output
{

class TerminalOutput : public IOutput
{
  public:
    static const uint8_t CLEAR_SCREEN_NEWLINES = 70;

    /**
     * @brief This function shows to as output the message in a color.
     *
     * @see IOutput for more detail.
     */
    EOutputErrorCodes render(std::string message, Colors::Color color) const override;

    /**
     * @brief This function clears the screen.
     */
    EOutputErrorCodes clear_screen() const override;
};

}; // namespace Output