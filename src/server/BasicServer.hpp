#pragma once
#include <EssaUtil/UString.hpp>
#include <cstdint>
#include <map>
#include <vector>
#include "../rest/AbstractServerMethod.hpp"

class BasicServer {
    uint16_t m_port = 8000;
    std::map<std::string, AbstractServerMethod> m_hooks;
protected:
    void add_method( const std::string url,  AbstractServerMethod const& method);

public:
    BasicServer() = default;

    uint16_t get_port() const { return m_port; }
    void set_port(uint16_t _port) { m_port = _port; }

    virtual void run() = 0;

    virtual ~BasicServer() = default;
};