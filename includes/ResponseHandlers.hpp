/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandlers.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcl <mcl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:42:45 by pmitsuko          #+#    #+#             */
/*   Updated: 2023/10/12 20:02:47 by mcl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Cgi.hpp"
#include "DeleteMethod.hpp"
#include "Libs.hpp"
#include "Location.hpp"
#include "Parser.hpp"
#include "PostMethod.hpp"
#include "Request.hpp"

typedef enum e_method_option {
    GET,
    POST,
    DELETE,
} t_method_option;

// TODO: consumir do .conf os métodos permitidos

class ResponseHandlers {
    private:
    responseData _res;

    void _initResponseData(void);
    int  _resolveOption(std::string method);
    void _getHandler(Parser &parser, HttpRequest &request, std::string port, std::string uri);
    void _postHandler(Parser &parser, HttpRequest &request, std::string port, std::string uri);
    void _deleteHandler(std::string uri);

    public:
    ResponseHandlers(void);
    ~ResponseHandlers(void);

    responseData exec(Parser &parser, HttpRequest &request);
};