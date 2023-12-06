#include "converterJson.h"
#include <nlohmann/json.hpp>
#include <fstream>


const std::string versionNumber= "1.0.0";

class JsonFileException : public std::exception
{
public:
    JsonFileException(const std::string& message) : message_(message) {}

    const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
};


std::vector<std::string> ConverterJSON::getTextDocuments()
{

    nlohmann::json configJson;
    std::ifstream configFileStream("config.json");

    if (!configFileStream.is_open()) {
        throw JsonFileException("CONFIG FILE IS MISSING!");
    }

    configFileStream >> configJson;
    configFileStream.close();

    if (configJson.empty()) {
        throw JsonFileException("CONFIG FILE IS EMPTY!");
    }

    std::vector<std::string> documents;
    std::string verN = configJson["config"]["version"];

    if(verN != versionNumber)
    {
        throw JsonFileException("WRONG APPLICATION VERSION!");
    }

        
    for (const auto& file : configJson["files"])
    {
        std::string path = file;
        std::ifstream input(path);
        if (input.is_open()) {

            std::string buffer;
            while (std::getline(input, buffer))
            {
                documents.push_back(buffer);
            }
            input.close();

        } else
        {
            std::cerr << "Failed to open file: " << file << std::endl;
        }
    }

    std::cout << "Documents Received.\n";
    return documents;
}

int ConverterJSON::getResponsesLimit()
{
    nlohmann::json configJson;
    std::ifstream configFileStream("config.json");

    if (!configFileStream.is_open()) {
        throw JsonFileException("CONFIG FILE IS MISSING!");
    }

    configFileStream >> configJson;

    if (configJson.empty()) {
        throw JsonFileException("CONFIG FILE IS EMPTY!");
    }

    configFileStream.close();

    int maxRequest = configJson["config"]["max_responses"];

    return maxRequest;

}

std::vector<std::string> ConverterJSON::getRequests()
{

    nlohmann::json requestsJson;
    std::ifstream configFileStream("requests.json");

    if (!configFileStream.is_open()) {
        throw JsonFileException("REQUESTS FILE IS MISSING!");
    }

    configFileStream >> requestsJson;

    if (requestsJson.empty()) {
        throw JsonFileException("REQUESTS FILE IS EMPTY");
    }

    configFileStream.close();

    std::vector<std::string> reqVector;

    if(requestsJson.find("requests") != requestsJson.end() && requestsJson["requests"].is_array())
    {
        for ( const auto& request : requestsJson["requests"])
        {
            if(request.is_string())
            {
                reqVector.push_back(request);
            }
        }
    }

    return reqVector;
}

std::vector<std::vector<std::pair<size_t, double>>> ConverterJSON::convertToPairVector
                                (const std::vector<std::vector<RelativeIndex>>& input)
{
    std::vector<std::vector<std::pair<size_t, double>>> result;

    for (const auto& innerVector : input) {
        std::vector<std::pair<size_t, double>> convertedVector;

        for (const auto& relIndex : innerVector) {
            
            convertedVector.emplace_back(relIndex.docId, relIndex.rank);
        }

        result.push_back(convertedVector);
    }

    return result;
}


void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<size_t, double>>>& answers)
{
    int maxResponses = getResponsesLimit();
    nlohmann::json answersJson;
    std::ifstream configFileStream("answers.json");
    if (!configFileStream.is_open()) {
        std::ofstream createFile("answers.json", std::ios::out);
        createFile.close();
        configFileStream.open("answers.json");
        if (!configFileStream.is_open()) {
            throw JsonFileException("ANSWERS FILE IS MISSING!");
        }
    }
    configFileStream >> answersJson;
    configFileStream.close();

    if (!answersJson.empty())
    {
        answersJson.clear();
    }

    for (int i = 0; i < answers.size(); ++i) {
        nlohmann::json answer;

        if (answers[i].empty()) {
            answer["result"] = "false";
        }
        else {
            answer["result"] = "true";
            
                nlohmann::json relevanceArray;

                for (int j = 0; j < answers[i].size(); ++j) {
                    if(j + 1 > maxResponses)
                    {
                        break;
                    }
                    nlohmann::json relevanceEntry;
                    relevanceEntry["docId"] = answers[i][j].first;
                    relevanceEntry["rank"] = answers[i][j].second;
                    relevanceArray.push_back(relevanceEntry);
                }
                answer["relevance"] = relevanceArray;        
            
        }
        answersJson["request00" + std::to_string(i + 1)] = answer;
    }

    std::ofstream answers_file("answers.json");
    answers_file << nlohmann::json{ {"answers", answersJson} }.dump(4);
    answers_file.close();
    std::cout << "The results of search have been put in answers.json file." << std::endl;

}


std::string ConverterJSON::programName()
{
    nlohmann::json configJson;
    std::ifstream configFileStream("config.json");

    if (!configFileStream.is_open()) {
        throw JsonFileException("CONFIG FILE IS MISSING!");
    }

    configFileStream >> configJson;

    if (configJson.empty()) {
        throw JsonFileException("CONFIG FILE IS EMPTY!");
    }

    configFileStream.close();

    std::string name = configJson["config"]["name"];

    return name;
}

int ConverterJSON::getUpdateTime()
{
    nlohmann::json configJson;
    std::ifstream configFileStream("config.json");

    if (!configFileStream.is_open()) {
        throw JsonFileException("CONFIG FILE IS MISSING!");
    }

    configFileStream >> configJson;

    if (configJson.empty()) {
        throw JsonFileException("CONFIG FILE IS EMPTY!");
    }

    configFileStream.close();

    int time = configJson["config"]["Update time of the database"];

    return time;
}

void ConverterJSON::addFileToConfig(const std::string& filePath)
{
    nlohmann::json configJson;
    std::ifstream configFileStream("config.json");
    if (!configFileStream.is_open()) {
        throw JsonFileException("CONFIG FILE IS MISSING!");
    }

    configFileStream >> configJson;

    if (configJson.empty()) {
        throw JsonFileException("CONFIG FILE IS EMPTY!");
    }
    configFileStream.close();

    configJson["files"].push_back(filePath);

    
    std::ofstream outFileStream("config.json");
    if (!outFileStream.is_open()) {
        throw JsonFileException("COULDN'T OPEN CONFIG FILE FOR WRITING!");
    }
    outFileStream << configJson << std::endl;
    outFileStream.close();

}
void ConverterJSON::addRequest(const std::string& request)
{
    nlohmann::json configJson;
    std::ifstream configFileStream("requests.json");
    if (!configFileStream.is_open()) {
        throw JsonFileException("REQUEST FILE IS MISSING!");
    }

    configFileStream >> configJson;

    configFileStream.close();

    configJson["requests"].push_back(request);

   
    std::ofstream outFileStream("requests.json");
    if (!outFileStream.is_open()) {
        throw JsonFileException("COULDN'T OPEN REQUEST FILE FOR WRITING!");
    }
    outFileStream << configJson << std::endl;
    outFileStream.close();
}
