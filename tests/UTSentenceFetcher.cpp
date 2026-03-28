#include "SentenceFetcher.h"
#include <gtest/gtest.h>

namespace Sentences
{

static constexpr uint8_t EXPECTED_INDEX_AFTER_ONE_RETRIVAL = 1;
static constexpr uint8_t EXPECTED_INDEX_AFTER_FULL_LAP = 0;
static const std::string EXPECTED_SENTENCE_AFTER_INITILAZATION =
    "The quick brown fox jumps over the lazy dog.";
static const std::string EXPECTED_SENTENCE_AFTER_ONE_RETRIEVAL = "Wait, is it 2026 already?";

class UTSentenceFetcher : public ::testing::Test
{
  protected:
    SentenceFetcher sentence_fetcher;

    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(UTSentenceFetcher,
       get_sentence_returns_the_excpected_sentence_with_suceess_error_code_when_initialized)
{
    std::string output;
    SentenceFetcherError error_code = sentence_fetcher.get_sentence(output);

    EXPECT_EQ(error_code, SentenceFetcherError::SUCCESS);
    EXPECT_EQ(output, EXPECTED_SENTENCE_AFTER_INITILAZATION);
}

TEST_F(UTSentenceFetcher,
       get_sentence_returns_the_excpected_sentence_with_suceess_error_code_after_one_retrieval)
{
    std::string output;
    SentenceFetcherError error_code = sentence_fetcher.get_sentence(output);
    error_code = sentence_fetcher.get_sentence(output);

    EXPECT_EQ(error_code, SentenceFetcherError::SUCCESS);
    EXPECT_EQ(output, EXPECTED_SENTENCE_AFTER_ONE_RETRIEVAL);
}

TEST_F(
    UTSentenceFetcher,
    get_sentence_returns_the_first_sentence_with_suceess_error_code_after_retrieving_all_the_sentences_once)
{
    std::string output;
    SentenceFetcherError error_code;
    for (uint64_t i = 0; i < sentence_fetcher.sentences.size(); i++)
    {
        error_code = sentence_fetcher.get_sentence(output);
        ASSERT_EQ(error_code, SentenceFetcherError::SUCCESS);
    }
    EXPECT_EQ(sentence_fetcher.index, EXPECTED_INDEX_AFTER_FULL_LAP);
}

TEST_F(UTSentenceFetcher, get_sentence_increases_index_by_one_when_not_exceeding_the_db_size)
{
    std::string output;
    SentenceFetcherError error_code = sentence_fetcher.get_sentence(output);

    EXPECT_EQ(sentence_fetcher.index, EXPECTED_INDEX_AFTER_ONE_RETRIVAL);
}
}; // namespace Sentences