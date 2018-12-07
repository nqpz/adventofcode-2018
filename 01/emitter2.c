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

  emit(#include <stdlib.h>);
  emit(#include <stdio.h>);
  emit(#define beg {); emit(#define end });
  emit(int main() beg);
  emit(int sum = 0;);
  emit(int found_freqs_size = 512;);
  emit(int *found_freqs = (int*) malloc(sizeof(int) * found_freqs_size););
  emit(found_freqs[0] = 0;);
  emit(int n_found_freqs = 1;);
  emit(loop:);
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
      emit(for (int i = 0; i < n_found_freqs; i++) beg);
      ; emit(if (sum == found_freqs[i]) beg);
      ; ; emit(printf("%%d\n", sum););
      ; ; emit(return 0;);
      ; emit(end);
      emit(end);
      emit(found_freqs[n_found_freqs] = sum;);
      emit(n_found_freqs++;);
      emit(if (n_found_freqs == found_freqs_size) beg);
      ; emit(found_freqs_size *= 2;);
      ; emit(found_freqs = (int*) realloc(found_freqs, sizeof(int) * found_freqs_size););
      emit(end);
      s.cur_val = 0;
      break;
    }
  }
  emit(goto loop;);
  emit(end);
}
