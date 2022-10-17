#ifndef _THEME_H_
#define _THEME_H_

#include "dark.h"
#include "light.h"
#include <stdint.h>

typedef enum{
    THEME_DARK,
    THEME_LIGHT,
}theme_type_e;

typedef struct{
    uint32_t theme_main_page_bg_color;
}theme_t;

void theme_init(int themeType);

extern theme_t theme;
#endif
