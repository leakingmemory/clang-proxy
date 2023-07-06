//
// Created by sigsegv on 7/6/23.
//

#include "SearchPath.h"
extern "C" {
#include <unistd.h>
}
#include <filesystem>

SearchPath::SearchPath() {
    const char *pathv = secure_getenv("PATH");
    if (pathv != nullptr) {
        std::string paths{pathv};
        while (!paths.empty()) {
            auto pos = paths.find(':');
            if (pos != std::string::npos) {
                std::string sub = paths.substr(0, pos);
                path.emplace_back(sub);
                sub = paths.substr(pos + 1);
                paths = sub;
            } else {
                path.emplace_back(paths);
                paths = "";
            }
        }
    }
}

std::string SearchPath::Find(std::string cmd) {
    if (cmd.starts_with("/") || cmd.starts_with("./")) {
        return cmd;
    }
    for (const auto strp : this->path) {
        std::filesystem::path path{strp};
        path = path / cmd;
        if (exists(path)) {
            return path;
        }
    }
    return "";
}
