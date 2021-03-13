#include "socket.h"
#include <iostream>
#include "utils.h"

std::string date_time() 
{
    time_t now = time(0);
    std::string t = ctime(&now); 
    return t;
}

const std::string format(const Socket::Res& res, const Socket::Req& req) 
{
    std::string main = "HTTP" + req.path + " 1.1 "; 
    main.append(std::to_string(res.status_code));
    main.append(" OK\n");
    main.append("Date: " + date_time() + " GMT\n");
    if (res.content_type == Socket::Content_Type::TEXT_HTML)
    {
        main.append("Content-Type: " + std::string{ "text/html\n" });
    } 
    main.append("Content-Length: " +  std::to_string(res.content.length()) + "\n"); 
    main.append("\n");
    main.append(res.content);
    return main;
}

void Socket::init(int port) 
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
        this->addr.sin_port = htons( port ); 
        this->addr.sin_addr.s_addr = INADDR_ANY; 
        this->addr.sin_family = AF_INET;
        int addrlen = sizeof(this->addr);
        int b = bind(sock_des, (struct sockaddr *)&this->addr, addrlen); 
        if (b < 0)
            throw "binding failed";
        int l = listen(sock_des, 4); 
        if (l < 0)
            throw "listening failed"; 
        while(true)
        {
            int new_socket = accept(sock_des, (struct sockaddr *)&this->addr, (socklen_t *)&addrlen);
            if (new_socket < 0)
                throw "new sock error"; 
            int r = read(new_socket, this->buffer, 1024); 
            Socket::Req rr = req_ref(this->buffer);
            if (this->APP.size() <= 0)
                throw "give 1 or more path";
            for (int i = 0; i < this->APP.size(); i++)
            {
                if (rr.path == (this->APP[i]).first)
                {
                    Socket::Req req; 
                    Socket::Res res; 
                    (this->APP[i]).second(req, res); 
                    if (req.method == rr.method)
                    {
                        std::string temp = format(res, req);
                        const char* ss = temp.c_str(); 
                        int s = send(new_socket, ss, temp.length(), 0);
                        if (s < 0)
                            throw "error occured while sending";
                    }
                } 
            }
            
        }
    } catch(const char *msg)
    {
        std::cout << msg;
    }
}




void Socket::app(const App* ap)
{
    this->APP = *ap;
}