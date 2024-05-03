#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    float horizontal_angle = 0.0;
    float vertical_angle = 0.0;

    float depth_buffer[1760];
    char render_buffer[1760];

    printf("\x1b[2J");

    while (1)
    {
        memset(render_buffer, 32, 1760);
        memset(depth_buffer, 0, 7040);

        for (float j = 0.0; j < 6.28; j += 0.020)
        {
            for (float i = 0.0; i < 6.28; i += 0.040)
            {

                float a = sin(i);
                float b = sin(j);
                float c = cos(i);
                float d = cos(j);
                float e = sin(horizontal_angle);
                float f = sin(vertical_angle);
                float g = cos(horizontal_angle);
                float h = cos(vertical_angle);

                float l = d + 2;
                float t = a * l * g - b * e;
                float depth_value = 1 / (a * l * e + b * g + 5);

                int x = 40 + 30 * depth_value * (c * l * h - t * f);
                int y = 12 + 15 * depth_value * (c * l * f + t * h);
                int z = x + 80 * y;

                int character_index = 8 * ((b * e - a * d * g) * h - a * d * e - b * g - c * d * f);

                if (22 > y && y > 0 && x > 0 && 80 > x && depth_value > depth_buffer[z])
                {
                    depth_buffer[z] = depth_value;

                    if (character_index > 0)
                        render_buffer[z] = ".,-~:;=!*#$@"[character_index];
                    else
                        render_buffer[z] = '.';
                }
            }
        }

        printf("\x1b[d");
        for (int i = 0; i < 1761; i++)
        {
            if (i % 80)
            {
                putchar(render_buffer[i]);
            }
            else
            {
                putchar(10);
            }
        }

        horizontal_angle += 0.04;
        vertical_angle += 0.02;
    }

    return 0;
}
