#include "../s21_string.h"
void* s21_memchr(const void* buff, int ch, s21_size_t count) {
  const unsigned char* ptr = (const unsigned char*)buff;
  void* find = S21_NULL;
  for (; count && !find; ++ptr, --count) {
    (*ptr == ch) ? find = (void*)ptr : 0;
  }
  return find;
}
