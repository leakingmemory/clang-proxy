//
// Created by sigsegv on 7/6/23.
//

#include "ProxyCommand.h"
#include "ShowInfo.h"
#include "ProxyConfig.h"

int main(int argc, const char * const * argv) {
    ProxyCommand proxyCommand{argc, argv};
    ProxyConfig config{};
    ShowInfo showInfo{proxyCommand};
    showInfo.PrintInfo();
    config.Apply(proxyCommand);
    showInfo.PrintCommand();
}