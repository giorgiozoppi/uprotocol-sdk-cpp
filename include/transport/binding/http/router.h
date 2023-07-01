#ifndef HTTPLIB_ROUTER_H
#define HTTPLIB_ROUTER_H
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

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <exception>
#include <binding/http/common.h>
#include <binding/http/fast_string.h>
///
///  This header contains the implementation of an HTTP Router/Muxer
///  The main responsibility of an HTTP Muter is to match the URIs to a given handler within a given method.
///  The user will map a set of uri/method to an handler.
///  For achieving this goal we need to implement:
///   1. a better fast stack allocated string
///   2. a trie for fast url matching
///   3. an http_router class that does the dispatch.
///
///

namespace http
{


    using index_type = int16_t;
    using fast_index_type = int_fast16_t;
   
    class http_router_node
    {
        index_type found_index_;
        index_type child_lookup_;
        // substring for this node;
        fast_string<MAX_FAST_STRING> substring_;
        std::map<http_method_t, http_handler> router_handlers_;
        fast_index_type substring_length() const
        {
            return static_cast<fast_index_type>(substring_.length());
        }
        const char *substring_data() const { return substring_.data(); }
    };

    class http_router_trie
    {

    public:

        http_router_trie() : size_(0) {}
        http_router_trie(http_router_trie&&) = default;
        http_router_trie& operator=(http_router_trie&&) = default;

    private:
        std::vector<http_router_node> nodes_;
        std::vector<index_type> lookup_table_;
        index_type size_;
    };

    class http_router
    {
        public:
        http_router() {

        }
        void map([[maybe_unused]] const std::string &path, [[maybe_unused]] http_method_t method, [[maybe_unused]] http_handler handler) {}
        private:
        http_router_trie mapping_tree_;
    };
}
#endif