#ifndef NEURALNET_H
#define NEURALNET_H

#include <perceptron.h>


class NeuralNet
{
private:

    /**
    * @brief Inputs Vector
    */
    vector<double> xi;


    /**
    * @brief In Layer
    */
    vector<Perceptron> inLayer;


    /**
    * @brief Hidden Layer
    */
    vector<Perceptron> hiddenLayer;

    /**
    * @brief Out Layer
    */
    vector<Perceptron> outLayer;



public:
    NeuralNet();


};

#endif // NEURALNET_H
