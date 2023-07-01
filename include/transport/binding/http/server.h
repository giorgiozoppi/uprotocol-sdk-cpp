#ifndef HTTPLIB_SERVER_H
#define HTTPLIB_SERVER_H

#include <memory>
#include <string>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <utility>
#include <optional>
#include <binding/http/router.h>

namespace binding::http
{

    enum class http_server_status_t
    {
        OK,
        FAIL,
        STOP,
        CANNOT_OPEN_SOCKET,
        CANNOT_BIND_SOCKET,
        CANNOT_BIND_AND_LISTEN_SOCKET,
        CANNOT_LOAD_CERTIFICATES,
        CANNOT_CREATE_LOGS
    };

    class http_server : public std::enable_shared_from_this<http_server>
    {
    public:
        ///
        /// Constructor
        /// \param cntx  HTTP server context that provides the configuration for the server.
        ///
        http_server(const http_context &cntx);
        ///
        /// Constructor
        /// \param server_name  Label associated to this server
        /// \param context         HTTP server context that provides the configuration for the server.

        http_server(const std::string &server_name, const http_context &context);
        ///
        /// Destructor
        ///
        ~http_server();
        ///
        /// open the server socket and put itself on the accept.
        /// \param router router that provides the rest mapping
        /// \return an invalid status whether there's an exception
        ///
        expected<http_server_status_t, std::string> listen_serve(http_router&& router);
        ///
        /// shutdown the httpserver.
        ///
        void shutdown();

    private:
    
        expected<http_server_status_t, std::string> init_server();
        status<bool> load_certificates(ssl::context &ctx);
        void stop();
        std::string server_name_;
        http_router router_;
        http_context cntx_;
        http_server_status_t current_state_{http_server_status_t::STOP};
        std::shared_ptr<spdlog::logger> logger_;
        std::vector<std::thread> server_threads_;
    };
} // namespace http
#endif