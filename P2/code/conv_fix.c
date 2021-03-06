
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "lib/stb_image.h"
#include "lib/stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

int main(){

    //Read the image file.
    int width,height,n,dimensions;

    unsigned char* data = stbi_load("./img/lena2048.jpg", &width, &height, &n, 1);

    //Write the gray version for comparison.
    stbi_write_png("./img/gray-lena.png", width, height, 1, data, width);

    dimensions = width * height;
    //The pointer with the data to create the image from.
    unsigned char* output_data = calloc(dimensions, (size_t) sizeof(char));

    //Define kernel.
    int kernel[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};

    //Declare the variables for the indeces.
    int topLeft, top, topRight, centerLeft;
    int centerRight, bottomLeft, bottom, bottomRight;
    struct timespec start, end;
    
    //Declare the index.
    int i;
    int avg;

        //TODO Start the timer.
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        
        //Set the number of thread teams.
        #pragma omp parallel num_threads(4) shared(kernel,data,output_data)
        {
            #pragma omp for private(i,topLeft, top, topRight, centerLeft,centerRight, bottomLeft, bottom, bottomRight)
            for(i = 0; i < dimensions; i++){
                
                //Declare the value to sum.
                int pixel = 0;

                //fprintf(fpi, "Pixel %d, value = %d\n",i, data[i]);

                //printf("PIXEL= %d\n", i);
                //printf("Pixel %d with value: %d\n", i, data[i]);

                //SECTION Valor del centro.
                pixel += (int) (kernel[4] * data[i]);
                //printf("Centro: %d * %d\n", kernel[4], data[i]);
                //printf("Value = %d\n", pixel);

                //SECTION Valor del centro-izquierda.
                centerLeft = i - 1;
                
                if(centerLeft%width != width - 1 && centerLeft%width >= 0){
                    pixel += (int) (kernel[3] * data[centerLeft]);
                    //printf("Centro-izquierda: %d * %d\n", kernel[3], data[centerLeft]);
                    //printf("Value = %d\n", pixel);
                }
                
                //SECTION Valor del centro-derecha.
                centerRight = i + 1;
                if(centerRight%width != 0){
                    pixel += (int) (kernel[5] * data[centerRight]);
                    //printf("Centro-derecha: %d * %d\n", kernel[5], data[centerRight]);
                    //printf("Value = %d\n", pixel);
                }

                //SECTION Valor superior.
                top = i - width;
                if(top >= 0){
                    pixel += (int) (kernel[1] * data[top]);
                    //printf("Superior: %d * %d\n", kernel[1], data[top]);
                    //printf("Value = %d\n", pixel);
                }

                //SECTION Valor superior izquierdo.
                topLeft = top - 1;
                if(topLeft >= 0){
                    if(topLeft%width != width-1){
                        pixel += (int) (kernel[0] * data[topLeft]);
                        //printf("Superior izquierda: %d * %d\n", kernel[0], data[topLeft]);
                        //printf("Value = %d\n", pixel);
                    }
                }

                //SECTION Valor superior derecho.
                topRight = top + 1;
                if(topRight >= 0){
                    if(topRight%width != 0){
                        pixel += (int) (kernel[2] * data[topRight]);
                        //printf("Superior derecha: %d * %d\n", kernel[2], data[topRight]);
                        //printf("Value = %d\n", pixel);
                    }
                }

                //SECTION Valor inferior.
                bottom = i + width;
                if(bottom < dimensions){
                    pixel += (int)(kernel[7] * data[bottom]);
                    //printf("Inferior: %d * %d\n", kernel[7], data[bottom]);
                    //printf("Value = %d\n", pixel);
                }

                //SECTION Valor inferior izquierdo.
                bottomLeft = bottom - 1;
                if(bottomLeft < dimensions){
                    if(bottomLeft%width != width - 1){
                        pixel += (int)(kernel[6] * data[bottomLeft]);
                        //printf("Inferior izquierda: %d * %d\n", kernel[6], data[bottomLeft]);
                        //printf("Value = %d\n", pixel);
                    }
                }

                //SECTION Valor inferior derecho.
                bottomRight = bottom + 1;
                if(bottomRight < dimensions){
                    if(bottomRight%width != 0){
                        pixel += (int)(kernel[8] * data[bottomRight]);
                        //printf("Inferior derecha: %d * %d\n", kernel[8], data[bottomRight]);
                        //printf("Value = %d\n", pixel);
                    }
                }

                if (pixel > 255)
                    pixel = 255;
                else if(pixel < 0)
                    pixel = 0;
                
                output_data[i] = pixel;

                //printf("Final: %d\n\n", output_data[i]);
            }
        }
        //TODO Stop the timer.
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        avg+= (int) delta_us;
        printf("It took %llu microseconds.\n", delta_us);

    //Write image to file.
    stbi_write_png("./img/lena-border.png", width, height, 1, output_data, width);
    stbi_image_free(data);
    free(output_data);

    return 0;
}