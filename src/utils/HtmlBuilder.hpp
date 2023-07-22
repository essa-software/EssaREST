#pragma once

#include <array>
#include <initializer_list>
#include <ostream>
#include <string>
#include <string_view>

#include <cstddef>
#include <cstring>

class literal_str_list {
private:
    const char* const text_ptr;
    unsigned int text_size;
    const literal_str_list* const head;

    constexpr char get_char_from_head(unsigned int i, unsigned int hd_size) const {
        return (i < hd_size ? (*head)[i] : (i < (hd_size + text_size) ? text_ptr[i - hd_size] : '\0'));
    };

    static constexpr std::size_t fnv_prime = (sizeof(std::size_t) == 8 ? 1099511628211u : 16777619u);
    static constexpr std::size_t fnv_offset = (sizeof(std::size_t) == 8 ? 14695981039346656037u : 2166136261u);

    constexpr std::size_t fnv_1a_hash(unsigned int i) const {
        return (
            i == 0 ? (head != nullptr ? ((head->fnv_1a_hash(head->text_size - 1) ^ text_ptr[0]) * fnv_prime) : fnv_offset)
                   : ((fnv_1a_hash(i - 1) ^ text_ptr[i]) * fnv_prime)
        );
    };

    template<typename FwdIter> void copy_to_recurse(FwdIter& beg, FwdIter end) const {
        if (head != nullptr)
            head->copy_to_recurse(beg, end);
        for (unsigned int i = 0; (i < text_size) && (beg != end); ++i, ++beg)
            *beg = text_ptr[i];
    };

    void copy_to_recurse(char*& beg, char* end) const {
        if (head != nullptr)
            head->copy_to_recurse(beg, end);
        std::size_t sz_to_cpy = (end - beg < text_size ? end - beg : text_size);
        std::memcpy(beg, text_ptr, sz_to_cpy);
        beg += sz_to_cpy;
    };

    constexpr literal_str_list(const char* aStr, unsigned int N, const literal_str_list* aHead = nullptr)
        : text_ptr(aStr)
        , text_size(N)
        , head(aHead) {};

public:
    friend std::ostream& operator<<(std::ostream& out, const literal_str_list& str){
        return out << str.text_ptr;
    }
    template<unsigned int N>
    constexpr literal_str_list(const char (&aStr)[N], const literal_str_list* aHead = nullptr)
        : text_ptr(aStr)
        , text_size(N - 1)
        , head(aHead) {
        static_assert(N >= 1, "Invalid string literal! Length is zero!");
    };

    constexpr unsigned int size() const { return text_size + (head != nullptr ? head->size() : 0); };

    constexpr char operator[](unsigned int i) const {
        return (head != nullptr ? get_char_from_head(i, head->size()) : (i < text_size ? text_ptr[i] : '\0'));
    };

    template<unsigned int N> constexpr literal_str_list operator+(const char (&aHead)[N]) const { return literal_str_list(aHead, this); };

    constexpr literal_str_list operator+(const literal_str_list& aHead) const {
        return literal_str_list(aHead.text_ptr, aHead.text_size, this);
    };

    constexpr std::size_t hash() const { return fnv_1a_hash(text_size - 1); };

    template<typename FwdIter> void copy_to(FwdIter beg, FwdIter end) const { copy_to_recurse(beg, end); };

    void copy_to(char* beg, char* end) const { copy_to_recurse(beg, end); };
};

constexpr literal_str_list Value(const literal_str_list key, const literal_str_list val) {
    return literal_str_list(" ") + key + literal_str_list("=\"") + val + literal_str_list("\"");
}

template<typename... Args>
constexpr literal_str_list Attributes(Args... args) {
    return (literal_str_list("") + ... + args);
}

template<typename... Args>
constexpr literal_str_list Element(const literal_str_list Name, const literal_str_list Attrib, const literal_str_list Content, Args... args) {
    return literal_str_list("<") + Name + Attrib + literal_str_list(">") + Content + (literal_str_list("") + ... + args) + literal_str_list("</") + Name + literal_str_list(">");
}

template <typename... Args>
constexpr literal_str_list HtmlBuilder(const literal_str_list& title, const Args&... args) {
    return literal_str_list("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>") + title + literal_str_list("</title></head><body>") + ((literal_str_list("") + args) + ...) + literal_str_list("</body></html>");
}