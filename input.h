#ifndef __INPUT_H__
#define __INPUT_H__

// The Input class gets unbuffered input.
class Input {
public:
  enum Key {
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    UP = 65,
    DOWN = 66,
    RIGHT = 67,
    LEFT = 68,
#else /* WINDOWS */
    UP = 72,
    DOWN = 80,
    RIGHT = 77,
    LEFT = 75,
#endif
    ENTER   = '\n',
    SPACE   = ' ',
    UNKNOWN = -1
  };

  enum Key get();
};

#endif /* __INPUT_H__ */
