/**
* @file perceptron.h
* @brief Perceptron simple 1.0
* @author: Juan Carlos Ruiz González
* Universidad de Guanajuato
* Email: juancarlosruiz14@gmail.com
* @date 7/02/2013
*/

#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include<algorithm>
#include<ctime>
#include "csv/csvhandler.h"



using namespace std;


#define LINEARAF 0
#define STEPAF 1
#define SIGMOIDAF 2
#define SIGMOIDBIPAF 3

#define ALPHA 0.2f
#define LAMBDA 1.0


/**
* @brief Simple perceptron Class
*/
class Perceptron
{


    vector <double> x; /** @brief Inputs */
    vector <double> w; /** @brief Weights */
    double theta; /** @brief bias value */
    double y; /** @brief output sum */
    double O; /** @brief output after the activation function*/
    double delta;






public:
    Perceptron();
    ~Perceptron();

    //Funciones de activación

    /**
    * @brief Linear AF $f(x)=\alpha*x$
    * @param alpha alpha value
    * @param x input value
    * @return double
    */
    static double linear(double alpha,double x);

    /**
    * @brief step AF
    * @param offset offset value
    * @param x input
    * @return int
    */

    static int step(double offset,double x);

    /**
    * @brief sigmoid AF $1/(1+exp(-\lambda*y))$;
    * @param lambda lambda value
    * @param y input
    * @return double
    */
    static double sigmoid(double lambda,double y);

    /**
    * @brief sigmoid Bipolar AF $2/(1+\exp^(-\lambda*y))-1$;
    * @param lambda lambda value
    * @param y input
    * @return double
    */

    static double sigmoidBip(double lambda,double y);


    /**
    * @brief derivate of sigmoid AF $f(x)'=sigmoid(x)(1-sigmoid(x))$;
    * @param lambda lambda value
    * @param y input
    * @return double
    */
    static double diffSigmoid(double lambda, double y);

    /**
    * @brief derivate of sigmoid Bipolar AF $0.5*(1+sigmoidBip(x))(1-sigmoidBip(x))$;
    * @param lambda lambda value
    * @param y input
    * @return double
    */
    static double diffSigmoidBip(double lambda, double y);


    //Sets

    /**
    * @brief add an input (push)
    * @param xi input
    */
    void setInput(double xi); //agrega una entrada (push)

    /**
    * @brief insert an input vector
    * @param xi  vector<double> input
    */
    void setInput( vector<double> xi); //Inserta vector de entradas

    /**
    * @brief add a weight (push)
    * @param wi input
    */
    void setWeight(double wi); //agrega un peso (push)

    /**
    * @brief insert an weight vector
    * @param wi  vector<double> input
    */
    void setWeight(vector<double> wi); //inserta vector de entradas

    /**
    * @brief Set theta value (bias)
    * @param theta double value
    */
    void setTheta(double theta); //inserta el valor de theta


    /**
    * @brief Set out value O
    * @param o double value
    */
    void setO(double o); //inserta el valor de O

    /**
    * @brief initialize the perceptron
    * @param xi vector of inputs
    * @param wi vector of weights
    * @param theta bias value
    */
    void setPerceptron(vector<double> xi,vector<double> wi, double theta); //inicializa la neurona con los valores dados

    /**
    * @brief Set the random weights (include bias)
    * @param num number of inputs
    */
    void setRandomWeights(int num); //coloca pesos aleatorios igual a la cantitdad dada


    /**
    * @brief set delta value;
    * @param double delta delta value
    */
    void setDelta(double delta);


    //Gets

    /**
    * @brief return the input requested value
    * @param i input resquested
    * @return double
    */
    double getInput(int i); //regresa el valor de la entrada solicitada

    /**
    * @brief return all the inputs in a vector
    * @return vector<double>
    */
    vector<double> getInputs(); //regresa todas las entradas en un vector

    /**
    * @brief return the weight requested value
    * @param i input resquested
    * @return double
    */
    double getWeight(int i); //regresa el peso solicitado


    /**
    * @brief return all the weights in a vector
    * @return vector<double>
    */
    vector<double> getWeights(); //regresa todos los pesos en un vector

    /**
    * @brief get the bias value
    * @return double
    */
    double getTheta(); //regresa el valor de theta

    /**
    * @brief get the out value
    * @return double
    */
    double getO(); //regresa el valor de O

    /**
    * @brief get the delta value
    * @return double
    */
    double getDelta();



    //prints

    /**
    * @brief display the inputs
    */
    void showInputs();

    /**
    * @brief display the weights
    */
    void showWeights();

    /**
    * @brief display the bias
    */
    void showThetha();

    /**
    * @brief display the out
    */
    void showO();

    /**
    * @brief display general information
    */
    void showAll();

    /**
    * @brief display the inputs and the ouputs before and after the AF
    */
    void showResults();


    //File Manage
    void clearFile(string name);
    void loadData();
    void saveData();
    void saveResults(string name);




    //O=Fj(SUM(WX)-THETHA))

    /**
    * @brief Eval the perceptron with the inputs, weights and the selected AF
    * @param opt Activation Function
    * @param d offset/\lambda
    */
    double solve(int opt,double d);

    /**
    * @brief Clear the perceptron (all)
    */
    void clear();

    /**
    * @brief clear the inputs
    */
    void clearInputs();


    /**
    * @brief Load the Train Dataset and set tue iterations
    * @param file file name
    * @param it number of iterations
    */
    void train(string file, int it);

    /**
    * @brief Train the neuron
    * @param x inputs
    * @param O output
    */
    void trainNeuron(vector<double> x, double O);
};

#endif // PERCEPTRON_H
