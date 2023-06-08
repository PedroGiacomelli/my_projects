#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned char un_char;

un_char **hidden_layers;
un_char **hidden_bias; //clean hidden bias

void network_initializer(un_char n_inputs, un_char n_hidden_layers, un_char len_hidden_layers, un_char n_outputs);
void layers_creator(un_char x, un_char *hidden_weights, un_char *hidden_bias_weight);
void print_hidden_layers(un_char n_hidden_layers, un_char len_hidden_layers);
uint32_t neuron_activation(un_char *weights, uint32_t *inputs, un_char len_hidden_layers);
void forward_propagation(uint32_t *inputs, un_char n_hidden_layers, un_char len_hidden_layers, un_char n_outputs, uint32_t *outputs);
uint32_t ReLu(uint32_t val);


int main() {
    un_char n_inputs=8;
    un_char n_outputs=2;
    un_char n_hidden_layers=2;
    un_char len_hidden_layers=15;
    uint32_t inputs[8]={1,2,3,4,5,6,7,8}; //create a for loop to substitute the manual population
    uint32_t output[2]={1,2}; // same here
    network_initializer(n_inputs, n_hidden_layers, len_hidden_layers, n_outputs);
    print_hidden_layers(n_hidden_layers, len_hidden_layers);
    forward_propagation(inputs,n_hidden_layers, len_hidden_layers, n_outputs, output);
    return 0;
}

void network_initializer(un_char n_inputs, un_char n_hidden_layers, un_char len_hidden_layers, un_char n_outputs) {
    hidden_layers = (un_char **)malloc(n_hidden_layers * sizeof(un_char *));
    hidden_bias = (un_char**)malloc(n_hidden_layers * sizeof(un_char *));

    if (hidden_layers==NULL|| hidden_bias==NULL){
            printf("ERROR while allocating memory.\n");
            return;
        }

    un_char i;
    for (i = 0; i < n_hidden_layers; i++) {
        hidden_layers[i] = (un_char *)malloc((len_hidden_layers+1) * sizeof(un_char));
        hidden_bias[i]=(un_char*)malloc((len_hidden_layers+1) * sizeof(un_char));

        if (hidden_layers[i]==NULL || hidden_bias[i]==NULL){
            printf("ERROR while allocating memory.\n");
            return;
        }
        layers_creator(len_hidden_layers, hidden_layers[i], hidden_bias[i]);
    }
}

void layers_creator(un_char x, un_char *hidden_weights, un_char *hidden_bias_weight) {
    un_char i;
    for (i = 0; i < x+1; i++) {
        hidden_weights[i] = i;
        hidden_bias_weight[i]=i;
    }
}

void print_hidden_layers(un_char n_hidden_layers, un_char len_hidden_layers) {
    un_char i, j;

    for (i = 0; i < n_hidden_layers; i++) {
        for (j = 0; j < len_hidden_layers+1; j++) {
            printf("%hhu ", hidden_layers[i][j]);
        }
        printf("\n");
    }

    printf("-0-0-0-0-0-\n");

    for (i = 0; i < n_hidden_layers; i++) {
        for (j = 0; j < len_hidden_layers+1; j++) {
            printf("%hhu ", hidden_bias[i][j]);
        }
        printf("\n");
    }
}

void forward_propagation(uint32_t *inputs, un_char n_hidden_layers, un_char len_hidden_layers, un_char n_outputs, uint32_t *outputs){

un_char i,j;
for (i=0; i<n_hidden_layers; i++){
    uint32_t next_inputs[len_hidden_layers];
    for (j=0; j<len_hidden_layers; j++){
        uint32_t val_activation = neuron_activation(hidden_layers[i], inputs, len_hidden_layers);
        uint32_t new_output= ReLu(val_activation);
        next_inputs[j]=new_output;
    }
    inputs=next_inputs;
};
for (i=0; i<n_outputs;i++){
        outputs[i]=inputs[i];
}
}

uint32_t neuron_activation(un_char *weights, uint32_t *inputs, un_char len_hidden_layers){
    uint32_t activation=weights[len_hidden_layers];
    un_char i;
    for (i=0; i<len_hidden_layers; i++){
        activation+= weights[i]*inputs[i];
        //printf("%hhu\n",weights[i]);
    }
    printf("%d\n",i);
    return activation;
}

uint32_t ReLu(uint32_t val){
    if (val<0){
        return 0;
    }
    return val;
}
