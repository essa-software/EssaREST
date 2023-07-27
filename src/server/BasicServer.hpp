#pragma once
#include <EssaUtil/UString.hpp>
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "../rest/AbstractServerMethod.hpp"

class BasicServer {
    uint16_t m_port = 8000;
    std::map<std::string, AbstractServerMethod*> m_hooks;
protected:
    void add_method( const std::string& url, AbstractServerMethod* method);

    template<typename T, typename U>
    std::string execute_method(const std::string& url, AbstractClientRequest* req){
        auto it = m_hooks.find(url);

        if(it == m_hooks.end())
            throw std::runtime_error("Not Found");
        
        T* method = dynamic_cast<T*>(it->second);

        if(!method)
            throw std::runtime_error("Method not allowed");
        
        U* request = dynamic_cast<U*>(req);

        if(!request)
            throw std::runtime_error("Incorrect request");
        
        return method->exec(*request);
    }

public:
    BasicServer() = default;

    uint16_t get_port() const { return m_port; }
    void set_port(uint16_t _port) { m_port = _port; }

    virtual void run() = 0;

    virtual ~BasicServer();
};