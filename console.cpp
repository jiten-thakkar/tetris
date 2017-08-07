#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <unistd.h>
#endif
#include "console.h"

Console::Console()
{
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  old_t = t;
  t.c_lflag &= (~ICANON & ~ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

Console::~Console()
{
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
  tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
#endif
}
