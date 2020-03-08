
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "lib/stb_image.h"
#include "lib/stb_image_write.h"
#include <stdio.h>
#include <time.h>

//If the value of the pixel exceeds 255, we need to truncate it.
int normalize(int pixel_value){
    int value = 255;
    if(pixel_value < 255)
        value = pixel_value;
    return value;
}

int main(){

    //Read the image file.
    int width,height,n, dimensions;
    struct timespec start, end;

    unsigned char* data = stbi_load("./img/lena2048.png", &width, &height, &n, 1);
    stbi_write_png("./img/greylena.png", width, height, 1, data, width);

    dimensions = width * height;
    //The pointer with the data to create the image from.
    unsigned char output_data[dimensions];

    //Define kernel.
    double kernel[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    int is_top = 0;
    int is_bottom = 0;

    //For each pixel, we'll multiply and add it.
    //Start the timer.
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int i = 0; i < dimensions; i++){

        int left_index = i - width;
        int right_index = i + width;

        output_data[i] = 0;

        //Checks for top border.
        if(left_index < 0){
            //printf("%d - Top\n", i);
            output_data[i] += 0;
            is_top = 1;

        }
        else{
            output_data[i] += kernel[1] * data[left_index];
        }

        //Checks for bottom border.
        if(right_index > dimensions - 1){
            //printf("%d - Bottom\n", i);
            output_data[i] += 0;
            is_bottom = 1;

        }
        else{
            output_data[i] += kernel[7] * data[right_index];
        }

        //Checks for left border --------------------.
        if(i%width == 0){
            //printf("%d - Left\n", i);
            output_data[i] += 0;
        }
        else{
            if(is_top == 0){
                output_data[i] += kernel[0] * data[left_index - 1];
            }
            else{
                output_data[i] += 0;
            }
            output_data[i] += kernel[3] * data[i-1];
            output_data[i] += kernel[6] * data[right_index - 1];
        }

        //Checks for right border.
        if((i+1)%width == 0){
            //printf("%d - Right\n", i);
            output_data[i] += 0;
        }
        else{
            output_data[i] += kernel[2] * data[left_index + 1];
            output_data[i] += kernel[5] * data[i + 1];
            if(is_bottom == 0){
                output_data[i] += kernel[8] * data[right_index + 1];
            }
            else{
                output_data[i] += 0;
            }
        }

        //Center value remains the same:
        output_data[i] += kernel[4] * data[i];


        output_data[i] = normalize(output_data[i]);
       //printf("New pixel data: %d\n\n", output_data[i]);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("It took: %llu microseconds.\n", delta_us);

    //Write image to file.
    //stbi_write_jpg("./img/greylena256.jpg", width, height, 1, data, 100);
    stbi_write_png("./img/lena-grey-sobel.png", width, height, 1, output_data, width);
    stbi_image_free(data);


    return 0;
}