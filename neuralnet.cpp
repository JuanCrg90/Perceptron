#include "neuralnet.h"

NeuralNet::NeuralNet()
{    
}


NeuralNet::NeuralNet(int in, int hidden, int out)
{
    //Init perceptron Layers
    inLayer.resize(in);
    hiddenLayer.resize(hidden);
    outLayer.resize(out);

    Perceptron a1;




/*
    //connect inputs with in Layer

    for(unsigned int i=0;inLayer.size();i++)
    {
        inLayer[i].setInput(xi);
    }

    //Connect in layer outputs in hidden Layer inputs

    for(unsigned int i=0;i<inLayer.size();i++)
    {
        for(unsigned int j=0;j<hiddenLayer.size();j++)
        {
            hiddenLayer[j].setInput(inLayer[i].getO());
        }
    }

    //Connect hidden layer outputs in out layer inputs

    for(unsigned int i=0;i<hiddenLayer.size();i++)
    {
        for(unsigned int j=0;j<outLayer.size();j++)
        {
            outLayer[j].setInput(hiddenLayer[i].getO());
        }
    }
*/
}



void NeuralNet::initNeuralNet(int in, int hidden, int out)
{
    //Init perceptron Layers
    inLayer.resize(in);
    hiddenLayer.resize(hidden);
    outLayer.resize(out);
}

void NeuralNet::backPropagationTraining(string name,int it)
{
    Perceptron a;
    CsvHandler csv;

    csv.loadCsv(name);

    vector<double> aux;
    vector<double> x;
    double o;
    int k=0;

    aux.resize(csv.getNumCols());
    x.resize(csv.getNumCols()-1);





    // Step 1: Set All weight and node offset to small random values

    // set weights on the Input layer

    for(unsigned int i=0;i<inLayer.size();i++)
    {
        inLayer[i].setRandomWeights(csv.getNumCols()-1);
    }


    // set weights on the Hidden Layer

    for(unsigned int i=0;i<hiddenLayer.size();i++)
    {
        hiddenLayer[i].setRandomWeights(inLayer.size());
    }

    // set weights on the Output Layer

    for(unsigned int i=0;i<outLayer.size();i++)
    {
        outLayer[i].setRandomWeights(hiddenLayer.size());
    }


    //Step 2 Present Input and Desired Outputs


    while(k!=it)
    {
        for(int j=0;j<csv.getNumRows();j++)
        {
            aux=CsvHandler::toDouble(csv.getRow(j));
            copy(aux.begin(),aux.end()-1,x.begin());
            o=aux[aux.size()-1];

        }


    }
}

void NeuralNet::SolveNeuralNet(vector<double> xi, string inWeights,string hiddenWeights,string outWeights)
{

    CsvHandler csvIn;
    CsvHandler csvHid;
    CsvHandler csvOut;

    vector<double> aux;
    vector<double> w;
    double theta;


    csvIn.loadCsv(inWeights);
    csvHid.loadCsv(hiddenWeights);
    csvOut.loadCsv(outWeights);

    this->xi=xi;



    //Set weights in each layer

    //Input Layer
    for(int i=0;i<csvIn.getNumRows();i++)
    {
        aux=CsvHandler::toDouble(csvIn.getRow(i));
        w.assign(aux.begin(),aux.end()-1);
        theta=aux.back();

        inLayer[i].setWeight(w);
        inLayer[i].setTheta(theta);

    }

    //Hidden Layer
    for(int i=0;i<csvHid.getNumRows();i++)
    {
        aux=CsvHandler::toDouble(csvHid.getRow(i));
        w.assign(aux.begin(),aux.end()-1);
        theta=aux.back();

        hiddenLayer[i].setWeight(w);
        hiddenLayer[i].setTheta(theta);
    }

    //Out Layer
    for(int i=0;i<csvOut.getNumRows();i++)
    {
        aux=CsvHandler::toDouble(csvOut.getRow(i));
        w.assign(aux.begin(),aux.end()-1);
        theta=aux.back();

        outLayer[i].setWeight(w);
        outLayer[i].setTheta(theta);
    }


    // Set inputs in the input Layer
    for(unsigned int i=0;i<inLayer.size();i++)
    {
        inLayer[i].setInput(this->xi);
    }

    //Solve input Layer

    for(unsigned int i=0;i<inLayer.size();i++)
    {
        inLayer[i].solve(SIGMOIDAF,LAMBDA);
    }

    //Connect input layer outs with the hidden Layer inputs
    for(unsigned i=0;i<hiddenLayer.size();i++)
    {
        for(unsigned int j=0;j<inLayer.size();j++)
        {
            hiddenLayer[i].setInput(inLayer[j].getO());
        }
    }

    //Solve hidden Layer
    for(unsigned int i=0;i<hiddenLayer.size();i++)
    {
        hiddenLayer[i].solve(SIGMOIDAF,LAMBDA);
    }

    //Connect hidden Layer outs with the output layer inputs
    for(unsigned i=0;i<outLayer.size();i++)
    {
        for(unsigned int j=0;j<hiddenLayer.size();j++)
        {
            outLayer[i].setInput(hiddenLayer[j].getO());
        }
    }

    //Solve output Layer
    for(unsigned int i=0;i<outLayer.size();i++)
    {
        outLayer[i].solve(SIGMOIDAF,LAMBDA);
    }

    //copy outputs
    for(unsigned int i=0;i<outLayer.size();i++)
    {
        this->O.push_back(outLayer[i].getO());
    }

}

