/* File name: ExtremeC_examples_chapter12_3.c
 * Description: Unicode support
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __APPLE__

#include <stdint.h>

typedef uint16_t char16_t;
typedef uint32_t char32_t;

#else
#include <uchar.h> // Needed for char16_t and char32_t
#endif

typedef struct {
  long num_chars;
  long num_bytes;
} unicode_len_t;

unicode_len_t strlen_ascii(char* str) {
  unicode_len_t res;
  res.num_chars = 0;
  res.num_bytes = 0;
  if (!str) {
    return res;
  }
  res.num_chars = strlen(str) + 1;
  res.num_bytes = strlen(str) + 1;
  return res;
}

unicode_len_t strlen_u8(char* str) {
  unicode_len_t res;
  res.num_chars = 0;
  res.num_bytes = 0;
  if (!str) {
    return res;
  }
  // Last null character
  res.num_chars = 1;
  res.num_bytes = 1;
  while (*str) {
    if ((*str | 0x7f) == 0x7f) { // 0x7f = 0b01111111
      res.num_chars++;
      res.num_bytes++;
      str++;
    } else if ((*str & 0xf0) == 0xf0) { // 0xf0 = 0b11110000
      res.num_chars++;
      res.num_bytes += 4;
      str += 4;
    } else if ((*str & 0xe0) == 0xe0) { // 0xe0 = 0b11100000
      res.num_chars++;
      res.num_bytes += 3;
      str += 3;
    } else if ((*str & 0xc0) == 0xc0) { // 0xc0 = 0b11000000
      res.num_chars++;
      res.num_bytes += 2;
      str += 2;
    } else {
      fprintf(stderr, "UTF-8 string is not valid!\n");
      exit(1);
    }
  }
  return res;
}

unicode_len_t strlen_u16(char16_t* str) {
  unicode_len_t res;
  res.num_chars = 0;
  res.num_bytes = 0;
  if (!str) {
    return res;
  }
  // Last null character
  res.num_chars = 1;
  res.num_bytes = 2;
  while (*str) {
    if (*str < 0xdc00 || *str > 0xdfff) {
      res.num_chars++;
      res.num_bytes += 2;
      str++;
    } else {
      res.num_chars++;
      res.num_bytes += 4;
      str += 2;
    }
  }
  return res;
}
unicode_len_t strlen_u32(char32_t* str) {
  unicode_len_t res;
  res.num_chars = 0;
  res.num_bytes = 0;
  if (!str) {
    return res;
  }
  // Last null character
  res.num_chars = 1;
  res.num_bytes = 4;
  while (*str) {
      res.num_chars++;
      res.num_bytes += 4;
      str++;
  }
  return res;
}

int main(int argc, char** argv) {

  char ascii_string[32] = "Hello World!";

  char utf8_string[32] = u8"Hello World!";
  char utf8_string_2[32] = u8"درود دنیا!";

  char16_t utf16_string[32] = u"Hello World!";
  char16_t utf16_string_2[32] = u"درود دنیا!";
  char16_t utf16_string_3[32] = u"𝦵হ𝡩!";

  char32_t utf32_string[32] = U"Hello World!";
  char32_t utf32_string_2[32] = U"درود دنیا!";
  char32_t utf32_string_3[32] = U"𝦵হ𝡩!";

  unicode_len_t len = strlen_ascii(ascii_string);
  printf("Length of ASCII string:\t\t\t %ld chars, %ld bytes\n\n",
      len.num_chars, len.num_bytes);

  len = strlen_u8(utf8_string);
  printf("Length of UTF-8 english string:\t\t %ld chars, %ld bytes\n",
      len.num_chars, len.num_bytes);
  len = strlen_u16(utf16_string);
  printf("Length of UTF-16 english string:\t %ld chars, %ld bytes\n",
      len.num_chars, len.num_bytes);
  len = strlen_u32(utf32_string);
  printf("Length of UTF-32 english string:\t %ld chars, %ld bytes\n\n",
      len.num_chars, len.num_bytes);

  len = strlen_u8(utf8_string_2);
  printf("Length of UTF-8 persian string:\t\t %ld chars, %ld bytes\n",
      len.num_chars, len.num_bytes);
  len = strlen_u16(utf16_string_2);
  printf("Length of UTF-16 persian string:\t %ld chars, %ld bytes\n",
      len.num_chars, len.num_bytes);
  len = strlen_u32(utf32_string_2);
  printf("Length of UTF-32 persian string:\t %ld chars, %ld bytes\n\n",
      len.num_chars, len.num_bytes);

  len = strlen_u16(utf16_string_3);
  printf("Length of UTF-16 alien string:\t\t %ld chars, %ld bytes\n",
      len.num_chars, len.num_bytes);
  len = strlen_u32(utf32_string_3);
  printf("Length of UTF-32 alien string:\t\t %ld chars, %ld bytes\n",
      len.num_chars, len.num_bytes);

  return 0;
}
