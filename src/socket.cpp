#include "socket.h"
#include <iostream>

std::string date_time() 
{
    time_t now = time(0);
    std::string t = ctime(&now); 
    return t;
}

const std::string format(Socket::Res r) 
{
    std::string main = "HTTP/1.1 "; 
    main.append(std::to_string(r.status_code));
    main.append(" OK\n");
    main.append("Date: " + date_time() + " GMT\n");
    if (r.content_type == Socket::Content_Type::TEXT_HTML)
    {
        main.append("Content-Type: " + std::string{ "text/html\n" });
    } 
    main.append("Content-Length: " +  std::to_string(r.content.length()) + "\n"); 
    main.append("\n");
    main.append(r.content);
    return main;
}

void Socket::init(int port ) 
{
    try 
    {
        int opt = 1; 
        int sock_des = socket(AF_INET, SOCK_STREAM, 0); 
        if (sock_des == 0)
            throw "socket desc error";
        int sockopt = setsockopt(sock_des, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 
        if (sockopt)
            throw "socket opt error";
        this->addr.sin_port = htons( 3000 ); 
        this->addr.sin_addr.s_addr = INADDR_ANY; 
        this->addr.sin_family = AF_INET;
        int addrlen = sizeof(this->addr);
        int b = bind(sock_des, (struct sockaddr *)&this->addr, addrlen); 
        if (b < 0)
            throw "binding failed";
        int l = listen(sock_des, 4); 
        if (l < 0)
            throw "listening failed";
        Socket::Res r;
        r.status_code = 200;
        r.content_type = Socket::Content_Type::TEXT_HTML;
        std::vector<std::pair<std::string , std::string>> header; 
        std::pair<std::string, std::string> kk("Authorization", "None");
        header.push_back(kk); 
        r.headers = header;
        std::string content = "Hello World!"; 
        r.content = content;
        std::string k = format(r);
        const char *buff = k.c_str(); 

        int new_socket = accept(sock_des, (struct sockaddr *)&this->addr, (socklen_t *)&addrlen);
        if (new_socket < 0)
            throw "new sock error"; 
        int s = send(new_socket, buff, k.length(), 0);
    } catch(const char *msg)
    {
        std::cout << msg;
    }
}

