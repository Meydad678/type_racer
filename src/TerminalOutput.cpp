#include "TerminalOutput.h"
#include "Color.h"
#include "ColorCodes.h"
#include "string"

Output::EOutputErrorCodes Output::TerminalOutput::render(std::string message,
                                                         Colors::Color color) const
{
    Colors::ColorCodes color_codes;
    std::cout << color.get_code() << message << color_codes.RESET;

    if (std::cout.fail() || std::cout.bad())
    {
        return Output::EOutputErrorCodes::FAILURE;
    }
    return Output::EOutputErrorCodes::SUCCESS;
}