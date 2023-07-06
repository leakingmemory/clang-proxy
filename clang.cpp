//
// Created by sigsegv on 6/24/23.
//

#include "ProxyCommand.h"
#include "ProxyConfig.h"

int main(int argc, const char * const * argv) {
    ProxyCommand proxyCommand{argc, argv};
    ProxyConfig config{};
    config.Apply(proxyCommand);
    proxyCommand.RunTool(config.GetCc());
}
