# ProbePioneer
A local file search engine.

This project is a local search engine written in C++. It is designed to scan and index files on your computer for subsequent searching and extraction of information from them.

## Description

This program consists of four distinct classes, each having its own header and executable file. The classes are organized as follows:

ConverterJSON - converterJson.h and converterJson.cpp
"ConverterJSON Class functionalities:

Reading Configuration Data from JSON: Parses and retrieves configuration data stored in JSON format.
Converting Queries to JSON Format: Converts incoming queries into JSON format for processing.
Generating Responses in a Defined JSON Structure: Constructs and outputs responses in a predetermined JSON structure."

InvertedIndex - invertedIndex.h.h and invertedIndex.h.cpp
InvertedIndex Class functionality:
**Running File Indexing in Separate Threads:** Initiates the indexing process for each file listed in the configuration file, running each indexation task in separate threads.
**Parsing Text Blocks from the ConverterJSON Class into Individual Words:** Divides the received text blocks from the ConverterJSON class into separate words for further processing.
**Collecting All Unique Words per Document and Counting Their Occurrences:** Gathers all unique words within a document and counts their occurrences.
**Maintaining a Frequency Dictionary:** Manages a dictionary (`freq_dictionary`) where:
    - If a word is absent in the dictionary, it's added with a count value of one.
    - If the word is present, its count is incremented by the number of occurrences in the document. The count value represents the frequency of the word in the document.
**Storing Word-Document Associations:** Records word-document associations in the `freq_dictionary` collection, indicating the frequency of word occurrences within specific documents.
This description covers the functionalities of the class, including indexing files in separate threads, splitting text blocks into individual words, counting unique words and their frequencies in documents, as well as maintaining a dictionary of word frequencies.

SearchServer - relativeIndex.h and relativeIndex.cpp
SearchServer Class functionalities:
**Splitting the Search Query into Individual Words:** Breaks down the search query into separate words.
**Creating a List of Unique Words:** Forms a list containing unique words extracted from the query.
**Sorting Words by Increasing Frequency of Occurrence:** Arranges words in ascending order based on their frequency in the `freq_dictionary` field, from the least frequent to the most frequent.
**Finding Documents Containing the Least Frequent Word:** Identifies all documents containing the first (least frequent) word from the sorted list.
**Matching Subsequent Words with the Document List:** Continues to search for matches between subsequent words and this list of documents.
**Handling Cases with Zero Matching Documents:** If no documents remain after processing all words, outputs the count of found documents as 0 and records the result as false.
**Calculating Relevance for Each Document:** If documents are found, calculates the relevance for each document and displays it in the 'rank' field of the query response. This calculation involves determining the absolute relevance for each document, which is the sum of all 'count' values of words found in the document from the `freq_dictionary` collection. The absolute relevance is then divided by the maximum absolute relevance among all documents found.
This description outlines the step-by-step process the class performs, including word manipulation, sorting by frequency, document retrieval based on word frequency, relevance calculation, and output generation based on the query's criteria.

ProgramInterface - programInterface.h and programInterface.cpp
ProgramInterface Class functionalities:
The `ProgramInterface` class serves as an interface for managing various operations within the program. The interface is initialized through `main.cpp` with the inclusion of `#include "programInterface.h"`.

### Constructor
- **ProgramInterface():** Initializes various components necessary for the program's functionality, such as:
    - `converter`: Utilizes the `ConverterJSON` class to handle JSON conversions.
    - `invIndex`: Manages the inverted index through the `InvertedIndex` class.
    - `server`: Sets up the `SearchServer` for search operations based on the inverted index.

### Methods
- **runUpdateDocsThread():** Runs a thread that updates the document base used by the inverted index at regular intervals specified by `getUpdateTime()` from the `converter` object.
- **runSearchServer():** Manages another thread that handles incoming search requests (`getRequests()`) using the `server` object. It catches exceptions that might occur during the search process.
- **programFace(std::thread& t1, std::thread& t2):** Controls the program's user interface, allowing interaction with the system. Commands include:
    - `addFile`: Adds a file to the configuration by specifying its path.
    - `addReq`: Adds a request/query to the system for subsequent search operations.
    - `search`: Initiates a search operation based on the existing queries.
    - `update`: Manually triggers an update to the document base.
    - `put`: Processes and stores search results for retrieval.

### Usage
The `ProgramInterface` class is instantiated and utilized within the `main` function to initialize the program's interface and manage its functionalities. It initializes essential components and handles various operations such as file additions, query processing, search operations, and data updates, providing an interactive command-line interface for users to interact with the system.

Each class encapsulates specific functionalities and is implemented across its respective header and source files for better organization and modularity of the codebase.
## Installation

1. Clone the repository:
    ```shell
    git clone https://github.com/your_username/your_repository.git
    ```

2. Make sure you have a C++ compiler and the nlohmann::json library installed.

3. Build the project using your compiler.

## Usage

1. Run the program.

2. Index the folders and files you want to include in the search.

3. Conduct searches for keywords or phrases to extract information from files.
