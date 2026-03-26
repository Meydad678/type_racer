#pragma once

#include "ColorCodes.h"
#include "IRuleAssessor.h"
namespace Assessment
{
class LetterAssessor : public IRuleAssessor
{
  public:
    const Colors::ColorCodes color_codes;
    const Colors::Color COLOR_OF_CORRECT = Colors::Color{color_codes.GREEN};
    const Colors::Color COLOR_OF_INCORRECT = Colors::Color{color_codes.RED};
    const Colors::Color COLOR_OF_UNTYPED = Colors::Color{color_codes.RESET};
    const Colors::Color COLOR_OF_EXTRA = Colors::Color{color_codes.BOLDRED};
    const Colors::Color COLOR_OF_SKIPPED = Colors::Color{color_codes.UNDERLINE};
    // const Colors::Color COLOR_OF_SKIPPED = Colors::Color{color_codes.BOLDBLACK};
    const Colors::Color COLOR_OF_ERROR = Colors::Color{color_codes.BOLDMAGENTA};

    static constexpr unsigned char NO_ENTRY = __UINT8_MAX__;
    static constexpr unsigned char BLANK_SPACE = ' ';
    /**
     * @brief This function assesses the expected vs reality, and generates the letter state.
     *        It's one of the main components of the game rules.
     *
     * @see IRuleAssessor for more detail.
     */
    LetterState assess(unsigned char expected, unsigned char reality) const override;

    /**
     * @brief This function generates the color for each letter state.
     *
     * @see IRuleAssessor for more detail.
     */
    bool state_to_color(LetterState state, Colors::Color &o_color) const override;
};

}; // namespace Assessment