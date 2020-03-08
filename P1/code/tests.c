#include <stdio.h>
#include <stdlib.h>

int main(){
    int width = 4;
    int dimensions = 16;
    int data[16]={1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};

    int kernel[9]={1,1,1,1,1,1,1,1,1};

    int output_data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    int topLeft, top, topRight, centerLeft;
    int centerRight, bottomLeft, bottom, bottomRight;

    for(int i = 0; i < dimensions; i++){

        printf("\nInitial: %d\n", output_data[i]);

        //SECTION Valor del centro.
        output_data[i] += kernel[4] * data[i];
        printf("Centro: %d * %d\n", kernel[4], data[i]);

        //SECTION Valor del centro-izquierda.
        centerLeft = i - 1;
        
        if(centerLeft%width != width - 1 && centerLeft%width >= 0){
            output_data[i] += kernel[3] * data[centerLeft];
            printf("Centro-izquierda: %d * %d\n", kernel[3], data[centerLeft]);
        }
        
        //SECTION Valor del centro-derecha.
        centerRight = i + 1;
        if(centerRight%width != 0){
            output_data[i] += kernel[5] * data[centerRight];
            printf("Centro-derecha: %d * %d\n", kernel[5], data[centerRight]);
        }

        //SECTION Valor superior.
        top = i - width;
        if(top >= 0){
            output_data[i] += kernel[1] * data[top];
            printf("Superior: %d * %d\n", kernel[1], data[top]);
        }

        //SECTION Valor superior izquierdo.
        topLeft = top - 1;
        if(topLeft >= 0){
            if(topLeft%width != width-1){
                output_data[i] += kernel[0] * data[topLeft];
                printf("Superior izquierda: %d * %d\n", kernel[0], data[topLeft]);
            }
        }

        //SECTION Valor superior derecho.
        topRight = top + 1;
        if(topRight >= 0){
            if(topRight%width != 0){
                output_data[i] += kernel[2] * data[topRight];
                printf("Superior derecha: %d * %d\n", kernel[2], data[topRight]);
            }
        }

        //SECTION Valor inferior.
        bottom = i + width;
        if(bottom < dimensions){
            output_data[i] += kernel[7] * data[bottom];
            printf("Inferior: %d * %d\n", kernel[7], data[bottom]);
        }

        //SECTION Valor inferior izquierdo.
        bottomLeft = bottom - 1;
        if(bottomLeft < dimensions){
            if(bottomLeft%width != width - 1){
                output_data[i] += kernel[6] * data[bottomLeft];
                printf("Inferior izquierda: %d * %d\n", kernel[6], data[bottomLeft]);
            }
        }

        //SECTION Valor inferior derecho.
        bottomRight = bottom + 1;
        if(bottomRight < dimensions){
            if(bottomRight%width != 0){
                output_data[i] += kernel[8] * data[bottomRight];
                printf("Inferior derecha: %d * %d\n", kernel[8], data[bottomRight]);
            }
        }

        printf("Final: %d\n\n", output_data[i]);
    }

    return 0;
}