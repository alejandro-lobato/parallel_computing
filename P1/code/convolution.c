
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "lib/stb_image.h"
#include "lib/stb_image_write.h"
#include <stdio.h>

int main(){

    //Read the image file.
    int width,height,n;
    unsigned char* data = stbi_load("img/lena256.png", &width, &height, &n, 1);
    
    //Create the pointer with the data to create the image from.
    unsigned char* output_data;

    //Define kernel.
    double kernel[9] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};

    //Apply convolution.
    int i = 0;
    int neighborhood[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    //For each pixel, we'll multiply.
    for(i = 0; i < height * width; i++){
        printf("%i ", data[i]);
        output_data[i] = 0;
        int neighbor = 0;
        for(int j = 0; j < 9; i++){
            //Sum that shit boi.

            //If it's in the left side
            if(i*width==0){

            }
        }
    }

    //Write image to file.
    stbi_write_png("img/greylena256.png", width, height, 1, data, 256);
    stbi_image_free(data);
    //??
    //Profit.

    return 0;
}