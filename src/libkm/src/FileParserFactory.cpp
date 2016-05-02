/* 
 * File:   FileParserFactory.cpp
 * Author: veraalva
 * 
 * Created on April 11, 2016, 12:50 PM
 */
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <fstream>

#include "FileParserFactory.h"
#include "cstring.h"

using namespace std;
using namespace parsers;

FileParserFactory::FileParserFactory() {
    this->closeFile = false;
    this->bufferSize = 10000000;
    this->currPosition = 0;
    this->backup = false;
    this->line = "";
}

FileParserFactory::~FileParserFactory() {
    if (this->closeFile && this->fileToParse.is_open()) this->fileToParse.close();
}

void FileParserFactory::clean() {
    if (this->closeFile && this->fileToParse.is_open()) this->fileToParse.close();
    this->closeFile = false;
    this->words.clear();
    this->line.erase();
    this->backup = false;
    this->bufferSize = 10000000;
    this->buffer.erase();
    this->currPosition = 0;
}

bool FileParserFactory::iterate(std::string dontStartWith) {
    if (!fileToParse.is_open()) {
        throw exceptions::FileNotFoundException("Can't do an iteration in a NULL file");
    }
    if (currPosition == std::string::npos) return false;
    while (1) {
        if (currPosition == 0) fileToParse.read(&buffer[0], bufferSize);
        size_t pos = buffer.find_first_of("\n", currPosition);
        if (pos != std::string::npos && pos <= static_cast<size_t>(fileToParse.gcount())) {
            if (backup) line += buffer.substr(currPosition, pos - currPosition);
            else line = buffer.substr(currPosition, pos - currPosition);
            backup = false;
            currPosition = pos + 1;
            if (!lineStartWith(dontStartWith)) return true;
        } else {
            if (!backup) {
                line.erase();
                backup = true;
            }
            line += buffer.substr(currPosition, fileToParse.gcount() - currPosition);
            if (fileToParse.eof()) {
                currPosition = std::string::npos;
                if (!lineStartWith(dontStartWith) &&
                        !lineStartWith("\n") &&
                        !line.empty()) return true;
                return false;
            }
            currPosition = 0;
        }
    }
    return false;
}

bool FileParserFactory::iterate(std::string dontStartWith, std::string delimiters) {
    while (iterate(dontStartWith)) {
        cstring::split(line, delimiters, words);
        return true;
    }
    return false;
}


