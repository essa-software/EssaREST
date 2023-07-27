#pragma once

#include <string>
class AbstractServerResponse{
    std::string m_uri;
    std::string m_data;
protected:
    virtual std::string raw_data() const = 0;
    std::string Data() const{return m_data;}
    void set_data(const std::string& _data){m_data = _data;}
public:
    AbstractServerResponse(const std::string& _uri) : m_uri(_uri){};
    std::string Uri() const{return m_uri;}

    virtual ~AbstractServerResponse() = default;
};