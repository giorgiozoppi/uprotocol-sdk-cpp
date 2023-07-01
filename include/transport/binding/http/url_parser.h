#ifndef HTTPLIB_URLPARSER_H
#define HTTPLIB_URLPARSER_H
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
#include <variant>
#include <string>
#include <string_view>
#include <utility>
#include <url.h>
#include <unordered_set>

namespace http
{

  /// 
  ///  we're creating a url_parser
  /// an uri has the following structure: scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
  /// we'd use a compile state machine with  curiously recurring template pattern
  ///  We've the following states:
  ///  1. START = scheme_parser_state 
  ///  2. authority_parser_state
  ///  3. host_parser_parser_state
  ///  4. path_parser_state
  ///  5. fragment_parser_state

  class url_parser
  {
  public:
    static expected<url_parser_status, URL> parse(std::string_view url)
    {
        if (url.size() == 0) {
            return {url_parser_status::generic_failure, URL()};
        }
      return {url_parser_status::generic_failure, URL()};
    }
  };
}

#endif
