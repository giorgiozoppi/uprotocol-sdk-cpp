#ifndef HTTPLIB_FAST_STRING_H
#define HTTPLIB_FAST_STRING_H
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
#include <cstdint>
namespace http
{
    constexpr uint8_t MAX_FAST_STRING = 255;

    /// forward declaration.

    template <std::uint8_t N>
    class fast_string;
    template <std::uint8_t N>
    bool operator==(const fast_string<N> &first, const fast_string<N> &second) {
        bool data{true};
        if (first.length() != second.length()) {
            return false;
        }
        for (size_t i = 0; i < first.length(); i++) {
            data = data && (first[i] == second[i]);
        }
        return data;
    }
    template <std::uint8_t N>
    bool operator!=(const fast_string<N> &first, const fast_string<N> &second) {
        bool data{false};
        if (first.length() != second.length()) {
            return true;
        }
        for (size_t i = 0; i < first.length(); i++) {
            data = data && (first[i] != second[i]);
        }
        return data;
    }
    ///
    ///  fast_string is a stack allocated string. We're aware of small object optimization of C++17
    ///  but we'd like to have the control.
    ///
    template <std::uint8_t N>
    class fast_string
    {
        template <std::uint8_t K>
        class fast_string_iterator

        {
        public:
            /// iterator constructor
            /// \param c string container
            explicit fast_string_iterator(fast_string<K> &c) : container_(c), pos_(0)
            {
            }
            /// iterator constructor and end iterator
            /// \param c string container
            /// \param end end of the string
            explicit fast_string_iterator(fast_string<K> &c, int end) : container_(c), pos_(end)
            {
            }
            /// iterator incremental operator
            fast_string_iterator &operator++()
            {
                if (pos_+1 > container_.length_) {
                    pos_ = fast_string::npos;
                } else {
                    pos_++;
                }
                return *this;
            }
            /// iterator incremental operator

            fast_string_iterator &operator++(int j)
            {
                if (pos_+j > container_.length_) {
                    pos_ = fast_string::npos;
                } else {
                    pos_ = pos_++;
                }
                return *this;
            }
            /// iterator decremental operator
            fast_string_iterator &operator--(int s)
            {
                if (pos_ -s <=0) {
                    pos_ = 0;
                } else {
                    pos_ = pos_ - s;
                }
                return *this;
            }
            /// iterator decremental operator
            fast_string_iterator &operator-=(int s)
            {
                if (pos_ -s <=0) {
                    pos_ = 0;
                } else {
                    pos_ = pos_ - s;
                }
                return *this;
            }
            /// iterator incremental operator
            fast_string_iterator &operator+=(int j)
            {
                pos_ = (pos_ + j > container_.length_) ? fast_string::npos : pos_++;
                return *this;
            }
            char operator[](int k)
            {
                if (pos_ == fast_string::npos)
                {
                    throw std::out_of_range("no valid position");
                }
                return container_[k];
            }
            char operator*()
            {
                if (pos_ == fast_string::npos)
                {
                    throw std::out_of_range("no valid position");
                }
                return container_[pos_];
            }
            bool operator==(fast_string_iterator other) const { return other.pos_ == pos_; }
            bool operator!=(fast_string_iterator other) const { return other.pos_ != pos_; }

            // iterator traits
            using difference_type = int;
            using value_type = char;
            using pointer = const char *;
            using reference = const char &;
            using iterator_category = std::random_access_iterator_tag;

        private:
            fast_string<K> &container_; // container in which elements are inserted
            int pos_{0};
        };

    public:
        using iterator = fast_string_iterator<N>;
        static const int npos = -1;

        fast_string(std::string_view s)
        {
            std::size_t to_copy{0};
            uint8_t current_size = static_cast<std::size_t>(s.size());
            to_copy = (current_size > N) ? N : current_size;
            length_ = to_copy;
            std::memcpy(data_, s.data(), length_);
            // a string shall be always null terminated.
            data_[length_] = '\0';
        }

        iterator begin()
        {
            return fast_string_iterator<N>(*this);
        }
        iterator end()
        {
            return fast_string_iterator<N>(*this, length_);
        }
        size_t length() const { return length_; }
        bool empty() const { return length_ == 0; }
        char operator[](size_t pos) const
        {
            if (pos <= length_)
            {
                return data_[pos];
            }
            std::string msg{"string access out of range "};
            throw std::out_of_range(msg.c_str());
        }
        const char *data() const
        {
            return data_;
        }
        fast_string substr(size_t pos) const
        {
            return fast_string(std::string_view(*this).substr(pos));
        }
        fast_string substr(size_t pos, size_t count) const
        {
            return fast_string(std::string_view(*this).substr(pos, count));
        }

    private:
        friend bool operator== <N> (const fast_string<N> &first, const fast_string<N> &second);
        friend bool operator!= <N> (const fast_string<N> &first, const fast_string<N> &second);
        char data_[N];
        std::uint8_t length_;
    };
    template <std::uint8_t N>
    bool operator==(fast_string<N> &&first, fast_string<N> &&second)
    {
        if (first.length_ == second.length_)
        {
            return !strcmp(first.data, second.data);
        }
        return false;
    }

    template <std::uint8_t N>
    bool operator!=(fast_string<N> &&first, fast_string<N> &&second)
    {
        if (first.length_ != second.length_)
        {
            return false;
        }
        return strcmp(first.data, second.data);
    }
}

#endif //HTTPLIB_FAST_STRING_H
