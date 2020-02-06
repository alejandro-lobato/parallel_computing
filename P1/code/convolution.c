
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "lib/stb_image.h"
#include "lib/stb_image_write.h"
#include <stdio.h>

int main(){

    //Read the image file.
    int x,y,n;
    unsigned char *data = stbi_load("img/lena256.png", &x, &y, &n, 1);
    
    //Define kernel.
    
    
    //Convert image file.
    //Apply convolution.

    //Write image to file.
    stbi_write_png("img/greylena256.png", x, y, 1, data, 256);
    stbi_image_free(data);
    //??
    //Profit.

    return 0;
}