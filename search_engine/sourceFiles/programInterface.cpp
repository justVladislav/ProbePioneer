#include "programInterface.h"
#include <atomic>


ProgramInterface::ProgramInterface()
{
    converter = std::make_shared<ConverterJSON>();
    invIndex = std::make_shared<InvertedIndex>();
    server = new SearchServer(*invIndex);
}

std::atomic<bool> terminate_threads(false);

void ProgramInterface::runUpdateDocsThread() {

    while (!terminate_threads) {
        invIndex->updateDocumentBase(converter->getTextDocuments());
        int time = converter->getUpdateTime();
        std::this_thread::sleep_for(std::chrono::minutes (time));
    }
}
void ProgramInterface::runSearchServer() {
    while (!terminate_threads) {
        queries_input = converter->getRequests();
        try {
            searchResult = server->search(queries_input);
            queries_input.clear();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

        int time = converter->getUpdateTime();
        std::this_thread::sleep_for(std::chrono::minutes(time));
    }
}

void ProgramInterface::programFace( std::thread& t1,  std::thread& t2) {
    std::string command = "";

    std::cout << "Starting Program " << converter->programName() << std::endl;

    while (command != "exit") {
        std::cout << "Enter the command: (addFile, addReq, search, update, put, exit)" << std::endl;

        std::cin >> command;
        if (command == "addFile") {
            std::cin.get();
            std::cout << "Please Enter the Path to the File(relative or absolute Path)\n";
            std::string path;
            std::getline(std::cin, path);
            converter->addFileToConfig(path);
        } else if (command == "addReq") {
            std::cin.get();
            std::cout << "Please Enter the Request:\n";
            std::string request;
            std::getline(std::cin, request);
            converter->addRequest(request);
        } else if (command == "search") {
            {
                std::unique_lock<std::mutex> lock(results_mutex);
                queries_input = converter->getRequests();
                searchResult = server->search(queries_input);
                queries_input.clear();

            }

        } else if (command == "update") {
            invIndex->updateDocumentBase(converter->getTextDocuments());

        } else if (command == "put") {
            std::unique_lock<std::mutex> lock(results_mutex);
            converterResult = converter->convertToPairVector(searchResult);
            converter->putAnswers(converterResult);
            converterResult.clear();
            searchResult.clear();
        }
    }

    terminate_threads = true;
    t1.detach();
    t2.detach();


}