//
// Created by sigsegv on 7/6/23.
//

#ifndef CLANG_PROXY_SEARCHPATH_H
#define CLANG_PROXY_SEARCHPATH_H

#include <string>
#include <vector>

class SearchPath {
private:
    std::vector<std::string> path{};
public:
    SearchPath();
    std::string Find(std::string cmd);
};


#endif //CLANG_PROXY_SEARCHPATH_H
