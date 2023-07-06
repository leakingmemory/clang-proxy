//
// Created by sigsegv on 7/6/23.
//

#ifndef CLANG_PROXY_PROXYCONFIG_H
#define CLANG_PROXY_PROXYCONFIG_H

#include <string>

class ProxyCommand;

class ProxyConfig {
private:
    std::string dynamicLinker;
    std::string cc{"clang"};
    std::string cxx{"clang++"};
public:
    ProxyConfig(const std::string &filename);
    ProxyConfig() : ProxyConfig("/etc/sys-clang-proxy.conf") {}
    [[nodiscard]] std::string GetDynamicLinker() const {
        return dynamicLinker;
    }
    [[nodiscard]] std::string GetCc() const {
        return cc;
    }
    [[nodiscard]] std::string GetCxx() const {
        return cxx;
    }
    void Apply(ProxyCommand &) const;
};


#endif //CLANG_PROXY_PROXYCONFIG_H
