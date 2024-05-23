#ifndef DITHER
#define DITHER
#include <stdint.h>

enum Dither_op {FloydStein, Ordered};
void buf_to_ppm(uint8_t* buf, int width, int height, int line_size, char* file_name);
int Floyd_Stein_Dither(uint8_t* buffer, int width, int height, int line_size, int rgb_buff_size);
int Ordererd_Dither(uint8_t* buffer, int width, int height);

#endif // !DITHER
