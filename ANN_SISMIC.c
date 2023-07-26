// Importing msp430 library
#include <msp430.h>

/*
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 */

#define N_INPUTS 11
#define N_OUTPUTS 1
#define N_HIDDEN_LAYERS 2
#define LEN_HIDDEN_LAYERS 15

void forward_propagation(int input_weights[N_INPUTS][LEN_HIDDEN_LAYERS], int hidden_weights[LEN_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS], int output_weights[LEN_HIDDEN_LAYERS],
                         int input_bias[LEN_HIDDEN_LAYERS], int hidden_bias[LEN_HIDDEN_LAYERS], int output_bias[N_OUTPUTS],
                         long long temp_vals[LEN_HIDDEN_LAYERS],long long final_vals[LEN_HIDDEN_LAYERS],
                         int *inputs);

long long ReLu(long long val);

int main() {

    // Remember stopping watchdog timer. Otherwise the program will not run properly.
    WDTCTL = WDTPW | WDTHOLD;

    long long temp_vals[LEN_HIDDEN_LAYERS], final_vals[LEN_HIDDEN_LAYERS];

    int inputs[N_INPUTS]={40, 2040, 2247, 2247, 2172, 2183, 4095, 2179, 2150, 2171, 2235};

    int input_weights[N_INPUTS][LEN_HIDDEN_LAYERS]={
                                                    {-79,  21, -75, -53, -35,  73,  33,   8, -96,  48, -21,
                                                        62, -49, -91,  75},
                                                    {-57, -21, -38, -87,  70,  71,  96, -24,  93, -11,  35,
                                                        -85,  83, -41, -49},
                                                    {-101,    8,   -5,   28,   98,   84,   83,    5,  -81,
                                                        -65,   93,  -18,   77,   35,   26},
                                                    {-46,  80, -60, -20, 101,  48, -12,  12, -18,  46, -21,
                                                        35,  44,  22,   8},
                                                    {-60, -63,  61, -43,  32, -41, -74, -20, -39, -53,  18,
                                                        -52,  53,  45,  40},
                                                    { -81,   89,    1,   82,  -62,   19,   94,  102,  -97,
                                                        -4,  -43,  -89,   16, -101,   23},
                                                    { 76,  76,  93,  49, -65, -13,  77, -50, -12,  24, -81,
                                                        -2, -89, -39,  51},
                                                    { 44,  89,  57, -58,  83,  11,  70,  86,  67, -22,  20,
                                                        -14,  42,  -3, -76},
                                                    {  30,  -62,   50,  -81, -101,  -34,   95,   41,  -18,
                                                        -78,  -90,   46,   85,  -99,   17},
                                                    { 47, -43,   5,  64,  20, -25, -87,  -3,  -7, -65, -88,
                                                        2, -33, -58, -83},
                                                    {  69,  -31,   67,  -97, -102,   87,   35,  101,   -4,
                                                       -70,   93,  -68,  -24,   89,  -86}};

    int hidden_weights[LEN_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS]={
                                                            { 90,  31, -78,  17, -55,  56, -29,   0,  39, -63,  19,
                                                                -65,  62, -32,   9},
                                                            { 64,  91, -33, -78,  88,  93,  77,  67,  -1,  -6,  11,
                                                                -74,  75,  19,  93},
                                                            { 38, -26, -62, -86, -33, -27,  -7,  30, -79, -39, -57,
                                                                30,  14,  32, -54},
                                                            {-91, -88,  -8,  72,   7,   5,   8,   3,  74, -17,  61,
                                                                63,  18, -57,  52},
                                                            {-94, -85,  15, -47, -45, -87,  76,  11, -91,  14,  39,
                                                                41, -10, -14, -43},
                                                            { 86,  57,  94,  78, -18, -12,  19, -33, -89, -64,  10,
                                                                8,  88,   3,  31},
                                                            {-41, -16, -82, -11, -57, -83,  48, -68,  75, -60,  58,
                                                                74, -96,  17,  58},
                                                            { 83,  18,  54,   1,  15, -50, -17,  29, -41, -12,  84,
                                                                -74, -20,  53, -76},
                                                            { 10, -28,   5, -33, -81,  75,  92, -14,  39, -15,  50,
                                                                57, -37, -87,  94},
                                                            { 39,  42,  29, -83, -85,  -2,  58,  91,  16, -77, -29,
                                                                84,  30, -13,  88},
                                                            { 49, -64, -68,  30,  91,  59,  41,  51, -64,  -2,  21,
                                                                -59, -85, -45,  74},
                                                            {-87, -40, -77,  34, -47,  -1, -39,  73,  42, -58,  23,
                                                                -70, -39, -26, -17},
                                                            { 83, -85,  59,  24,  61, -45, -93, -80, -80, -63, -62,
                                                                37,  32, -90,  12},
                                                            { 82,  14, -13, -67,  26, -22, -38, -73, -38, -63, -29,
                                                                -59,  31,  62,  49},
                                                            {-15, -48,  13,  76,  46,  37, -24, -62, -63,  94, -64,
                                                                65,  53,  12,  79}};

    int output_weights[LEN_HIDDEN_LAYERS]={-43, -62, 24, -50, 38, 56, 97, -47, 113, 127, 13, -37, 120, 76, 12};

    int input_bias[LEN_HIDDEN_LAYERS]={-9, 79, -37, 95, 102, -3, -37, 97, 102, -11, -93, -11, 43, 26, 35};
    int hidden_bias[LEN_HIDDEN_LAYERS]={79, 67, -65, -33, -2, -20, -76, 66, -40, -35, 53, -30, 60, -73, 52};
    int output_bias[N_OUTPUTS]={47};

    forward_propagation(input_weights,  hidden_weights, output_weights, input_bias, hidden_bias, output_bias, temp_vals, final_vals, inputs);

    //                              | - - - - - - - - - - - - - - - - - - - |
    //                              | - - - - - - - ATTENTION - - - - - - - |
    // | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |
    // | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |
    // | The result is seen in temp_vals[0]. If it equals 0, then the fuel is not adulterated. Otherwise, it is contaminated.|
    // | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - = | 
    // | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |
    //                              | - - - - - - - - - - - - - - - - - - - |
    //                              | - - - - - - - - - - - - - - - - - - - |

    // Loop to allow analysing the result in MSP430
    while(1);

    return 0;

}

