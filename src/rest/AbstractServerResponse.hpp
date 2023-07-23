#pragma once

#include <string>
class AbstractServerResponse{
    void* m_data;
    std::string m_uri;
protected:
    virtual const char* raw_data() const = 0;
public:
    AbstractServerResponse(std::string _uri) : m_uri(_uri){};
    void* Data() const{return m_data;}
    std::string Uri() const{return m_uri;}

    virtual ~AbstractServerResponse() = default;
};