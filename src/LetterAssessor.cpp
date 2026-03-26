#include "LetterAssessor.h"

Assessment::LetterState Assessment::LetterAssessor::assess(unsigned char expected,
                                                           unsigned char reality) const
{
    if (expected == Assessment::LetterAssessor::NO_ENTRY)
    {
        return Assessment::LetterState::ERROR;
    }
    if (reality == Assessment::LetterAssessor::NO_ENTRY)
    {
        return Assessment::LetterState::UNTYPED;
    }
    if (expected == reality)
    {
        return Assessment::LetterState::CORRECT;
    }
    if (expected == Assessment::LetterAssessor::BLANK_SPACE &&
        reality != Assessment::LetterAssessor::BLANK_SPACE)
    {
        return Assessment::LetterState::EXTRA;
    }
    if (expected != Assessment::LetterAssessor::BLANK_SPACE &&
        reality == Assessment::LetterAssessor::BLANK_SPACE)
    {
        return Assessment::LetterState::MISSING;
    }
    return Assessment::LetterState::INCORRECT;
}

bool Assessment::LetterAssessor::state_to_color(Assessment::LetterState state,
                                                Colors::Color &o_color) const
{
    switch (state)
    {
    case Assessment::LetterState::CORRECT:
        o_color = Assessment::LetterAssessor::COLOR_OF_CORRECT;
        return true;
    case Assessment::LetterState::INCORRECT:
        o_color = Assessment::LetterAssessor::COLOR_OF_INCORRECT;
        return true;
    case Assessment::LetterState::UNTYPED:
        o_color = Assessment::LetterAssessor::COLOR_OF_UNTYPED;
        return true;
    case Assessment::LetterState::EXTRA:
        o_color = Assessment::LetterAssessor::COLOR_OF_EXTRA;
        return true;
    case Assessment::LetterState::MISSING:
        o_color = Assessment::LetterAssessor::COLOR_OF_MISSING;
        return true;
    case Assessment::LetterState::ERROR:
        o_color = Assessment::LetterAssessor::COLOR_OF_ERROR;
        return false;
    default:
        return false;
    }
}
