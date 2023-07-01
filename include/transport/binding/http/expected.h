#ifndef HTTPLIB_EXPECTED_H
#define HTTPLIB_EXPECTED_H
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
#include <utility>
#include <optional>
namespace http {
    template <typename T, typename V>
    class expected
    {
    public:
        expected(const T &result)
        {
            _value = std::nullopt;
            _error = result;
        }
        expected(const T &result, const V &v)
        {
            _value = std::make_optional(v);
            _error = result;
        }
        expected(const T &result, const std::optional<V> &v)
        {
            _value = v;
            _error = result;
        }
        expected(const expected &source) : _value(source._value), _error(source._error) {}
        expected &operator=(const expected &source)
        {
            if (this != &source)
            {
                _value = source._value;
                _error = source._error;
            }
            return *this;
        }
        expected &operator=(expected &&source)
        {
            if (this != &source)
            {
                _value = std::move(source._value);
                _error = std::move(source._error);
            }
            return *this;
        }
        expected(expected &&vr)
        {
            _value = std::move(vr._value);
            _error = std::move(vr._error);
        }
        ~expected() = default;
        auto value() const {

            return _value.value();
        }
        bool has_value() const { return _value.has_value(); }
        T result() const { return _error; }

    private:
        template <typename K, typename Z>
        friend std::pair<K, Z> value(const expected<K, Z> &v);
        std::optional<V> _value{std::nullopt};
        T _error;
    };
    template <typename K, typename Z>
    std::pair<K, Z> value(const expected<K, Z> &v)
    {
        return {v._error, v._value.value()};
    }
    template <class T>
    using status = expected<T, int>;
    using http_status = status<int>;
}
#endif