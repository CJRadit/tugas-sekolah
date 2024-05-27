#include <termios.h>
#include <stdio.h>
// #include <stdbool.h>

// struct User
// {
//   char username[32];
//   char password[256];
//   bool is_admin;
// };

// ssize_t hidden_input(...)

// Thanks, stranger from internet!
size_t
hidden_input(char **lineptr, size_t *n, FILE *stream)
{
  struct termios old, new;
  int nread;

  /* Turn echoing off and fail if we can't. */
  if (tcgetattr(fileno(stream), &old) != 0)
    return -1;
  new = old;
  new.c_lflag &= ~ECHO;
  if (tcsetattr(fileno(stream), TCSAFLUSH, &new) != 0)
    return -1;

  /* Read the password. */
  nread = getline(lineptr, n, stream);

  /* Restore terminal. */
  (void)tcsetattr(fileno(stream), TCSAFLUSH, &old);

  return nread;
}