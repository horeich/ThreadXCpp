/**
 * @file            bmhl_assert.h
 * @author          Simon Schrampfer, Andreas Reichle
 * @brief 
 * @version         0.1
 * @date            2021-04-18
 * 
 * @copyright       All rights reserved
 * 
 */

#ifndef BMHL_ASSERT_H_
#define BMHL_ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief               Results in rutime error if condition is false. 
 *                      BMHL_ASSERT is limited to Debug and Develop builds (NDEBUG)        
 * 
 * @param expr 
 * @param file 
 * @param line 
 */
void bmhl_assert(const char* expr, const char* file, int line);

#ifdef __cplusplus
}
#endif

#ifdef NDEBUG
#define BMHL_ASSERT(expr) ((void)0)

#else
#define BMHL_ASSERT(expr)                                \
do {                                                     \
    if (!(expr)) {                                       \
        bmhl_assert(#expr, __FILE__, __LINE__);          \
    }                                                    \
} while (0)
#endif

#endif // BMHL_ASSERT_H_