#include "LetterAssessor.h"
#include <gtest/gtest.h>

namespace Assessment
{

static constexpr unsigned char BLANK_SPACE = ' ';
static constexpr unsigned char NO_ENTRY = UINT8_MAX;
static constexpr unsigned char NON_BLANK_LETTER1 = 'a';
static constexpr unsigned char NON_BLANK_LETTER2 = 'b';
static constexpr unsigned char NON_BLANK_LETTER3 = 'C';

class UTRuleAssessor : public ::testing::Test
{
  protected:
    std::unique_ptr<IRuleAssessor> assessor;
    void SetUp() override { assessor = std::make_unique<LetterAssessor>(); }
    void TearDown() override {}
};

TEST_F(UTRuleAssessor, assess_returns_correct_when_expected_equals_reality)
{
    EXPECT_EQ(LetterState::CORRECT, assessor->assess(NON_BLANK_LETTER1, NON_BLANK_LETTER1));
    EXPECT_EQ(LetterState::CORRECT, assessor->assess(BLANK_SPACE, BLANK_SPACE));
}
TEST_F(UTRuleAssessor, assess_returns_untyped_when_reality_is_no_entry)
{
    EXPECT_EQ(LetterState::UNTYPED, assessor->assess(NON_BLANK_LETTER1, NO_ENTRY));
    EXPECT_EQ(LetterState::UNTYPED, assessor->assess(BLANK_SPACE, NO_ENTRY));
}
TEST_F(UTRuleAssessor, assess_returns_error_when_expected_is_no_entry)
{
    EXPECT_EQ(LetterState::ERROR, assessor->assess(NO_ENTRY, NO_ENTRY));
    EXPECT_EQ(LetterState::ERROR, assessor->assess(NO_ENTRY, BLANK_SPACE));
    EXPECT_EQ(LetterState::ERROR, assessor->assess(NO_ENTRY, NON_BLANK_LETTER1));
}
TEST_F(UTRuleAssessor,
       assess_returns_extra_when_expected_is_blank_space_and_reality_is_non_blank_space)
{
    EXPECT_EQ(LetterState::EXTRA, assessor->assess(BLANK_SPACE, NON_BLANK_LETTER1));
}
TEST_F(UTRuleAssessor,
       assess_returns_missing_when_expected_is_non_blank_space_and_reality_is_blank_space)
{
    EXPECT_EQ(LetterState::MISSING, assessor->assess(NON_BLANK_LETTER1, BLANK_SPACE));
}
TEST_F(UTRuleAssessor,
       assess_returns_incorrect_when_expected_and_reality_are_non_blank_spaces_and_diffrent)
{
    EXPECT_EQ(LetterState::INCORRECT, assessor->assess(NON_BLANK_LETTER1, NON_BLANK_LETTER2));
    EXPECT_NE(LetterState::INCORRECT, assessor->assess(NON_BLANK_LETTER1, NON_BLANK_LETTER1));
}
}; // namespace Assessment