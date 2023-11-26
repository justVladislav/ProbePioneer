#include "programInterface.h"


int main() {

    
    std::shared_ptr<ProgramInterface> searchEngine = std::make_shared<ProgramInterface>();
    std::thread updateDocsBase(&ProgramInterface::runUpdateDocsThread, searchEngine);
    std::thread runServer(&ProgramInterface::runSearchServer, searchEngine);

    std::thread programSearchEngine([searchEngine, &updateDocsBase, &runServer]() {
        searchEngine->programFace(updateDocsBase, runServer);
    });

    programSearchEngine.join();
    return 0;
}
