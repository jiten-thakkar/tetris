#if !(defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)))
#include <conio.h>
#endif
#include <iostream>
#include "input.h"

// `get` reads characters from the input and looks for arrow keys.
// Returns arrow key code if pressed; return 0 otherwise.
Input::Key Input::get()
{
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
  // 27 and 91 are the first two characters of an arrow key input
  char c;
  std::cin.get(c);
  if (c == 27) {
    std::cin.get(c);
    if (c != 91) {
      return UNKNOWN;
    }
    std::cin.get(c);
    return (Input::Key)c;
  }
  return UNKNOWN;
#else /* WINDOWS */
  // -32 is the first byte of an arrow key input
  char c = _getch();
  if (c != -32) {
    return UNKNOWN;
  }
  return (Input::Key)_getch();
#endif
}
