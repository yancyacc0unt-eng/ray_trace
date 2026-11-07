#include "main.h"
/*
* This file can display the results to stdout, It is the screen of the porgram.
* "\xe2\x96\x84" is the unicode character for a half-solid block,
* which it's foreground can be used as a pixel in odd rows,
* and it's background can be used as a pixel in even rows.
* 
* Setting foreground RGB, use \033[38;2;R;G;Bm.
* Setting background RGB, use \033[48;2;R;G;Bm.
* Reset colors, use \033[0m.
*/
