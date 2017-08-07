#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <termios.h>
#endif

// The Console class puts the terminal in raw mode on POSIX machines
class Console {
private:
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
  struct termios old_t;
#endif

public:
  Console();
  ~Console();
};

#endif /* __CONSOLE_H__ */
