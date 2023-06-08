typedef unsigned char un_char;

un_char my_input[n_inputs]={};

void network_initializer(un_char n_inputs, un_char n_hidden_layers, un_char len_hidden_layers ,un_char n_outputs){

un_char i;
un_char hidden_layers[n_hidden_layers]={}

for (i=1; i<= n_hidden_layers, i++){
    hidden_layers[i]=layers_creator(len_hidden_layers);
}

}

un_char layers_creator(un_char x){
static un_char hidden_weights[x]={};
un_char i;
for(i=0, i<x, i++){
    hidden_weights[i]=i;
}

return hidden_weights

}