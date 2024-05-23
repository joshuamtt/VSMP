#include "dither.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void buf_to_pgm(uint8_t* buf, int width, int height, int line_size, char* file_name) {
    FILE* file;
    file = fopen(file_name, "w");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "P5\n%d %d\n255\n", width, height);

    for (int i = 0; i < height*width; ++i) {
        /* fwrite(buf + i * width, sizeof(uint8_t), width*width, file); */
        fputc(buf[i], file);
    }
    fclose(file);


}
void buf_to_ppm(uint8_t* buf, int width, int height, int line_size, char* file_name) {
    FILE* file;
    file = fopen(file_name, "wb");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    // Write line by line
    for (int i = 0; i < height; ++i) {
        fwrite(buf + i*line_size, sizeof(uint8_t), width*3, file);
    }

    fclose(file);
}


static const int16_t FS_DITHER_COEFFS[2][3] = {
    { 1, 0, 7 },
    { 3, 5, 1 }
};

int index_buff(int x, int y, int width) {
    return (x + y * width);
}
void buf_to_gray(uint8_t* buffer, int width, int height, int line_size, char* file_name) {

    uint8_t *gray_buffer = malloc(width*height*sizeof(uint8_t));
    if (!gray_buffer) {
        printf("Error allocating gray buffer.\n");
        return;
    }

    uint8_t r, g, b, new_val;
    int index;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            index = index_buff(x, y, width);
            r = buffer[index];
            g = buffer[index+1];
            b = buffer[index+1];

            new_val = r * 0.3 + g * 0.59 + b*0.11;

            gray_buffer[index] = new_val;

        }
    }
    buf_to_pgm(gray_buffer, width, height, width, file_name);

}

void binary(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
}


int Floyd_Stein_Dither(uint8_t *buffer, int width, int height, int line_size, int rgb_buff_size) {
    buf_to_gray(buffer, width, height, line_size, "gray.pgm");
    for (int y = 0; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            // Calculate pixel index
            int index = (y * width + x) * 3;

            // Thresholding each color component separately
            for (int c = 0; c < 3; ++c) {
                uint8_t old_pixel = buffer[index + c];
                uint8_t new_pixel = old_pixel > 127 ? 255 : 0; // Thresholding

                buffer[index + c] = new_pixel;

                int16_t error = old_pixel - new_pixel;

                for (int i = 0; i < 2; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int16_t coef = FS_DITHER_COEFFS[i][j + 1];
                        int neighbor_index = ((y + i) * width + (x + j)) * 3 + c;
                        buffer[neighbor_index] += (error * coef) / 16;
                    }
                }
            }
        }
    }
    /* uint8_t old_pixel, new_pixel, quant_error; */

    /* for (int y = 0; y < height-1; ++y) { */
    /*     for (int x = 1; x < width-1; ++x) { */

    /*         int index = index_buff(x, y, width); */

    /*         uint8_t old_pixel; */
    /*         uint8_t new_pixel, quant_error; */

    /*         uint8_t r, g, b, new_r, new_g, new_b, err_r, err_b, err_g; */

    /*         r = buffer[x + y*width]; */
    /*         g = buffer[x + y*width]; */
    /*         b = buffer[x + y*width]; */



    /*         new_r = (r>128) ? 255 : 0; */
    /*         new_g = (r>128) ? 255 : 0; */
    /*         new_b = (r>128) ? 255 : 0; */

    /*         err_r =  */







    /*         buffer[index_buff(x+1, y, width)]   = buffer[index_buff(x+1, y, width)]; */
    /*         buffer[index_buff(x-1, y+1, width)] = buffer[index_buff(x-1, y+1, width)]; */
    /*         buffer[index_buff(x, y+1, width)]   = buffer[index_buff(x, y+1, width)]; */
    /*         buffer[index_buff(x+1, y+1, width)] = buffer[index_buff(x+1, y+1, width)]; */

    /*         /\* buffer[x+1 + y]     = buffer[x+1 + y] + 7.0/16 * quant_error; *\/ */
    /*         /\* buffer[x-1 + (y+1)] = buffer[x-1 + (y+1)] + 3.0/16 * quant_error; *\/ */
    /*         /\* buffer[x + (y+1)]   = buffer[x + (y+1)] + 5.0/16 * quant_error; *\/ */
    /*         /\* buffer[x+1 + (y+1)] = buffer[x+1 + (y+1)] + 1.0/16 * quant_error; *\/ */

    /*     } */
    /* } */

    // Test if buffer is good?
    buf_to_ppm(buffer, width, height, line_size, "floyd_out.ppm");


}


int Ordererd_Dither(uint8_t* buffer, int width, int height) {

}
