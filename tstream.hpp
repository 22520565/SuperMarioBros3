#pragma once
#include "tchar.hpp"
#include <fstream>
#include <ios>
#include <iosfwd>
#include <istream>
#include <memory>
#include <ostream>
#include <streambuf>
#include <string>

namespace game {
    using tios = std::basic_ios<tchar, std::char_traits<tchar>>;
    using tstreambuf = std::basic_streambuf<tchar, std::char_traits<tchar>>;
    using tistream = std::basic_istream<tchar, std::char_traits<tchar>>;
    using tostream = std::basic_ostream<tchar, std::char_traits<tchar>>;
    using tiostream = std::basic_iostream<tchar, std::char_traits<tchar>>;
    using tstringbuf = std::basic_stringbuf<tchar, std::char_traits<tchar>, std::allocator<tchar>>;
    using tistringstream = std::basic_istringstream<tchar, std::char_traits<tchar>, std::allocator<tchar>>;
    using tostringstream = std::basic_ostringstream<tchar, std::char_traits<tchar>, std::allocator<tchar>>;
    using tstringstream = std::basic_stringstream<tchar, std::char_traits<tchar>, std::allocator<tchar>>;
    using tfilebuf = std::basic_filebuf<tchar, std::char_traits<tchar>>;
    using tifstream = std::basic_ifstream<tchar, std::char_traits<tchar>>;
    using tofstream = std::basic_ofstream<tchar, std::char_traits<tchar>>;
    using tfstream = std::basic_fstream<tchar, std::char_traits<tchar>>;
#if _HAS_CXX20
    using tsyncbuf = std::basic_syncbuf<tchar>;
    using tosyncstream = std::basic_osyncstream<tchar>;
#endif
#if _HAS_CXX23
    using tspanbuf = std::basic_spanbuf<tchar>;
    using tispanstream = std::basic_ispanstream<tchar>;
    using tospanstream = std::basic_ospanstream<tchar>;
    using tspanstream = std::basic_spanstream<tchar>;
#endif
}
