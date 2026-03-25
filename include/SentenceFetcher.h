#include "SentenceFetcherError.h"
#include <cstdint>
#include <gtest/gtest_prod.h>
#include <string>
#include <vector>

constexpr int DEFAULT_INDEX = 0;

namespace Sentences
{
class SentenceFetcher
{
  private:
    const std::vector<std::string> sentences;
    uint64_t index;

    FRIEND_TEST(UTSentenceFetcher,
                get_sentence_increases_index_by_one_when_not_exceeding_the_db_size);
    FRIEND_TEST(
        UTSentenceFetcher,
        get_sentence_returns_the_first_sentence_with_suceess_error_code_after_retrieving_all_the_sentences_once);

    /**
     * @brief This function updates the index.
     *        It increases it by 1, or if goes over the size of the DB, it will go back to 0.
     */
    void update_index();

  public:
    SentenceFetcher();

    /**
     * @returns the sentence in the index place from the sentences vector.
     */
    SentenceFetcherError get_sentence(std::string &o_sentence);
};
}; // namespace Sentences