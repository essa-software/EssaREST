#pragma once

#include <functional>
#include <string>
#include "AbstractClientRequest.hpp"

class AbstractServerMethod{
    const std::string m_uri;
public:
    AbstractServerMethod(const std::string& _uri) : m_uri(_uri){}

    std::string Uri() const {return m_uri;}

    virtual ~AbstractServerMethod() = default;
};
