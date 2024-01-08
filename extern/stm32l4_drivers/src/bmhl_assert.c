/**
 * @file            bmhl_assert.c
 * @author          Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version         0.1
 * @date            2021-04-18
 * 
 * @copyright       All rights reserved
 * 
 */

#include "bmhl_assert.h"
#include "bmhl_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

void bmhl_assert(const char* expr, const char* file, int line)
{
    printf("Fatal error in file %s @line %d", file, line);
}

#ifdef __cplusplus
}
#endif
