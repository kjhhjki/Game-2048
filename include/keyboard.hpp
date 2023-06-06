#ifndef _KEYBOARD_
#define _KEYBOARD_

#define KEYCODE_R 185
#define KEYCODE_L 186
#define KEYCODE_U 183
#define KEYCODE_D 184
#define KEYCODE_ESC '\033'
#define KEYCODE_ENTER 13

#ifdef __WIN32__

#define KEYCODE_DIRECTION 224
#define KEYCODE_DIRECTION_R 77
#define KEYCODE_DIRECTION_L 75
#define KEYCODE_DIRECTION_U 72
#define KEYCODE_DIRECTION_D 80

#endif

#ifdef __linux__

#define KEYCODE_DIRECTION '['
#define KEYCODE_DIRECTION_R 'C'
#define KEYCODE_DIRECTION_L 'D'
#define KEYCODE_DIRECTION_U 'A'
#define KEYCODE_DIRECTION_D 'B'

#endif

void keyboard_open();
void keyboard_close();
int __kbhit(void);
int read();
int check_input(int);

#endif