#ifndef HTTPLIB_CLIENT_H
#define HTTPLIB_CLIENT_H
/**
* Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
* All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "common.h"
#include "expected.h"
#include "url.h"

namespace http
{
    struct http_response
    {
        beast::flat_buffer buffer;
       // http::response<http::dynamic_body> res;
    };
    using form_items = std::map<std::string, std::vector<std::string>>;

    class http_client
    {
    public:
        http_client() = default;
        http_client(const http_context &ctx) : context_(ctx) {}

        std::future<http_response> get(const URL &uri);
        std::future<http_response> get(const URL &uri, std::map<std::string, std::string> &&headers);
        std::future<http_response> head(const URL &uri);
        std::future<http_response> post(const URL &uri, const std::string_view &content_type, std::streambuf &&buffer);
        std::future<http_response> post_form(const URL &uri, form_items &&buffer);

    private:
        void init_client() {}
        boost::asio::io_context ioc;
        // These objects perform our I/O
        tcp::resolver resolver{ioc};
        tcp::socket socket{ioc};
        http_context context_;
    };
};

#endif