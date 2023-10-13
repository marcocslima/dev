/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandlers.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcl <mcl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:41:36 by pmitsuko          #+#    #+#             */
/*   Updated: 2023/10/13 05:35:18 by mcl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseHandlers.hpp"

ResponseHandlers::ResponseHandlers(void) {}

ResponseHandlers::~ResponseHandlers(void) {}

responseData ResponseHandlers::exec(Parser &parser, HttpRequest &request)
{
    this->_initResponseData();
    // TODO: check server_Name
    // TODO: check method
    switch (this->_resolveOption(request.getMethod())) {
        case GET:
            this->_getHandler(parser, request, request.getPort(), request.getUri());
            break;
        case POST:
            this->_postHandler(parser, request, request.getPort(), request.getUri());
            break;
        case DELETE:
            this->_deleteHandler(request.getUri());
            break;
        default:
            break;
    }
    return (this->_res);
}

void ResponseHandlers::_initResponseData(void)
{
    this->_res.statusCode    = "";
    this->_res.contentType   = "";
    this->_res.content       = "";
    this->_res.contentLength = -1;
}

int ResponseHandlers::_resolveOption(std::string method)
{
    std::string option[] = {"GET", "POST", "DELETE"};
    int         i        = 0;

    while (i < 3 && method != option[i])
        i++;
    return (i);
}

void ResponseHandlers::_getHandler(Parser      &parser,
                                   HttpRequest &request,
                                   std::string  port,
                                   std::string  uri)
{
    Location location;
    CGI      cgi;
    // TODO: chamar autoindex
    // TODO: chamar cgi
    cgi.executeCGI(parser, request, port);

    location.setup(parser, port, uri);
    this->_res = location.getLocationContent();
    std::cout << "ResponseHandlers::_getHandler: " << this->_res.content << std::endl;
}

void ResponseHandlers::_postHandler(Parser      &parser,
                                    HttpRequest &request,
                                    std::string  port,
                                    std::string  uri)
{

    (void)uri;
    PostMethod post_method(request);
    CGI        cgi;

    // TODO: chamar cgi
    cgi.executeCGI(parser, request, port);

    post_method.handleMethod(request.getUri());
    // TODO: preciso que retorne o responseData
}

void ResponseHandlers::_deleteHandler(std::string uri)
{
    DeleteMethod delete_method;

    delete_method.handleMethod(uri);
    // TODO: preciso que retorne o responseData
}
