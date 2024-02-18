#include "mbstrings.h"

#include <stddef.h>

/* mbslen - multi-byte string length
 * - Description: returns the number of UTF-8 code points ("characters")
 * in a multibyte string. If the argument is NULL or an invalid UTF-8
 * string is passed, returns -1.
 *
 * - Arguments: A pointer to a character array (`bytes`), consisting of UTF-8
 * variable-length encoded multibyte code points.
 *
 * - Return: returns the actual number of UTF-8 code points in `src`. If an
 * invalid sequence of bytes is encountered, return -1.
 *
 * - Hints:
 * UTF-8 characters are encoded in 1 to 4 bytes. The number of leading 1s in the
 * highest order byte indicates the length (in bytes) of the character. For
 * example, a character with the encoding 1111.... is 4 bytes long, a character
 * with the encoding 1110.... is 3 bytes long, and a character with the encoding
 * 1100.... is 2 bytes long. Single-byte UTF-8 characters were designed to be
 * compatible with ASCII. As such, the first bit of a 1-byte UTF-8 character is
 * 0.......
 *
 * You will need bitwise operations for this part of the assignment!
 */
size_t mbslen(const char* bytes) {
    // TODO: implement!
    if (bytes == NULL) {
        return -1;
    }

    size_t len = 0;
    for (size_t i = 0; bytes[i] != '\0'; ) {
        unsigned char leadByte = bytes[i];
        size_t charLen = 0;

        if ((leadByte >> 7) == 0) {
            // 1-byte character (0xxxxxxx)
            charLen = 1;
        } else if ((leadByte >> 5) == 0x6) {
            // 2-byte character (110xxxxx)
            charLen = 2;
        } else if ((leadByte >> 4) == 0xE) {
            // 3-byte character (1110xxxx)
            charLen = 3;
        } else if ((leadByte >> 3) == 0x1E) {
            // 4-byte character (11110xxx)
            charLen = 4;
        } else {
            return -1; // Invalid starting byte
        }

        // Check continuation bytes for multibyte characters
        for (size_t j = 1; j < charLen; j++) {
            if ((bytes[i + j] & 0xC0) != 0x80) {
                return -1; // Invalid continuation byte
            }
        }

        i += charLen; // Advance to the next character
        len++; // Increment character count
    }

    return len;
}
