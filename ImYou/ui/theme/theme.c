#include "theme.h"

theme_t theme;
void theme_init(int themeType)
{
    switch(themeType)
    {
        case THEME_DARK:
            theme.theme_main_page_bg_color = THEME_DARK_MAIN_PAGE_BG_COLOR;
            break;
        case THEME_LIGHT:
            theme.theme_main_page_bg_color = THEME_LIGHT_MAIN_PAGE_BG_COLOR;
            break;
        default:
            theme.theme_main_page_bg_color = THEME_DARK_MAIN_PAGE_BG_COLOR;
            break;
    }
}