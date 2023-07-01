#ifndef HTTPLIB_NET_URL_H
#define HTTPLIB_NET_URL_H
#include <string>
#include <string_view>
#include <optional>
#include <system_error>
#include <variant>
#include <algorithm>
#include "expected.h"

namespace http
{
    enum class url_parser_status
    {
        ok = 0,
        empty_uri = 1,
        invalid_control_chars = 2,
        url_schema_error = 3,
        generic_failure = 4
    };


    struct credentials
    {
        ///
        ///  Constructor with a single credential
        ///  @param username your username 
        ///  
        credentials(const std::string& username):  username_{username}, password_{std::nullopt} {

        }
        ///
        ///  Constructor with a credentials
        ///  @param username your username 
        ///  @param password your password
        /// 
        credentials(const std::string& username, std::string& password): username_{username}, password_{password} {

        }
        ///
        /// Request username
        /// @param username request username
        /// 
        std::string username() const { return username_;}
        ///
        /// Password
        /// @param password  request password
        ///
        std::optional<std::string> password() const { return password_;}
        private:
        std::string username_;
        std::optional<std::string> password_;
    };
    ///
    /// A URL represents a parsed URL.
    /// The form of a URL is:
    ///      [scheme:][//[userinfo@]host][/]path[?query][#fragment]
    ///
    /// URLs that do not start with a slash after the scheme are interpreted as:
    ///
    ///      scheme:opaque[?query][#fragment]
    ///
    class URL final
    {
    public:
        URL() = default;

        [[maybe_unused]] std::string scheme() const;
        std::string opaque() const;
        std::optional<credentials> user() const;
        std::string host() const;
        std::optional<unsigned int> port() const;
        std::optional<std::string> path() const;
        std::optional<std::string> query() const;
        std::optional<std::string> raw_query() const;
        std::optional<std::string> fragment() const;
        std::string str() const;

    private:
        std::string protocol_;
        std::optional<credentials> user_data_;
        std::string host_;
        std::optional<unsigned int> port_;
        std::optional<std::string> path_;
        std::optional<std::string> query_;
        std::optional<std::string> fragment_;
    };
}
#endif