void forward_propagation(int input_weights[N_INPUTS][LEN_HIDDEN_LAYERS], int hidden_weights[LEN_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS], int output_weights[LEN_HIDDEN_LAYERS],
                         int input_bias[LEN_HIDDEN_LAYERS], int hidden_bias[LEN_HIDDEN_LAYERS], int output_bias[N_OUTPUTS],
                         long long temp_vals[LEN_HIDDEN_LAYERS], long long final_vals[LEN_HIDDEN_LAYERS],
                         int *inputs)
{


    long long activation=0;
    int i,j=0;

    for (i=0; i<LEN_HIDDEN_LAYERS; i++){

        activation= input_bias[i];

        for (j=0; j<N_INPUTS; j++) {

            activation+=(long long)input_weights[j][i]* (long long)inputs[j];

        }

        temp_vals[i]=ReLu(activation);

    }


    for (i=0; i<LEN_HIDDEN_LAYERS; i++){

        activation= hidden_bias[i];

        for (j=0; j<LEN_HIDDEN_LAYERS; j++){

            activation+= hidden_weights[j][i]*temp_vals[j];

        }

        final_vals[i]=ReLu(activation);

    }



    for(i=0; i < N_OUTPUTS; i++){

        activation=output_bias[i];

        for (j=0; j < LEN_HIDDEN_LAYERS; j++){

            activation+=output_weights[j]*final_vals[j];

        }

        temp_vals[i]=ReLu(activation);

    }
}


long long ReLu(long long val){
    if (val<0){
        return 0;
    }
    return val;
}

