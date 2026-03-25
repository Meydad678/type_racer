#pragma once

#include "IRuleAssessor.h"

namespace Assessment
{
class LetterAssessor : public IRuleAssessor
{
  public:
    static constexpr unsigned char NO_ENTRY = __UINT8_MAX__;
    static constexpr unsigned char BLANK_SPACE = ' ';
    /**
     * @brief This function assesses the expected vs reality, and generates the letter state.
     *        It's one of the main components of the game rules.
     *
     * @see IRuleAssessor for more detail.
     */
    LetterState assess(unsigned char expected, unsigned char reality) const override;
};

}; // namespace Assessment