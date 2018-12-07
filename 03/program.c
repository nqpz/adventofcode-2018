#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <read.h>

#ifdef PROGRAM1
#include "program1.h"
#endif
#ifdef PROGRAM2
#include "program2.h"
#endif

int main() {
  int32_t xs[1296];
  int32_t ys[1296];
  int32_t ws[1296];
  int32_t hs[1296];
  int n_elems = 0;
  int32_t cur_val = 0;
  int32_t *cur_list = xs;

  char c;
  while (read_char(&c)) {
    switch(c) {
    case DIGIT:
      cur_val = cur_val * 10 + char_to_digit(c);
      break;
    case '\n':
      cur_list[n_elems] = cur_val;
      n_elems++;
      break;
    case '@':
      cur_val = 0;
      cur_list = xs;
      break;
    case ',':
      cur_list[n_elems] = cur_val;
      cur_val = 0;
      cur_list = ys;
      break;
    case ':':
      cur_list[n_elems] = cur_val;
      cur_val = 0;
      cur_list = ws;
      break;
    case 'x':
      cur_list[n_elems] = cur_val;
      cur_val = 0;
      cur_list = hs;
      break;
    }
  }

  struct futhark_context_config *cfg = futhark_context_config_new();
  struct futhark_context *ctx = futhark_context_new(cfg);
  int32_t solution;
  int ret = futhark_entry_answer(ctx, &solution,
                                 futhark_new_i32_1d(ctx, xs, n_elems),
                                 futhark_new_i32_1d(ctx, ys, n_elems),
                                  futhark_new_i32_1d(ctx, ws, n_elems),
                                 futhark_new_i32_1d(ctx, hs, n_elems)
                                 );
  if (ret != 0) {
    puts(futhark_context_get_error(ctx));
    return EXIT_FAILURE;
  }
  printf("%d\n", solution);
  return EXIT_SUCCESS;
}
