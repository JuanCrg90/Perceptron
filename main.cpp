#include "perceptron.h"
#include "neuralnet.h"


using namespace std;

int main()
{
    Perceptron a1;
    NeuralNet n1;


    a1.clearFile("./datasets/outTest.csv");
    a1.clearFile("./datasets/inputWeights.csv");
    a1.clearFile("./datasets/hiddenWeights.csv");
    a1.clearFile("./datasets/outWeights.csv");

    n1.initNeuralNet(4,8,1);

    n1.backPropagationTraining("./datasets/trainC.csv",5000);
    n1.testNeuralNet("./datasets/train.csv","./datasets/inputWeights.csv","./datasets/hiddenWeights.csv","./datasets/outWeights.csv");
    n1.showNetwork();



    return 0;
}

