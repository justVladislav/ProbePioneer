#include "gtest/gtest.h"
#include "relativeIndex.h"

using namespace  std;
//Tests passed successfully!
//In case of testing, parameters should be added to the method of the tested class,
// updateDocumentBase(), according to the testing class.
TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    vector<string> request = {"milk water", "sugar"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.69999999999999996},
                    {1, 0.29999999999999999}
            },
            {
            }
    };
    InvertedIndex idx;
    idx.updateDocumentBase(/**docs*/); //please see the remarks in invertedIndex.h
    // Here, it is necessary to put 'docs' as the parameter

    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}


TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    vector<string> request = {"moscow is the capital of russia"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, 0.66666666666666663},
                    {1, 0.66666666666666663},
                    {2, 0.66666666666666663},
                    {3, 0.66666666666666663},
                    {4, 0.66666666666666663},
                    {5, 0.66666666666666663},
                    {6, 0.66666666666666663},
                    {8, 0.66666666666666663},
                    {9, 0.66666666666666663},
                    {10, 0.66666666666666663},
                    {11, 0.66666666666666663},
                    {12, 0.66666666666666663},
                    {13, 0.66666666666666663},
                    {15, 0.66666666666666663},
                    {16, 0.66666666666666663},
                    {17, 0.66666666666666663},
                    {18, 0.66666666666666663},
                    {19, 0.66666666666666663},
                    {20, 0.66666666666666663},
                    {21, 0.66666666666666663}

            }
    };
    InvertedIndex idx;
    idx.updateDocumentBase(/**docs*/); //please see the remarks in invertedIndex.h
    // Here, it is necessary to put 'docs' as the parameter

    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = srv.search(request);

    ASSERT_EQ(result, expected);
}