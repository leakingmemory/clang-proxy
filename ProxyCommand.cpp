//
// Created by sigsegv on 6/24/23.
//

#include "ProxyCommand.h"
#include "SearchPath.h"
extern "C" {
#include <unistd.h>
}

ProxyCommand::ProxyCommand(int argc, const char *const *argv) : args() {
    std::vector<std::function<void (const std::string &)>> consumers{};
    bool endOfFlags{false};
    for (int i = 0; i < argc; i++) {
        std::string &arg = args.emplace_back(argv[i]);
        if (i == 0) {
            continue;
        }
        if (endOfFlags) {
            InputFile(arg);
        } else if (consumers.size() == 0) {
            if (arg != "--") {
                for (const auto &consumer: ParseFlags(arg)) {
                    consumers.emplace_back(consumer);
                }
            } else {
                endOfFlags = true;
            }
        } else {
            auto iterator = consumers.begin();
            (*iterator)(arg);
            consumers.erase(iterator);
        }
    }
}

std::vector<std::function<void(const std::string &)>> ProxyCommand::ParseFlags(const std::string &arg) {
    std::vector<std::function<void (const std::string &)>> consumers{};
    if (arg.starts_with("--")) {
        auto consumer = ParseDoubleDash(arg);
        if (consumer) {
            consumers.emplace_back(*consumer);
        }
    } else if (arg.starts_with("-")) {
        if (IsSingleDashWord(arg)) {
            auto consumer = ParseSingleDashWord(arg);
            if (consumer) {
                consumers.emplace_back(*consumer);
            }
        } else {
            auto iterator = arg.begin();
            ++iterator;
            while (iterator != arg.end()) {
                char opt = *iterator;
                auto consumer = ParseFlag(opt);
                if (consumer) {
                    consumers.emplace_back(*consumer);
                }
                ++iterator;
            }
        }
    } else {
        InputFile(arg);
    }
    return consumers;
}

std::optional<std::function<void(const std::string &)>> ProxyCommand::ParseDoubleDash(const std::string &) {
    return {};
}

std::optional<std::function<void(const std::string &)>> ProxyCommand::ParseFlag(char flag) {
    switch (flag) {
        case 'o':
            return [this] (const std::string &outputFile) {
                this->outputFile = outputFile;
            };
        case 'c':
            linking = false;
            break;
    }
    return {};
}

bool ProxyCommand::IsSingleDashWord(const std::string &arg) const {
    if (arg.starts_with("-W")) {
        return true;
    } else if (arg.starts_with("-std")) {
        return true;
    } else if (arg.starts_with("-O")) {
        return true;
    }
    return false;
}

std::optional<std::function<void(const std::string &)>> ProxyCommand::ParseSingleDashWord(const std::string &arg) {
    if (arg.starts_with("-std")) {
        if (!arg.starts_with("-std=")) {
            return [] (const std::string &) {
            };
        }
    }
    return {};
}

void ProxyCommand::InputFile(const std::string &inputFile) {
    inputFiles.emplace_back(inputFile);
}

void ProxyCommand::InsertParameter(const std::string &str) {
    auto iterator = args.begin();
    if (iterator != args.end()) {
        ++iterator;
    }
    args.emplace(iterator, str);
}

void ProxyCommand::RunTool(const std::string &cmd) {
    std::vector<std::string> args{};
    args = this->args;
    args[0] = cmd;
    std::vector<const char *> argv{};
    for (const auto &arg : args) {
        argv.emplace_back(arg.c_str());
    }
    argv.emplace_back(nullptr);
    const char **argvp = argv.data();
    SearchPath searchPath{};
    std::string filename = searchPath.Find(cmd);
    if (!filename.empty()) {
        execv(filename.c_str(), (char **) argvp);
    }
    throw std::exception();
}