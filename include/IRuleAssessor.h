#pragma once

#include "LetterState.h"
#include <string>
#include "Color.h"

namespace Assessment
{
class IRuleAssessor
{
  public:
    virtual ~IRuleAssessor() = default;

    /**
     * @brief This function assesses the expected vs reality, and generates the letter state.
     *        It's one of the main components of the game rules.
     *
     * @param expected - The expected input of the user.
     * @param reality - The input of the user in reality.
     *
     * @return The appropriate letter state.
     */
    virtual LetterState assess(unsigned char expected, unsigned char reality) const = 0;

    /**
     * @brief This function generates the color for each letter state.
     *
     * @param state - The letter state.
     * @param color - The color that is appropriate to the letter state. output paramater.
     *
     * @return If the state has an appropiate color
     */
    virtual bool state_to_color(LetterState state, Colors::Color &o_color) const = 0;
};

}; // namespace Assessment