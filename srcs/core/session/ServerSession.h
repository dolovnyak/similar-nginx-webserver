#pragma once

#include "Session.h"
#include "utilities.h"
#include "Config.h"

template<class CoreModule>
class ServerSession : public Session<CoreModule> {
public:
    ServerSession(int core_module_index, CoreModule* core_module, int socket,
                  const SharedPtr<ServerConfig>& server_config)
            : Session<CoreModule>(core_module_index, core_module, socket),
              server_config(server_config) {}

    ~ServerSession() {}

    bool ShouldCloseAfterResponse() const OVERRIDE {
        throw std::logic_error("ServerSession::GetResponseData() should not be called");
    }

    const std::string& GetResponseData() const OVERRIDE {
        throw std::logic_error("ServerSession::GetResponseData() should not be called");
    }

    const std::string& GetName() const OVERRIDE {
        static std::string kName = "ServerSession";
        return kName;
    }

    SessionType::Type GetType() const override {
        return SessionType::Server;
    }

    SharedPtr<ServerConfig> server_config;
};