#include "invertedIndex.h"
#include "converterJson.h"
#include <sstream>
#include <thread>




int InvertedIndex::count(const std::vector<std::string>& vec, const std::string& str)const
{
    int count = 0;
    for (int i = 0; i < vec.size(); ++i)
    {

        if (vec[i] == str)
        {
            count++;
        }
    }

    return count;
}

void InvertedIndex::processDocument(const size_t& docId)
{
    std::vector<std::string> words;
    std::map<std::string, std::vector<Entry>> tempDict;

    std::string line = docs[docId];
    int c = 0;
    std::istringstream ss(line);
    std::string word;

    while (ss >> word)
    {
        words.push_back(word);
    }

    std::lock_guard<std::mutex> lock(mtx);

    while (!words.empty())
    {
        c = count(words, words[0]);
        tempDict[words[0]].push_back({docId, c});

        std::string target = words[0];
        auto it = words.begin();

        while (it != words.end())
        {
            if (*it == target)
            {
                it = words.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    for (const auto& entry : tempDict)
    {
        freqDictionary[entry.first].insert(freqDictionary[entry.first].end(), entry.second.begin(), entry.second.end());
    }

}

void InvertedIndex::updateDocumentBase()
{
    //In case of testing, it is necessary to pass all the parameter values of the method as the variable 'docs',
    // instead of calling the method converter.getTextDocuments();
    //void InvertedIndex::updateDocumentBase(std::vector<std::string> inputDocs)
    //      docs = inputDocs;
    ConverterJSON converter;
    docs = converter.getTextDocuments();
    std::vector<std::thread> threads;

    for (size_t i = 0; i < docs.size(); ++i)
    {
        threads.emplace_back(&InvertedIndex::processDocument, this, i);
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    std::cout << "Database Updated.\n";
}
std::vector<Entry> InvertedIndex::getWordCount(const std::string& word)
{
    return this->freqDictionary[word];
}


std::map<std::string, std::vector<Entry>> InvertedIndex::getDictionary()
{
return this->freqDictionary;
}