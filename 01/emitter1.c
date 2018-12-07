#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <read.h>
#include <emit.h>

#include "common.h"

int main() {
  char c;
  read_state_t s;
  s.cur_val = 0;

  emit(#include <stdio.h>);
  emit(#define beg {); emit(#define end });
  emit(int main() beg);
  emit(int sum = 0;);
  while (read_char(&c)) {
    switch(c) {
    case '+':
      s.cur_sign = +1;
      break;
    case '-':
      s.cur_sign = -1;
      break;
    case DIGIT:
      s.cur_val = s.cur_val * 10 + char_to_digit(c);
      break;
    case '\n':
      emit(sum += %d;, s.cur_sign * s.cur_val);
      s.cur_val = 0;
      break;
    }
  }
  emit(printf("%%d\n", sum););
  emit(end);
}
