#include <msp430.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


unsigned int **hidden_layers;
unsigned int **hidden_bias; //clean hidden bias

int network_initializer(unsigned int n_inputs, unsigned int n_hidden_layers, unsigned int len_hidden_layers, unsigned int n_outputs);
void layers_creator(unsigned int x, unsigned int *hidden_weights, unsigned int *hidden_bias_weight);
void print_hidden_layers(unsigned int n_hidden_layers, unsigned int len_hidden_layers);
int32_t neuron_activation(unsigned int *weights, int32_t *inputs, unsigned int len_hidden_layers) ;
int32_t forward_propagation(int32_t *inputs, unsigned int n_hidden_layers, unsigned int len_hidden_layers, unsigned int n_outputs, int32_t *outputs);
int32_t ReLu(int32_t val);
int32_t output_result(int32_t *result, unsigned int len_hidden_layers);



int main() {
    unsigned int n_inputs=8;
    unsigned int n_outputs=2;
    unsigned int n_hidden_layers=2;
    unsigned int len_hidden_layers=15;
    int32_t inputs[8]={1,2,3,4,5,6,7,8}; //create a for loop to substitute the manual population
    int32_t output[2]={1,2}; // same here
    int check;
    int32_t result;

    check=network_initializer(n_inputs, n_hidden_layers, len_hidden_layers, n_outputs);
    if (!check){
        // print("Memory allocation ERROR")
        return 0;
    }
    print_hidden_layers(n_hidden_layers, len_hidden_layers);
    result = forward_propagation(inputs,n_hidden_layers, len_hidden_layers, n_outputs, output);

    output_result(result);

    return 0;
}

int network_initializer(unsigned int n_inputs, unsigned int n_hidden_layers, unsigned int len_hidden_layers, unsigned int n_outputs) {
    hidden_layers = (unsigned int **)malloc(n_hidden_layers * sizeof(unsigned int *));
    hidden_bias = (unsigned int**)malloc(n_hidden_layers * sizeof(unsigned int *));

    if (hidden_layers==NULL|| hidden_bias==NULL){
            return 0;
        }

    unsigned int i;
    for (i = 0; i < n_hidden_layers; i++) {
        hidden_layers[i] = (unsigned int *)malloc((len_hidden_layers+1) * sizeof(unsigned int));
        hidden_bias[i]=(unsigned int*)malloc((len_hidden_layers+1) * sizeof(unsigned int));

        if (hidden_layers[i]==NULL || hidden_bias[i]==NULL){
            return 0;
        }
        layers_creator(len_hidden_layers, hidden_layers[i], hidden_bias[i]);
    }
    return 1;
}

void layers_creator(unsigned int x, unsigned int *hidden_weights, unsigned int *hidden_bias_weight) {
    unsigned int i;
    for (i = 0; i < x+1; i++) {
        hidden_weights[i] = i;
        hidden_bias_weight[i]=i;
    }
}

void print_hidden_layers(unsigned int n_hidden_layers, unsigned int len_hidden_layers) {
    unsigned int i, j;

    for (i = 0; i < n_hidden_layers; i++) {
        for (j = 0; j < len_hidden_layers+1; j++) {
            printf("%d ", hidden_layers[i][j]);
        }
        printf("\n");
    }

    printf("-0-0-0-0-0-\n");

    for (i = 0; i < n_hidden_layers; i++) {
        for (j = 0; j < len_hidden_layers+1; j++) {
            printf("%d ", hidden_bias[i][j]);
        }
        printf("\n");
    }
}

int32_t forward_propagation(int32_t *inputs, unsigned int n_hidden_layers, unsigned int len_hidden_layers, unsigned int n_outputs, int32_t *outputs){

unsigned int i,j;

int32_t next_inputs[len_hidden_layers];
for (i=0; i<n_hidden_layers; i++){
    for (j=0; j<len_hidden_layers; j++){
        int32_t val_activation = neuron_activation(hidden_layers[i], inputs, len_hidden_layers);
        int32_t new_output= ReLu(val_activation);
        next_inputs[j]=new_output;
    }
    inputs=next_inputs;
};

return inputs;

}

int32_t neuron_activation(unsigned int *weights, int32_t *inputs, unsigned int len_hidden_layers){
    int32_t activation=weights[len_hidden_layers];
    unsigned int i;
    for (i=0; i<len_hidden_layers; i++){
        activation+= weights[i]*inputs[i];
        //printf("%hhu\n",weights[i]);
    }
    printf("%d\n",i);
    return activation;
}

int32_t ReLu(int32_t val){
    if (val<0){
        return 0;
    }
    return val;
}

int32_t output_result(int32_t *result, unsigned int len_hidden_layers){

    char i;
    int32_t max_info[2]={0,0};

    for (i=0, i<len_hidden_layers, i++){
        if (result[i]> max_val[0]){
            max_info[0]=result[0];
            max_info[i]=i
        }
    }
    //define here the function to find the class.
}


