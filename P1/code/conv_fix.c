
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "lib/stb_image.h"
#include "lib/stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//If the value of the pixel exceeds 255, we need to truncate it.
int normalize(int pixel_value){
    int value = pixel_value;
    if (pixel_value > 255){
        printf("255 Normalized!\n");
        value = 255;
    } else if(pixel_value < 0){
        printf("0 Normalized!\n");
        value = 0;
    }
    return value;
}

int main(){

    //Read the image file.
    int width,height,n, dimensions;
    struct timespec start, end;

    unsigned char* data = stbi_load("./img/lena256.png", &width, &height, &n, 1);
    stbi_write_png("./img/greylena.png", width, height, 1, data, width);

    dimensions = width * height;
    //The pointer with the data to create the image from.
    unsigned char* output_data = calloc(dimensions, (size_t) sizeof(char));

    //Define kernel.
    int kernel[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    //Declare the variables for the indeces.
    int topLeft, top, topRight, centerLeft;
    int centerRight, bottomLeft, bottom, bottomRight;

    for(int i = 0; i < dimensions; i++){
        //printf("PIXEL= %d\n", i);
        //printf("Initial: %d\n", output_data[i]);

        //SECTION Valor del centro.
        output_data[i] += (int) (kernel[4] * data[i]);
        //printf("Centro: %d * %d\n", kernel[4], data[i]); 

        //SECTION Valor del centro-izquierda.
        centerLeft = i - 1;
        
        if(centerLeft%width != width - 1 && centerLeft%width >= 0){
            output_data[i] += (int) (kernel[3] * data[centerLeft]);
            //printf("Centro-izquierda: %d * %d\n", kernel[3], data[centerLeft]);
        }
        
        //SECTION Valor del centro-derecha.
        centerRight = i + 1;
        if(centerRight%width != 0){
            output_data[i] += (int) (kernel[5] * data[centerRight]);
            //printf("Centro-derecha: %d * %d\n", kernel[5], data[centerRight]);
        }

        //SECTION Valor superior.
        top = i - width;
        if(top >= 0){
            output_data[i] += (int) (kernel[1] * data[top]);
            //printf("Superior: %d * %d\n", kernel[1], data[top]);
        }

        //SECTION Valor superior izquierdo.
        topLeft = top - 1;
        if(topLeft >= 0){
            if(topLeft%width != width-1){
                output_data[i] += (int) (kernel[0] * data[topLeft]);
                //printf("Superior izquierda: %d * %d\n", kernel[0], data[topLeft]);
            }
        }

        //SECTION Valor superior derecho.
        topRight = top + 1;
        if(topRight >= 0){
            if(topRight%width != 0){
                output_data[i] += (int) (kernel[2] * data[topRight]);
                //printf("Superior derecha: %d * %d\n", kernel[2], data[topRight]);
            }
        }

        //SECTION Valor inferior.
        bottom = i + width;
        if(bottom < dimensions){
            output_data[i] += (int)(kernel[7] * data[bottom]);
            //printf("Inferior: %d * %d\n", kernel[7], data[bottom]);
        }

        //SECTION Valor inferior izquierdo.
        bottomLeft = bottom - 1;
        if(bottomLeft < dimensions){
            if(bottomLeft%width != width - 1){
                output_data[i] += (int)(kernel[6] * data[bottomLeft]);
                //printf("Inferior izquierda: %d * %d\n", kernel[6], data[bottomLeft]);
            }
        }

        //SECTION Valor inferior derecho.
        bottomRight = bottom + 1;
        if(bottomRight < dimensions){
            if(bottomRight%width != 0){
                output_data[i] += (int)(kernel[8] * data[bottomRight]);
                //printf("Inferior derecha: %d * %d\n", kernel[8], data[bottomRight]);
            }
        }

        output_data[i] = normalize(output_data[i]);
        //printf("Final: %d\n\n", output_data[i]);
    }
    
    //Write image to file.
    //stbi_write_jpg("./img/greylena256.jpg", width, height, 1, data, 100);
    stbi_write_png("./img/lena-grey-sobel.png", width, height, 1, output_data, width);
    stbi_image_free(data);
    free(output_data);


    return 0;
}