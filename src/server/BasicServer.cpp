#include "BasicServer.hpp"
#include <unistd.h>
#include <utility>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

void BasicServer::add_method( const std::string& url, AbstractServerMethod* method){
    m_hooks.insert(std::make_pair(url, method));
}

BasicServer::~BasicServer(){
    for(const auto& p : m_hooks){
        if(p.second)
            delete p.second;
    }
}