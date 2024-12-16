#include <iostream>
using namespace std;

float empiricalExpectation(float (*probability)(float), float* inputs, int N){
    float sum = 0;
    for(int i = 0; i < N; i++){
        sum += probability(inputs[i]);
    }
    return sum / N;
}

// TODO: redefine in terms of moment for backprop when implementing matrices
float variance(float (*probability)(float), float* inputs, int N){
    float sum = 0;
    float expectation = empiricalExpectation(probability, inputs, N);
    for(int i = 0; i < N; i++){
        sum += pow(probability(inputs[i]) - expectation, 2);
    }
    return sum / N;
}

float monteCarloLoss(float(*probability)(float), float* inputs, int N){
    return pow(variance(probability, inputs, N) / N, 0.5);
}