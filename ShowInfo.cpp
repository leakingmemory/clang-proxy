//
// Created by sigsegv on 7/6/23.
//

#include "ShowInfo.h"
#include "ProxyCommand.h"
#include <iostream>

void ShowInfo::PrintInfo() const {
    std::cout << "Is linking: " << (proxyCommand.IsLinking() ? "Yes\n" : "No\n");
    {
        auto outputFile = proxyCommand.GetOutputFile();
        std::cout << "Output file: " << (outputFile.empty() ? "default" : outputFile) << "\n";
    }
    std::cout << "Input files: ";
    for (const auto &inputFile : proxyCommand.GetInputFiles()) {
        std::cout << inputFile;
    }
    std::cout << "\n";
}

void ShowInfo::PrintCommand() const {
    auto args = proxyCommand.GetArgs();
    auto iterator = args.begin();
    if (iterator == args.end()) {
        std::cout << "\n";
        return;
    }
    std::cout << *iterator;
    ++iterator;
    while (iterator != args.end()) {
        std::cout << " " << *iterator;
        ++iterator;
    }
    std::cout << "\n";
}
