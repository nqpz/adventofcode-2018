#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <read.h>
#include <emit.h>

int main() {
  char c;

  emit(#include <stdio.h>);
  emit(#include <stdint.h>);
  emit(#include <string.h>);
  emit(#define beg {); emit(#define end });
  emit(int main() beg);

  emit(int twos = 0;);
  emit(int threes = 0;);

  emit(uint8_t chars_map[256];);
  emit(memset(chars_map, 0, 256););

  while (read_char(&c)) {
    switch(c) {
    case '\n':
      emit(for (int i = 0; i < 256; i++) beg);
      ; emit(if (chars_map[i] == 2) beg);
      ; ; emit(twos++;);
      ; ; emit(break;);
      ; emit(end);
      emit(end);
      emit(for (int i = 0; i < 256; i++) beg);
      ; emit(if (chars_map[i] == 3) beg);
      ; ; emit(threes++;);
      ; ; emit(break;);
      ; emit(end);
      emit(end);
      emit(memset(chars_map, 0, 256););
      break;
    default:
      emit(chars_map[%d]++;, (int) c);
    }
  }
  emit(printf("%%d\n", twos * threes););
  emit(end);
}
