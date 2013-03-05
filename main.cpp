#include "perceptron.h"
#include "neuralnet.h"


using namespace std;

int main()
{
    Perceptron a1;
    NeuralNet n1;


    //Borrando los Ficheros existentes
    a1.clearFile("./datasets/outTest.csv");
    a1.clearFile("./datasets/inputWeights.csv");
    a1.clearFile("./datasets/hiddenWeights.csv");
    a1.clearFile("./datasets/outWeights.csv");


    //Inicializando la Topologia de la red
    n1.initNeuralNet(4,8,1);
    //Umbralizando los histogramas
    n1.umbralize("./datasets/testNet.csv","./datasets/umbralTest.csv");
    n1.umbralize("./datasets/prueba32.csv","./datasets/umbral.csv");
    //Aplicando Entrenamiento de Retro-propagacion
    n1.backPropagationTraining("./datasets/umbralTest.csv",1000);

    //Probando la red Resultante
    n1.testNeuralNet("./datasets/umbral.csv","./datasets/inputWeights.csv","./datasets/hiddenWeights.csv","./datasets/outWeights.csv","./datasets/test2_4.csv");
    //Desplegando en pantalla
    n1.showNetwork();

    return 0;
}

