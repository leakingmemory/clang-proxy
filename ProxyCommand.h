//
// Created by sigsegv on 6/24/23.
//

#ifndef CLANG_PROXY_PROXYCOMMAND_H
#define CLANG_PROXY_PROXYCOMMAND_H

#include <vector>
#include <string>
#include <functional>
#include <optional>

class ProxyCommand {
private:
    std::vector<std::string> args;
    bool linking{true};
    std::string outputFile{};
    std::vector<std::string> inputFiles{};
public:
    ProxyCommand(int argc, const char * const * argv);
private:
    std::vector<std::function<void (const std::string &)>> ParseFlags(const std::string &);
    std::optional<std::function<void (const std::string &)>> ParseDoubleDash(const std::string &);
    std::optional<std::function<void (const std::string &)>> ParseFlag(char);
    bool IsSingleDashWord(const std::string &) const;
    std::optional<std::function<void (const std::string &)>> ParseSingleDashWord(const std::string &);
    void InputFile(const std::string &);
public:
    bool IsLinking() const {
        return linking;
    }
    std::string GetOutputFile() const {
        return outputFile;
    }
    std::vector<std::string> GetInputFiles() const {
        return inputFiles;
    }
    void InsertParameter(const std::string &);
    std::vector<std::string> GetArgs() const {
        return args;
    }
    void RunTool(const std::string &);
};


#endif //CLANG_PROXY_PROXYCOMMAND_H
