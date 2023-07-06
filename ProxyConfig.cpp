//
// Created by sigsegv on 7/6/23.
//

#include "ProxyConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "ProxyCommand.h"

ProxyConfig::ProxyConfig(const std::string &filename) {
    std::ifstream configFileStream{filename};
    nlohmann::json jsonData = nlohmann::json::parse(configFileStream);
    {
        auto iterator = jsonData.find("dl");
        if (iterator != jsonData.end()) {
            auto &dynamicLinkerItem = *iterator;
            if (dynamicLinkerItem.is_string()) {
                dynamicLinker = dynamicLinkerItem;
            }
        }
    }
    {
        auto iterator = jsonData.find("cc");
        if (iterator != jsonData.end()) {
            auto &ccItem = *iterator;
            if (ccItem.is_string()) {
                cc = ccItem;
            }
        }
    }
    {
        auto iterator = jsonData.find("cxx");
        if (iterator != jsonData.end()) {
            auto &cxxItem = *iterator;
            if (cxxItem.is_string()) {
                cxx = cxxItem;
            }
        }
    }
}

void ProxyConfig::Apply(ProxyCommand &proxyCommand) const {
    if (!dynamicLinker.empty() && proxyCommand.IsLinking()) {
        std::string opt{"-Wl,-dynamic-linker="};
        opt.append(dynamicLinker);
        proxyCommand.InsertParameter(opt);
    }
}
