#pragma once

#ifndef SKILLBOXSEARCHENGINE_CONVERTERJSON_H
#define SKILLBOXSEARCHENGINE_CONVERTERJSON_H


#include <iostream>
#include <vector>
#include <string>
#include "relativeIndex.h"
#include <mutex>

class ConverterJSON{


public:
    ConverterJSON() = default;

/**
* Method to retrieve the contents of files
* @return Returns a list with the contents of files listed
* in config.json
 **/
    std::vector<std::string> getTextDocuments();
/**
* The method reads the max_responses field to determine the maximum
* number of responses for a single request
* @return
*/
    int getResponsesLimit();
/**
* Method to fetch requests from the requests.json file
* @return returns a list of requests from the requests.json file
*/
    std::vector<std::string> getRequests();
/**
* Store the results of search queries in the answers.json file
*/
    void putAnswers(std::vector<std::vector<std::pair<size_t, double>>>& answers);
/**
* Gets programs Name fron config.json
*/
    std::string programName();
/**
 *
 * @param input
 * Method takes a vector of vectors containing relative indices (RelativeIndex) and converts it into a vector of vectors,
 * where each element contains a pair of values
 * @return
 * */
     std::vector<std::vector<std::pair<size_t, double>>> convertToPairVector
                    (const std::vector<std::vector<RelativeIndex>>& input);

    void addFileToConfig(const std::string& filePath);
    /**
 *
 * @param filePath
 * Method adds new file path to array of files in config.json
 * */
    void addRequest(const std::string& filePath);
    /**
*
* @param filePath
* Method adds new request path to array of requests in request.json
* */

    int getUpdateTime();

    std::mutex lock;




};
#endif //SKILLBOXSEARCHENGINE_CONVERTERJSON_H
