/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcl <mcl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:36:29 by mcl               #+#    #+#             */
/*   Updated: 2023/10/12 19:53:12 by mcl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AResponse.hpp"
#include "Location.hpp"
#include "Parser.hpp"
#include "Request.hpp"
#include "Utils.hpp"
// #include <string.h>
// #include <sys/wait.h>
// #include <unistd.h>

class CGI : public HttpRequest {
    private:
    char      **_envs;
    std::string _cgi_path;

    public:
    CGI();
    ~CGI();

    std::map<std::string, std::string> assembleCGIHeaders(const HttpRequest &request);
    char                             **assembleCGIEnv(std::map<std::string, std::string> map_envs);
    std::string executeCGI(Parser &parser, HttpRequest &request, std::string port);
};
