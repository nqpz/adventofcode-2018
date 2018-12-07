#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <read.h>
#include <emit.h>

typedef struct {
  int cur_char_index;
  int cur_id_index;
  char temp_id[256];
} read_state_t;

int main() {
  char c;
  read_state_t s;
  s.cur_char_index = 0;
  s.cur_id_index = 0;

  emit(#include <stdio.h>);
  emit(#include <stdint.h>);
  emit(#include <string.h>);
  emit(#define beg {); emit(#define end });
  emit(int main() beg);

  emit(char base_id[256];);
  emit(int n_diffs = 0;);
  emit(int last_diff_i;);
  emit(void *goto_next;);
  emit(goto_next = &&noskip0;);
  emit(goto *goto_next;);

  while (read_char(&c)) {
    switch(c) {
    case '\n':
      s.temp_id[s.cur_char_index] = '\0';

      emit(goto skip%d;, s.cur_id_index);

      emit(noskip%d:, s.cur_id_index);
      emit(memcpy(base_id, "%s", %d);, s.temp_id, s.cur_char_index);
      emit(goto_next = &&noskip%d;, s.cur_id_index + 1);

      emit(skip%d:, s.cur_id_index);
      for (int i = 0; i < s.cur_char_index; i++) {
        emit(if (base_id[%d] != %d) beg, i, s.temp_id[i]);
        ; emit(n_diffs++;);
        ; emit(last_diff_i = %d;, i);
        emit(end);
      }

      emit(if (n_diffs == 1) beg);
      ; emit(for (int i = 0; i < %d; i++) beg, s.cur_char_index);
      ; ; emit(if (i != last_diff_i) beg);
      ; ; ; emit(putchar((int) base_id[i]););
      ; ; emit(end);
      ; emit(end);
      ; emit(putchar((int) '\n'););
      ; emit(return 0;);
      emit(end);
      emit(n_diffs = 0;);

      s.cur_char_index = 0;
      s.cur_id_index++;
      break;
    default:
      s.temp_id[s.cur_char_index] = c;
      s.cur_char_index++;
    }
  }
  emit(goto *goto_next;);
  emit(noskip%d:, s.cur_id_index);
  emit(return 0;);
  emit(end);
}
