#include "gtest/gtest.h"
#include <vector>
#include <string>
#include "invertedIndex.h"

//Tests passed successfully!
//In case of testing, parameters should be added to the method of the tested class,
// updateDocumentBase(), according to the testing class.
void TestInvertedIndexFunctionality(
        const std::vector<std::string>& docs,
        const std::vector<std::string>& requests,
        const std::vector<std::vector<Entry>>& expected
)
{
std::vector<std::vector<Entry>> result;
InvertedIndex idx;
idx.updateDocumentBase(docs); 
for(auto& request : requests) {
std::vector<Entry> word_count = idx.getWordCount(request);
result.push_back(word_count);
}
ASSERT_EQ(result, expected);
}


TEST(TestCaseInvertedIndex, TestBasic) {
    const std::vector<std::string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    const std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::vector<Entry>> expected = {
            {
                    {0, 1}
            }, {
                    {0, 1}, {1, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const std::vector<std::string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const std::vector<std::string> requests = {"m", "statement"};
    const std::vector<std::vector<Entry>> expected = {
            {
            }, {
                    {1, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}


