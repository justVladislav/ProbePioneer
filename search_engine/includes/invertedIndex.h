#pragma once
#include <vector>
#include <string>
#include <map>
#include <mutex>

#ifndef SKILLBOXSEARCHENGINE_INVERTEDINDEX_H
#define SKILLBOXSEARCHENGINE_INVERTEDINDEX_H


struct Entry {
    size_t docId; int count;

    bool operator ==(const Entry& other) const {
        return (docId == other.docId &&
                count == other.count);
    }
};
class InvertedIndex
{
public:

    InvertedIndex() = default;
/**
* Update or populate the document database for searching, processing each file separately in threads
*/
    void updateDocumentBase(); //In case of testing necessary to add parameter according to the Testing Class
    // example - void updateDocumentBase(std::vector<std::string>& inputDocs)

/**
* The method determines the number of occurrences of the word in the loaded document database
* @param word the word to determine the frequency of occurrences
* @return returns a prepared list with word frequencies
*/
    std::vector<Entry> getWordCount(const std::string& word);

    std::map<std::string, std::vector<Entry>> getDictionary();
    /**
    *The validation method was used to check the accuracy of the completion
    */



private:

    std::vector<std::string>docs; //The list of document contents
    std::map<std::string, std::vector<Entry>> freqDictionary; //The dictionary obtained after processing the documents
    std::mutex mtx;
    void processDocument(const size_t& docId);//A private method for processing an array of documents to
    // subsequently initialize it separately in a thread
    int count(const std::vector<std::string>& vec, const std::string& str) const; //A private method that counts the occurrences
    // of identical words within a single document


};



#endif //SKILLBOXSEARCHENGINE_INVERTEDINDEX_H
