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