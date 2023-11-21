#include "converterJson.h"
#include "invertedIndex.h"
#include "relativeIndex.h"
#include <thread>
#include <memory>
#ifndef SKILLBOXSEARCHENGINE_PROGRAMINTERFACE_H
#define SKILLBOXSEARCHENGINE_PROGRAMINTERFACE_H


class ProgramInterface
{
public:
    ProgramInterface();

    void programFace( std::thread& t1,  std::thread& t2);
    /**
     * This function is the main program interface that takes user commands like adding files, adding requests,
     * performing searches, updating documents, and putting answers. It runs in a loop until
     * the user enters the "exit" command
     */
    void runUpdateDocsThread();
    /**
     * This method runs a thread that periodically updates the document base used by the inverted index.
     */
    void runSearchServer();
    /**
     * This function runs a thread that continuously processes user queries,
     * searches them in the server, and handles exceptions.
     */

    ~ProgramInterface()
    {
        delete server;
    }

private:

    std::shared_ptr<ConverterJSON> converter;// A shared pointer to an object of type ConverterJSON
    SearchServer* server; // A pointer to an object of type SearchServer
    std::shared_ptr<InvertedIndex> invIndex;//A shared pointer to an object of type InvertedIndex
    std::mutex results_mutex;
    std::vector<std::string> queries_input;
    std::vector<std::vector<RelativeIndex>> searchResult;
    std::vector<std::vector<std::pair<size_t, double>>> converterResult;
};


#endif //SKILLBOXSEARCHENGINE_PROGRAMINTERFACE_H
