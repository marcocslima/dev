/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/12 14:11:50 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AResponse.hpp"
#include "DeleteMethod.hpp"
#include "Libs.hpp"
#include "Location.hpp"
#include "Poll.hpp"
#include "PostMethod.hpp"
#include "Request.hpp"
#include "ResponseHandlers.hpp"
#include "Socket.hpp"

struct SocketInfo {
    std::string ipAddress;
    std::string port;

    SocketInfo(const std::string &ip, std::string p) : ipAddress(ip), port(p) {}
};

class Server {
    private:
    std::vector<SocketInfo> _socketsInfo;
    HttpRequest             _request;
    Parser                  _parser;
    std::vector<Socket *>   _sockets;
    Poll                    _poll;
    bool                    _verbose;
    std::string             _defaultHtmlContent;
    Location                _location;
    ResponseHandlers        _responseHandlers;

    public:
    Server(void);
    ~Server(void);

    void initParser(const char *configFile);
    void initSockets(void);
    void initPoll(void);
    int  run(void);
    bool acceptNewConnection(size_t i);
    void processClientData(int clientSocket);
    void closeServer(void);

    void setVerbose(bool verbose);
};