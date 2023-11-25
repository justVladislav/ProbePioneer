#include "relativeIndex.h"
#include <sstream>
#include <unordered_set>
#include "converterJson.h"
#include <algorithm>


bool SearchServer::compareVectors(const RelativeIndex& a, const RelativeIndex& b)
{
    return a.rank > b.rank;
}

std::vector<std::string> SearchServer::splitQuery(const std::string& query)
{
    std::vector<std::string> words;
    std::istringstream ss(query);
    std::string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}
std::vector<std::string> SearchServer::getUniqueWords(const std::vector<std::string>& words)
{
    std::unordered_set<std::string> tempContainer(words.begin(), words.end());
    std::vector<std::string> result (tempContainer.begin(), tempContainer.end());

    return result;

}

std::map<size_t, std::vector<int>> SearchServer::countWords(const std::multimap<int, size_t>& toSort)
{
    std::map<size_t, std::vector<int>> result;

    for (auto it = toSort.begin(); it != toSort.end(); ++it)
    {
        if (it->second == it->second) {

            result[it->second].push_back(it->first);
        }
    }

    return result;
}

std::vector<RelativeIndex> SearchServer::toCalculation(const std::map<size_t, std::vector<int>>& toCalculate)
{
    std::vector<RelativeIndex> result;

    for (const auto& pair : toCalculate)
    {
        size_t key = pair.first;
        std::vector<int> values = pair.second;

        double sum = 0;
        for (int value : values)
        {
            sum += value;

        }

        result.push_back({ key, sum });
    }

    return result;

}

std::vector<RelativeIndex> SearchServer::revelanceCalc(const std::vector<RelativeIndex>& calculation)
{
    double max = 0;
    std::vector<RelativeIndex> result;
    for (auto& c : calculation)
    {
        if (c.rank > max)
        {
            max = c.rank;
        }
    }

    for (const auto& c : calculation)
    {
        double s = c.rank / max;
        result.push_back({ c.docId, s });
    }

    return result;
}


std::vector<std::vector<RelativeIndex>>SearchServer::search( std::vector<std::string>& queries_input){
   
    std::vector<std::vector<RelativeIndex>> result;   


    for ( int i = 0; i < queries_input.size(); ++i)
    {
        std::vector<std::string> splitWords = splitQuery(queries_input[i]);
        std::vector<std::string> uniqWords = getUniqueWords(splitWords);
        splitWords.clear();

        std::multimap<int, size_t> toSort;

        for ( const auto & uW : uniqWords)
        {
            auto wordsQuantity = _index.getWordCount(uW);

            for( const auto& entry : wordsQuantity)
            {
                toSort.insert({entry.count, entry.docId});
            }
        }

        std::map<size_t, std::vector<int>> sortedResult = countWords(toSort);

        toSort.clear();

        std::vector<RelativeIndex> prepForCalc = toCalculation(sortedResult);

        sortedResult.clear();

        result.push_back(revelanceCalc(prepForCalc));

        prepForCalc.clear();
    }
    for (auto& innerVector : result) {
        std::sort(innerVector.begin(), innerVector.end(),
                  [this](const RelativeIndex& a, const RelativeIndex& b) {
                      if (a.rank == b.rank) {
                          
                          return a.docId < b.docId;
                      } else {
                          
                          return this->compareVectors(a, b);
                      }
                  });
    }

    std::cout << "Search Made.\n";

    return result;
}