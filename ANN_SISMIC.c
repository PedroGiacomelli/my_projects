// Importing msp430 library
#include <msp430.h>
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
*/

#define N_INPUTS 8
#define N_HIDDEN_LAYERS 2
#define LEN_HIDDEN_LAYERS 15

void network_initializer(long hidden_layers[N_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS], char n_inputs, char n_hidden_layers, char len_hidden_layers);
void forward_propagation(long final_vals[LEN_HIDDEN_LAYERS], long hidden_layers[N_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS], unsigned int *inputs, char n_inputs, char n_hidden_layers, char len_hidden_layers, unsigned int *activation_vec);
long ReLu(long val);
char output_result(long *result, char len_hidden_layers);

int main() {

    // Remember stopping watchdog timer. Otherwise the program will not run properly.
    WDTCTL = WDTPW | WDTHOLD;

    char n_inputs=N_INPUTS;
    char n_hidden_layers=N_HIDDEN_LAYERS;
    char len_hidden_layers=LEN_HIDDEN_LAYERS;
    unsigned int inputs[N_INPUTS]={1,2,3,4,5,6,7,8}; //create a for loop to substitute the manual population
    unsigned int activation_vec[N_HIDDEN_LAYERS]={2,3};
    long final_vals[LEN_HIDDEN_LAYERS];

    long hidden_layers[N_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS];//=
    network_initializer(hidden_layers, n_inputs, n_hidden_layers, len_hidden_layers);

    char i, j;

    //Throughout the program, certain sections were commented out to enable MSP430 reading it.
    // Configuring it to accept printf was unnecessary since using an IDE like CCS already provides the necessary functionality for printing.

    /*
    for (i = 0; i < n_hidden_layers; i++) {
        printf("\n-0-0-0-0-\n");
        printf("%d ", i);
        printf("\n-0-0-0-0-\n");
        for (j = 0; j < len_hidden_layers; j++) {
            printf("%d ", hidden_layers[i][j]);
        }
        printf("\n");
    }
    */

    forward_propagation(final_vals,hidden_layers, inputs, n_inputs, n_hidden_layers, len_hidden_layers, activation_vec);

    /*

    printf("0000000000\n");

    for (i = 0; i < len_hidden_layers; i++) {

        printf("%d ", i);
        printf("%d ", hidden_layers[N_HIDDEN_LAYERS-1][i]);
        printf("\n");

    }

    */

   // Loop to allow analysing the result in MSP430
    while(1);

    return 0;
}

void network_initializer(long hidden_layers[N_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS], char n_inputs, char n_hidden_layers, char len_hidden_layers) {
    char i,j;

    for (i = 0; i < n_hidden_layers; i++) {
        for (j=0; j<LEN_HIDDEN_LAYERS; j++){

            hidden_layers[i][j]=(i+1)*j;

        }
    }
}

void forward_propagation(long final_vals[LEN_HIDDEN_LAYERS], long hidden_layers[N_HIDDEN_LAYERS][LEN_HIDDEN_LAYERS], unsigned int *inputs, char n_inputs, char n_hidden_layers, char len_hidden_layers, unsigned int activation_vec[N_HIDDEN_LAYERS]){

char i,j;
long activation;

for (j=0; j<len_hidden_layers; j++){
    activation=activation_vec[0];

    for (i=0; i<n_inputs; i++){

        activation+=inputs[i]*hidden_layers[0][j];

    }

    final_vals[j]=ReLu(activation);

}

/*

for (i = 0; i < len_hidden_layers; i++) {

        printf("%d ", i);
        printf("%d ", final_vals[i]);
        printf("\n");

    }

    printf("0000000000\n");


*/

char index_hidden_layers;

for (index_hidden_layers=0; index_hidden_layers<n_hidden_layers-1; index_hidden_layers++){

    for (i=0; i<len_hidden_layers; i++){

        activation=activation_vec[index_hidden_layers+1];

        for (j=0; j<len_hidden_layers; j++){



            activation+= final_vals[j]*hidden_layers[index_hidden_layers+1][i];
        }

        hidden_layers[index_hidden_layers+1][i]=ReLu(activation);

    }

}

}

long ReLu(long val){
    if (val<0){
        return 0;
    }
    return val;
}

char output_result(long *result, char len_hidden_layers){

    char i;
    long max_info[2]={0,0};

    for (i=0; i<len_hidden_layers; i++){
        if (result[i]> max_info[0]){
            max_info[0]=result[0];
            max_info[i]=i;
        }
    }

    char test=0;
    return test;
}
