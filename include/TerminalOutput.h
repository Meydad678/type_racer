#pragma once

#include "Color.h"
#include "IOutput.h"
#include <iostream>
#include <string>

namespace Output
{
class TerminalOutput : public IOutput
{
  public:
    /**
     * @brief This function shows to as output the message in a color.
     *
     * @see IOutput for more detail.
     */
    EOutputErrorCodes render(std::string message, Colors::Color color) const override;
};

}; // namespace Output