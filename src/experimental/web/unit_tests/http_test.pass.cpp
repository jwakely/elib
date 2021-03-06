// REQUIRES: ELIB_WEB_SOURCE
#include <elib/experimental/web/http.hpp>
#include <elib/aux.hpp>
#include <elib/enumeration.hpp>
#include <elib/lexical_cast.hpp>
#include <iostream>
#include "rapid-cxx-test.hpp"

using namespace elib::web;
using namespace elib::web::http;
namespace enums = elib::enumeration;

TEST_SUITE(prox_http_test_suite)

TEST_CASE(prox_http_version_test)
{
    version zero = version::ONE_ZERO;
    version one = version::ONE_ONE;
    
    TEST_CHECK(std::string{"HTTP/1.0"} == to_string(zero));
    TEST_CHECK(std::string{"HTTP/1.1"} == to_string(one));
    
    TEST_CHECK(zero == to_version("HTTP/1.0"));
    TEST_CHECK(one == to_version("HTTP/1.1"));
}

#define TEST_STR_MAP(Name) \
    TEST_CHECK(enums::enum_cast<std::string>(Name) == #Name)
    
TEST_CASE(prox_method_test)
{
    auto OPTIONS = method::OPTIONS;
    auto GET = method::GET;
    auto HEAD = method::HEAD;
    auto POST = method::POST;
    auto PUT = method::PUT;
    auto DELETE = method::DELETE;
    auto TRACE = method::TRACE;
    auto CONNECT = method::CONNECT;
    
    using traits = enums::enum_traits<method>;
    using btraits = enums::basic_enum_traits<method>;
    TEST_CHECK(traits::has_first_value && traits::first_value == OPTIONS);
    TEST_CHECK(traits::has_last_value && traits::last_value == CONNECT);
    TEST_CHECK(traits::has_is_contigious && traits::is_contigious);
    TEST_CHECK(enums::has_name_map<method>::value
            && btraits::name_map.size() == enums::size<method>());
    
    TEST_CHECK(enums::has_constexpr_range<method>::value);
    
    TEST_STR_MAP(OPTIONS);
    TEST_STR_MAP(GET);
    TEST_STR_MAP(HEAD);
    TEST_STR_MAP(POST);
    TEST_STR_MAP(PUT);
    TEST_STR_MAP(DELETE);
    TEST_STR_MAP(TRACE);
    TEST_STR_MAP(CONNECT);
}
#undef TEST_STR_MAP

TEST_CASE(prox_status_test)
{    
    TEST_CHECK(enums::has_name_map<status>::value);
    TEST_CHECK(enums::has_range<status>::value);
    TEST_CHECK(!enums::has_constexpr_range<status>::value);
 
#define TEST_E(V, N)                                                                             \
    TEST_CHECK(N == enums::underlying_cast(status::V));                                    \
    TEST_CHECK(status::V == enums::enum_cast<status>(N));                             \
    TEST_CHECK(status::V == enums::enum_cast<status>(#V));                            \
    TEST_CHECK(std::string{ #V } == enums::enum_cast<std::string>(status::V));             \
    TEST_CHECK(#N == elib::lexical_cast<std::string>(enums::underlying_cast(status::V)) ); \
    TEST_CHECK( FN(V) )

#define FN(V) status_is_information(status::V)
    TEST_E(CONTINUE, 100);
    TEST_E(SWITCH_PROTOCOL, 101);
#undef FN
#define FN(V) status_is_success(status::V)
    TEST_E(OK, 200);
    TEST_E(CREATED, 201);
    TEST_E(ACCEPTED, 202);
    TEST_E(NON_AUTH_INFORMATION, 203);
    TEST_E(NO_CONTENT, 204);
    TEST_E(RESET_CONTENT, 205);
    TEST_E(PARTIAL_CONTENT, 206);
#undef FN
#define FN(V) status_is_redirect(status::V)
    TEST_E(REDIRECT_CHOICE, 300);
    TEST_E(REDIRECT_MOVED_PERM, 301);
    TEST_E(REDIRECT_FOUND, 302);
    TEST_E(REDIRECT_SEE_OTHER, 303);
    TEST_E(REDIRECT_NOT_MODIFIED, 304);
    TEST_E(REDIRECT_USE_PROXY, 305);
    //UNUSED 306
    TEST_E(REDIRECT_TEMP, 307);
#undef FN
#define FN(V) status_is_client_error(status::V) && status_is_error(status::V)
    TEST_E(BAD_REQUEST, 400);
    TEST_E(UNAUTHORIZED, 401);
    TEST_E(PAYMENT_REQUIRED, 402);
    TEST_E(FORBIDDEN, 403);
    TEST_E(NOT_FOUND, 404);
    TEST_E(METHOD_NOT_ALLOWED, 405);
    TEST_E(NOT_ACCEPTABLE, 406);
    TEST_E(PROXY_AUTH_REQUIRED, 407);
    TEST_E(REQUEST_TIMEOUT, 408);
    TEST_E(CONFLICT, 409);
    TEST_E(GONE, 410);
    TEST_E(LENGTH_REQUIRED, 411);
    TEST_E(PRECONDITION_FAILED, 412);
    TEST_E(REQUEST_ENTITY_TOO_LARGE, 413);
    TEST_E(REQUEST_URI_TOO_LARGE, 414);
    TEST_E(UNSUPPORTED_MEDIA_TYPE, 415);
    TEST_E(REQUEST_RANGE_NOT_SATISFIABLE, 416);
    TEST_E(EXPECTATION_FAILED, 417);
#undef FN
#define FN(V) status_is_server_error(status::V) && status_is_error(status::V)
    TEST_E(INTERNAL_SERVER_ERROR, 500);
    TEST_E(NOT_IMPLEMENTED, 501);
    TEST_E(BAD_GATEWAY, 502);
    TEST_E(SERVICE_UNAVAILABLE, 503);
    TEST_E(GATEWAY_TIMEOUT, 504);
    TEST_E(HTTP_VERSION_UNSUPPORTED, 505);
#undef FN
#undef TEST_E
}

inline bool operator==(data_type const & lhs, std::string const & rhs)
{
    std::string lhs_s = std::string(lhs.begin(), lhs.end());
    return lhs_s == rhs;
}


inline std::ostream & operator <<(std::ostream & out, data_type const & dt)
{
    out << std::string{dt.begin(), dt.end()};
    return out;
}

TEST_CASE(serialize_test)
{
    auto v = serialize(field_type{"Hello", "Value"});
    TEST_CHECK( v == "Hello: Value\r\n" );
    
    v = serialize(field_type{"Hello-World", "this \"is_my\" value"});
    TEST_CHECK( v == std::string{"Hello-World: this \"is_my\" value\r\n"});
}

TEST_CASE(serializes_test)
{
    std::vector<field_type> v =
        {
            {"Hello", "Value"}
          , {"Hello-World", "Tada "}
          , {"third-list", "3.14"}
        };
    
    std::string s =
        "Hello: Value\r\n"
        "Hello-World: Tada \r\n"
        "third-list: 3.14\r\n";

    TEST_CHECK(serialize(v) == s);
}

TEST_CASE(serialize_request_header_test)
{
    request_header h =
        {version::ONE_ZERO, method::GET, "/index.html"};
        
    std::string s =
        "GET /index.html HTTP/1.0\r\n";
        
    TEST_CHECK(serialize(h) == s);
}

TEST_CASE(serialize_response_header_test)
{
    response_header h =
        { version::ONE_ONE, status::OK, "OK"};
    
    std::string s = "HTTP/1.1 200 OK\r\n";
    TEST_CHECK(serialize(h) == s);
}

TEST_CASE(serialize_request_test)
{
    request h =
        { 
            {version::ONE_ONE, method::GET, "/home/index.html"}
          , {{"Hello", "World"}, {"Hello-World", "Value Test"}}
          , {'h', 'e', 'l', 'l', 'o'}
        };
        
    std::string s =
        "GET /home/index.html HTTP/1.1\r\n"
        "Hello: World\r\n"
        "Hello-World: Value Test\r\n"
        "\r\n"
        "hello";
        
    TEST_CHECK(serialize(h) == s);
}

TEST_CASE(serialize_response_test)
{
    response h =
        {
            {version::ONE_ZERO, status::NOT_FOUND, "Page Not Found"}
          , {{"Hello", "\"World\""}, {"My-Test", " 'test' 123"}} 
          , {'t', '\r', '\n', 't', 'e', 's', 't'}
        };
        
    std::string s =
        "HTTP/1.0 404 Page Not Found\r\n"
        "Hello: \"World\"\r\n"
        "My-Test:  'test' 123\r\n"
        "\r\n"
        "t\r\n"
        "test";
        
    TEST_CHECK(serialize(h) == s);
}
    
TEST_CASE(parse_field_type_test)
{
    std::string s_ = "Hello-World: Value\r\n";
    std::vector<char> s{s_.begin(), s_.end()};
    auto begin = s.begin();
    auto end = s.end();
    field_type f;
    
    TEST_CHECK(parse(begin, end, f) == end);
    TEST_CHECK(f.first == "Hello-World");
    TEST_CHECK(f.second == "Value");
}

TEST_CASE(parse_field_types_test)
{
    std::string s_ = 
        "Hello-World:  Value\r\n"
        "this: is 'a' test\r\n"
        "This-World-Is:  Going Down!\r\n";
    std::vector<char> s(s_.begin(), s_.end());
    auto begin = s.begin();
    auto end = s.end();
        
    std::vector<field_type> v =
        {
            {"Hello-World", " Value"}
          , {"this", "is 'a' test"}
          , {"This-World-Is", " Going Down!"}
        };
    
    std::vector<field_type> r;
    TEST_CHECK(parse(begin, end, r) == end);
    TEST_REQUIRE(r.size() == v.size());
    
    auto vb = v.begin();
    for (const auto & f : r)
    {
        TEST_CHECK(vb->first == f.first);
        TEST_CHECK(vb->second == f.second);
        ++vb;
    }
}

TEST_CASE(parse_request_header_test)
{
    std::string s_ = "GET \"this-value/index.html\" HTTP/1.1\r\n";
    std::vector<char> s{s_.begin(), s_.end()};
    request_header h;
    
    TEST_CHECK(parse(s.begin(), s.end(), h) == s.end());
    TEST_CHECK(h.http_version == version::ONE_ONE);
    TEST_CHECK(h.code == method::GET);
    TEST_CHECK(h.value == "\"this-value/index.html\"");
}

TEST_CASE(parse_response_header_test)
{
    std::string s_ = "HTTP/1.0 404 Page Not Found\r\n";
    std::vector<char> s(s_.begin(), s_.end());
    response_header h;
    
    TEST_CHECK(parse(s.begin(), s.end(), h) == s.end());
    TEST_CHECK(h.http_version == version::ONE_ZERO);
    TEST_CHECK(h.code == status::NOT_FOUND);
    TEST_CHECK(h.value == "Page Not Found");
}

TEST_SUITE_END()