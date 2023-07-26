# ANN

This project aims to build an Artificial Neural Network from scratch in C to detect fuel adulteration. Thus, MSP430F5529 was used as the microcontroller to read the sensors and also run the ANN after the training, which was done in python using a PC. The types of adulteration were distributed in two types: adulteration with alcohol, and adulteration with water. It is worth mentioning that the fuel was not adulterated when bought. This process was done by us to train the model. The level of adulteration varied between 5%, 10%, 15%, and 20% for each type of contamination. After the training, the ANN was responsible for determining whether the fuel was adultered or not. In total, 11 sensors were used, 9 of them to detect gases, 1 for temperature and the last one was chosen to measure the humidity of the samples. Given that the ANN processing has to be done by a microcontroller, which has low memory and processing power compared to a PC, memory mapping and velocity were variables that needed to be considered to make the project viable.


---
* Members: Pedro Augusto Giacomelli Fernandes (Pedro Giacomelli); Victor dos Reis Rodrigues.
* Electrical Engineering student - Universidade de Brasília (UnB)
* Areas of interest: AI and ML
