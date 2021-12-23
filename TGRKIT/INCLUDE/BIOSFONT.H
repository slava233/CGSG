/* Output strings in 256-colored dos modes
 * One must implement 'PutPixel' function to use library
 *
 * 2003-2014, Anton Timofeev, PML #30.
 */

/* Font letters dimensions */
#define BF_HEIGHT (*(word *)(0x485))
#define BF_WIDTH  8

typedef unsigned char byte;
typedef unsigned short word;

/* One must implement it on user side! */
void PutPixel(int x, int y, byte color);

/* Put char on the screen */
void BF_PutChar(int x, int y, byte C, byte color, byte bColor);

/* Formatted printf with background color specification */
void BF_PrintfB(int x, int y, byte color, byte bColor, char const* format, ...);

/* Formatted printf with transparent background */
void BF_Printf(int x, int y, byte color, char const* format, ...);
