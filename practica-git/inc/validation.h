
#ifndef __VALIDATION__
#define __VALIDATION__

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MENU_OPTION_SUM "sum"
#define MENU_OPTION_PRODUCT "prod"

bool isNumber(char*);
bool isAlphabet(char*);
bool isOption(char*);

#endif
