// error.h
// Řešení IJC-DU1, příklad b), 23.3.2024
// Autor: Jan Hájek, FIT
// Přeloženo: gcc 13.2.0
// hlavičkový soubor s definicemi funkcí warning a error_exit

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);
