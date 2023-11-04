#pragma once
#include <math.h>
#include <cstring>
#include <stdint.h>

inline
void flipVertical(unsigned char *dst, unsigned char *src, int width, int height, int components)
{
    for (int r = 0; r < height; r++) 
    {
        unsigned char* aSrc = &src[r * components * width];
        unsigned char* aDst = &dst[(height - r - 1) * components * width];
        memcpy(aDst, aSrc, components * width);
    }
}

inline
void resample(void *src, void *dst, int oldw, int oldh, int neww,  int newh)
{
int i;
int j;
int l;
int c;
float t;
float u;
float tmp;
float d1, d2, d3, d4;
unsigned int p1, p2, p3, p4; // nearby pixels
unsigned char red, green, blue, alpha;

    for (i = 0; i < newh; i++) 
    {
        for (j = 0; j < neww; j++) 
        {

            tmp = (float)(i) / (float)(newh - 1) * (oldh - 1);
            l = (int)floor(tmp);

            if (l < 0)
            {
                l = 0;
            }
            else 
            {
                if (l >= oldh - 1)
                {
                    l = oldh - 2;
                }
            }

            u = tmp - l;
            tmp = (float)(j) / (float)(neww - 1) * (oldw - 1);
            c = (int)floor(tmp);
            if (c < 0) {
                c = 0;
            }
            else
            {
                if (c >= oldw - 1) {
                    c = oldw - 2;
                }
            }
            t = tmp - c;

            // coefficients
            d1 = (1 - t) * (1 - u);
            d2 = t * (1 - u);
            d3 = t * u;
            d4 = (1 - t) * u;

            // nearby pixels: a[i][j]
            p1 = *((unsigned int*)src + (l * oldw) + c);
            p2 = *((unsigned int*)src + (l * oldw) + c + 1);
            p3 = *((unsigned int*)src + ((l + 1) * oldw) + c + 1);
            p4 = *((unsigned int*)src + ((l + 1) * oldw) + c);

            // color components
            blue  = (unsigned char)p1         * d1 + (unsigned char)p2         * d2 + (unsigned char)p3         * d3 + (unsigned char)p4         * d4;
            green = (unsigned char)(p1 >> 8)  * d1 + (unsigned char)(p2 >> 8)  * d2 + (unsigned char)(p3 >> 8)  * d3 + (unsigned char)(p4 >> 8)  * d4;
            red   = (unsigned char)(p1 >> 16) * d1 + (unsigned char)(p2 >> 16) * d2 + (unsigned char)(p3 >> 16) * d3 + (unsigned char)(p4 >> 16) * d4;
            alpha = (unsigned char)(p1 >> 24) * d1 + (unsigned char)(p2 >> 24) * d2 + (unsigned char)(p3 >> 24) * d3 + (unsigned char)(p4 >> 24) * d4;

            // new pixel R G B A
            *((unsigned int*)dst + (i * neww) + j) = (alpha << 24) | (red << 16) | (green << 8) | (blue);
        }
    }
}
