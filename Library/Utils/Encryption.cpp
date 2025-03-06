
#include <string>
#include "cryptopp/sha.h"
#include "cryptopp/filters.h"
#include "cryptopp/base64.h"

using namespace std;

// reference:  https://stackoverflow.com/questions/5930056/generating-a-sha256-hash-with-crypto-using-a-string-as-input-and-output
std::string SHA256HashString(std::string aString) {
    std::string digest;
    CryptoPP::SHA256 hash;

    CryptoPP::StringSource foo(aString, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::Base64Encoder(
                new CryptoPP::StringSink(digest))));

    return digest;
}
