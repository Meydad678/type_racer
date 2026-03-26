#include "TerminalOutput.h"
#include "Color.h"
#include "ColorCodes.h"
#include "string"

#define RETURN_APPROPIATE_STATUS_CODE()                                                            \
    do                                                                                             \
    {                                                                                              \
        if (std::cout.fail() || std::cout.bad())                                                   \
        {                                                                                          \
            return Output::EOutputErrorCodes::FAILURE;                                             \
        }                                                                                          \
        return Output::EOutputErrorCodes::SUCCESS;                                                 \
    } while (0)

Output::EOutputErrorCodes Output::TerminalOutput::render(std::string message,
                                                         Colors::Color color) const
{
    Colors::ColorCodes color_codes;
    std::cout << color.get_code() << message << color_codes.RESET;

    RETURN_APPROPIATE_STATUS_CODE();
}
Output::EOutputErrorCodes Output::TerminalOutput::make_new_line() const
{
    std::cout << std::endl;
    RETURN_APPROPIATE_STATUS_CODE();
}

Output::EOutputErrorCodes Output::TerminalOutput::clear_screen() const
{
    for (uint8_t i = 0; i < Output::TerminalOutput::CLEAR_SCREEN_NEWLINES; i++)
    {
        std::cout << std::endl;
        if (std::cout.bad() || std::cout.fail())
        {
            return Output::EOutputErrorCodes::FAILURE;
        }
    }
    return Output::EOutputErrorCodes::SUCCESS;
}
