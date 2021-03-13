#pragma once 
#include <string_view> 
#include "socket.h"

Socket::Req req_ref(const char *s, int length = 1024)
{
    Socket::Req req;
    std::string method;
    std::string host; 
    std::string path;
    std::string a;
    a = static_cast<std::string>(s); 
    int f = a.find(' ');
    method = a.substr(0, f); 
    a = a.substr(f + 1, length); 
    f = a.find(' ');
    path = a.substr(0, f); 
    a = a.substr(f + 1, length);
    int k = a.find("Host:"); 
    a = a.substr(k + 6, length); 
    host = a.substr(0, a.find(' '));
    req.method = method; 
    req.host = host; 
    req.path = path;  
    return req; 
}

