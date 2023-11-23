#pragma once
#include "invertedIndex.h"

#ifndef SKILLBOXSEARCHENGINE_RELATIVEINDEX_H
#define SKILLBOXSEARCHENGINE_RELATIVEINDEX_H

struct RelativeIndex
{
    size_t docId;
    double rank;

    bool operator ==  (const RelativeIndex& _oth) const
    {
        return (docId == _oth.docId && rank == _oth.rank);
    }
};

class SearchServer {
public:
/**
* @param idx a reference to the InvertedIndex class is passed into the constructor
* of the SearchServer so that it can determine the frequency of words encountered in the query.
*/
    SearchServer(InvertedIndex& idx) : _index(idx){ };
/**
* Method for processing search queries
* @param queries_input search queries taken from the file requests.json
* @return returns a sorted list of relevant responses for the given queries
*/
    std::vector<std::vector<RelativeIndex>> search ( std::vector<std::string>& queries_input);

private:
     InvertedIndex& _index;
     std::vector<std::string> splitQuery(const std::string& query);//The method separates a document into individual words
     std::vector<std::string> getUniqueWords(const std::vector<std::string>& words);//The method returns a list of unique words
     std::map<size_t, std::vector<int>> countWords(const std::multimap<int, size_t>& toSort);//The method returns the
     // count of words for each document according to the query number
     std::vector<RelativeIndex> toCalculation(const std::map<size_t, std::vector<int>>& toCalculate);
     //The method calculates the Absolute Relevance for each document
     std::vector<RelativeIndex> revelanceCalc(const std::vector<RelativeIndex>& calculation);//The method calculates
     // the Relative Relevance for each document and returns a container with the obtained results
     bool compareVectors(const RelativeIndex& a, const RelativeIndex& b);//Comparator for sorting the relevance container

};

#endif //SKILLBOXSEARCHENGINE_RELATIVEINDEX_H
