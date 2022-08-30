#include <string>
#include <unordered_set>

#define CR                  (char) '\r'
#define LF                  (char) '\n'
#define CRLF                "\r\n"
#define CRLF_LEN            2
#define DELIMITERS          " \f\n\r\t\v" /// from std::isspace

#define CONTENT_LENGTH "content-length"

#define TRANSFER_ENCODING "transfer-encoding"
#define CHUNKED "chunked"

namespace Http {

    class Header {
    public:
        Header(const std::string& key, const std::string& value)
                : key(key), value(value) {}

        std::string key;
        std::string value;
    };

    enum Code {
        OK = 200,
        BadRequest = 400,
        NotFound = 404,
        MethodNotAllowed = 405,
        PayloadTooLarge = 413,
        NotImplemented = 501,
    };

    std::unordered_set<std::string> supported_methods = {
            "GET",
            "POST",
            "PUT",
            "DELETE",
            "HEAD",
            "OPTIONS",
            "CONNECT",
            "TRACE",
            "PATCH",
    };
}