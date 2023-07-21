#include "HttpClientRequest.hpp"
#include "EssaUtil/UString.hpp"
#include <sstream>
#include <string>

std::string HttpClientRequest::operator[](std::string key) const{
    auto it = m_headers.find(key);

    if(it != m_headers.end()){
        return it->second;
    }else{
        return "";
    }
}

HttpResponseCode HttpClientRequest::parse(const char* req){
    std::stringstream ss;
    ss << req;

    std::string method, path, version;
    ss >> method >> path >> version;
    
    m_uri = path;

    if(version != "HTTP/1.1"){
        return HttpResponseCode::HTTPVersionNotSupported;
    }

    std::string line;
    while (std::getline(ss, line)) {
        std::string::size_type pos = line.find(": ");
        if(pos == std::string::npos){
            m_body = ss.str();
        }
        
        std::string header = line.substr(0, pos);
        std::string content = line.substr(pos + 2);

        m_headers[header] = content;
    }

    return HttpResponseCode::OK;
}

HttpResponseCode HttpGETClientRequest::parse(const char* req){
    HttpResponseCode res = HttpClientRequest::parse(req);
    if(res != HttpResponseCode::OK) return res;

    std::stringstream ss;
    ss << req;

    std::string method, path, version;
    ss >> method >> path >> version;

    if(method != "GET"){
        return HttpResponseCode::MethodNotAllowed;
    }

    return HttpResponseCode::OK;
}
