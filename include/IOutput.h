#pragma once

#include "Color.h"
#include "EOutputErrorCodes.h"
#include <string>
namespace Output
{
class IOutput
{
  public:
    virtual ~IOutput() = default;

    /**
     * @brief This function shows to as output the message in a color.
     *
     * @param message - the message to show.
     * @param color - an instance of a color object.
     *
     * @return The appropriate error code.
     */
    virtual EOutputErrorCodes render(std::string message, Colors::Color color) const = 0;

    /**
     * @brief This function makes a new line on the screen.
     *
     * @return The appropriate error code.
     */
    virtual EOutputErrorCodes make_new_line() const = 0;
    
    /**
     * @brief This function clears the screen.
     */
    virtual EOutputErrorCodes clear_screen() const = 0;
};

}; // namespace Output