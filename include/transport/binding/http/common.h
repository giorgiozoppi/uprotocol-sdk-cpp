#ifndef HTTPLIB_COMMON_H
#define HTTPLIB_COMMON_H

#include <map>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>  // support for loading levels from the environment variable
#include <spdlog/fmt/ostr.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>

#include "expected.h"

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>
    

namespace binding::http
{
    using loglevel_t = spdlog::level::level_enum;
    using http_header = std::map<std::string, std::vector<std::string>>;
    enum class http_method_t
    {
        GET,
        POST,
        PATCH,
        DELETE,
        PUT,
        HEAD
    };
    enum class http_protocol_t {
        HTTP_10,
        HTTP_11,
        HTTP_2    // not yet supported.
    };
    struct http_context
    {
        std::string default_host;
        std::string tls_certificate_path;
        unsigned short default_port{0};
        std::string document_root;
        std::string tls_certificate_keypath;
        int number_threads{0};
        std::string pass_key;
        loglevel_t log_level;
        std::string log_path;
        std::string log_category;
        std::string tls_dh_params;
        bool no_ssl{false};
        http_protocol_t protocol;
    };
    struct http_params {

    };
}
#endif