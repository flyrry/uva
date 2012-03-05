#include <stdio.h>

int main()
{
  char c;
  char keymap[256];
  keymap['\n'] = '\n';
  keymap['\t'] = '\t';
  keymap[' '] = ' ';
  keymap['\''] = 'l';
  keymap[','] = 'n';
  keymap['.'] = 'm';
  keymap['/'] = ',';
  keymap[';'] = 'k';
  keymap['['] = 'o';
  keymap['\\'] = ';';
  keymap[']'] = 'p';
  keymap['a'] = ';';
  keymap['b'] = 'c';
  keymap['c'] = 'z';
  keymap['d'] = 'a';
  keymap['e'] = 'q';
  keymap['f'] = 's';
  keymap['g'] = 'd';
  keymap['h'] = 'f';
  keymap['i'] = 'y';
  keymap['j'] = 'g';
  keymap['k'] = 'h';
  keymap['l'] = 'j';
  keymap['m'] = 'b';
  keymap['n'] = 'v';
  keymap['o'] = 'u';
  keymap['p'] = 'i';
  keymap['q'] = '{';
  keymap['r'] = 'w';
  keymap['s'] = '`';
  keymap['t'] = 'e';
  keymap['u'] = 't';
  keymap['v'] = 'x';
  keymap['w'] = '}';
  keymap['x'] = '/';
  keymap['y'] = 'r';
  keymap['z'] = '.';

  keymap['A'] = ';';
  keymap['B'] = 'c';
  keymap['C'] = 'z';
  keymap['D'] = 'a';
  keymap['E'] = 'q';
  keymap['F'] = 's';
  keymap['G'] = 'd';
  keymap['H'] = 'f';
  keymap['I'] = 'y';
  keymap['J'] = 'g';
  keymap['K'] = 'h';
  keymap['L'] = 'j';
  keymap['M'] = 'b';
  keymap['N'] = 'v';
  keymap['O'] = 'u';
  keymap['P'] = 'i';
  keymap['Q'] = '{';
  keymap['R'] = 'w';
  keymap['S'] = '`';
  keymap['T'] = 'e';
  keymap['U'] = 't';
  keymap['V'] = 'x';
  keymap['W'] = '}';
  keymap['X'] = '/';
  keymap['Y'] = 'r';
  keymap['Z'] = '.';

  while ((c = getchar()) != EOF) {
    putchar(keymap[c]);
  }
  return 0;
}
