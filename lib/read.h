#define DIGIT '0': \
  case '1':        \
  case '2':        \
  case '3':        \
  case '4':        \
  case '5':        \
  case '6':        \
  case '7':        \
  case '8':        \
  case '9'

bool read_char(char* dest) {
  int c = getchar();
  if (c != -1) {
    *dest = (char) c;
    return true;
  } else {
    return false;
  }
}

int char_to_digit(char c) {
  return c - '0';
}
