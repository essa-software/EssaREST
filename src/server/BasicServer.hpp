#pragma once
#include <EssaUtil/UString.hpp>
#include <cstdint>
#include <map>
#include <vector>
#include "../rest/AbstractServerMethod.hpp"

class BasicServer {
    uint16_t m_port = 8000;
    std::map<Util::UString, AbstractServerMethod> m_hooks;
protected:
    void add_method( const Util::UString url,  AbstractServerMethod const& method);

public:
    BasicServer() = default;

    uint16_t get_port() const { return m_port; }
    void set_port(uint16_t _port) { m_port = _port; }

    virtual void run();
    void set_method( const Util::UString url,  AbstractServerMethod const& method);

    virtual ~BasicServer() = default;
};