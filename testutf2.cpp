#include <algorithm>
#include <array>
#include <nowide/convert.hpp>
#include <string>
#include <vector>

using namespace std::string_literals;
using namespace nowide;

std::string escape_json_char(int c) {
    using T                 = char;
    static auto escape_code = [](auto d) { return "\\"s + (T)d; };

    static auto unicode_escape = [](auto d) {
        static const std::array<char, 16> hexify = {
            {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}
        };
        auto esc = escape_code('u');

        // this will spaz on numbers greaters than 0xffff
        for (int i = 0; i < 4; ++i)
            esc += (T)hexify[(d & 0xf000) >> 12], d <<= 4;

        return esc;
    };

    switch (c) {
        case '\b': return escape_code('b');  // 0x08
        case '\t': return escape_code('t');  // 0x09
        case '\n': return escape_code('n');  // 0x0a
        case '\r': return escape_code('r');  // 0x0d
        case '\\': return escape_code('\\');
        case '"':  return escape_code('"');
    }

    if (c >= 32 && c <= 126)
        return std::basic_string<T>((T)c, 1);

    return unicode_escape(c);
}

template <class T> auto escape_json(T const *p) { return escape_json(std::basic_string<T>(p)); }
template <class T> auto escape_json(std::basic_string<T> s) {
    std::vector<std::string> escaped;
    std::transform(s.begin(), s.end(), std::back_inserter(escaped), escape_json_char);
    return escaped;
}

int main() {
    std::string invalid("\u0006\t\t\u2514\u2500\u00e4\u2518\u00b4\u00d8\u008d\"");

    auto _wide   = widen(invalid);
    auto _narrow = narrow(_wide);

    printf("%s\n", invalid.c_str()); fflush(stdout);
    printf("%s\n", _narrow.c_str()); fflush(stdout);
    printf("%s\n", invalid == _narrow ? "==" : "!="); fflush(stdout);

    printf("narrow was %lli characters, wide was %lli characters.\n", _narrow.length(), _wide.length());

    auto escaped = escape_json(_wide);

    for (const auto& e : escaped)
        printf("%s", e.c_str());

    printf("\n\ntest complete.\n"); fflush(stdout);
    exit(0);
}

/*
		└─ä┘´Ø"
		└─ä┘´Ø"
==
narrow was 21 characters, wide was 11 characters.
\u0006\t\t\u2514\u2500\u00e4\u2518\u00b4\u00d8\u008d\"

test complete.
*/
/* vim: set ts=4 sts=4 sw=4 et: */
