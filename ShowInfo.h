//
// Created by sigsegv on 7/6/23.
//

#ifndef CLANG_PROXY_SHOWINFO_H
#define CLANG_PROXY_SHOWINFO_H

class ProxyCommand;

class ShowInfo {
private:
    ProxyCommand &proxyCommand;
public:
    ShowInfo(ProxyCommand &proxyCommand) : proxyCommand(proxyCommand) {}
    void PrintInfo() const;
    void PrintCommand() const;
};


#endif //CLANG_PROXY_SHOWINFO_H
