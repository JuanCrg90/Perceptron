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
}


void NeuralNet::setGlobalError(double e)
{
    globalError=e;
}

double NeuralNet::getGlobalError()
{
    return globalError;
}


void NeuralNet::initNeuralNet(int in, int hidden, int out)
{
    //Init perceptron Layers
    inLayer.resize(in);
    hiddenLayer.resize(hidden);
    outLayer.resize(out);
}


void NeuralNet::setRandomWeights(int inputsNum)
{
    // set weights on the Input layer

    for(unsigned int i=0;i<inLayer.size();i++)
    {
        inLayer[i].setRandomWeights(inputsNum);
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
    this->O.clear();



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



    // clear inputs in all layers
    for(unsigned int i=0;i<inLayer.size();i++) //input
    {
        inLayer[i].clearInputs();
    }

    for(unsigned int i=0;i<hiddenLayer.size();i++) //hidden
    {
        hiddenLayer[i].clearInputs();
    }

    for(unsigned int i=0;i<outLayer.size();i++) //output
    {
        outLayer[i].clearInputs();
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


void NeuralNet::SolveNeuralNet(vector<double> xi)
{
    this->xi=xi;
    this->O.clear();


    // clear inputs in all layers
    for(unsigned int i=0;i<inLayer.size();i++) //input
    {
        inLayer[i].clearInputs();
    }

    for(unsigned int i=0;i<hiddenLayer.size();i++) //hidden
    {
        hiddenLayer[i].clearInputs();
    }

    for(unsigned int i=0;i<outLayer.size();i++) //output
    {
        outLayer[i].clearInputs();
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


void NeuralNet::testNeuralNet(string examples, string inWeights, string hiddenWeights, string outWeights, string outFile)
{
    ofstream out;

    CsvHandler csvExamples;
    CsvHandler csvIn;
    CsvHandler csvHid;
    CsvHandler csvOut;

    vector<double> aux;
    vector<double> w;
    vector<double> x;
    double theta;



    csvExamples.loadCsv(examples);
    csvIn.loadCsv(inWeights);
    csvHid.loadCsv(hiddenWeights);
    csvOut.loadCsv(outWeights);

    out.open(outFile.c_str(),ios_base::app);
    if(!out.is_open())
    {
        cout<<"Unable create out file";
        exit(1);
    }


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


    //solve for each example
    for(int i=0;i<csvExamples.getNumRows();i++)
    {
        //copy example inputs from the csv object
        aux=CsvHandler::toDouble(csvExamples.getRow(i));
        x.assign(aux.begin(),aux.end()-1);
        this->xi=x;

        //clean inputs in hidden layer
        for(unsigned int i=0;i<hiddenLayer.size();i++)
        {
            hiddenLayer[i].clearInputs();
        }

        //clean inputs in output layer
        for(unsigned int i=0;i<outLayer.size();i++)
        {
            outLayer[i].clearInputs();
        }


        // Set inputs in the input Layer (the method include the clean)
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
        this->O.clear();
        for(unsigned int i=0;i<outLayer.size();i++)
        {
            this->O.push_back(outLayer[i].getO());
        }


        //save result inputs and output
        for(unsigned int i=0;i<this->xi.size();i++)
        {
            out<<this->xi[i]<<",";
        }
        //only works with 1 output
        for(unsigned int i=0;i<this->O.size();i++)
        {
            out<<this->O[i]<<endl;
        }



    }

    out.close();

}


void NeuralNet::showNetwork()
{
    cout<<"General information"<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"inputs"<<endl;
    for(unsigned int i=0;i<this->xi.size();i++)
    {
        cout<<"x"<<i<<"\t";
    }
    cout<<endl;
    for(unsigned int i=0;i<this->xi.size();i++)
    {
        cout<<this->xi[i]<<"\t";
    }
    cout<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"outputs"<<endl;
    for(unsigned int i=0;i<this->O.size();i++)
    {
        cout<<"O"<<i<<"\t";
    }
    cout<<endl;
    for(unsigned int i=0;i<this->O.size();i++)
    {
        cout<<this->O[i]<<"\t";
    }
    cout<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"Input layer"<<endl;
    for(unsigned int i=0;i<inLayer.size();i++)
    {

        inLayer[i].showAll();
        cout<<endl;
    }
    cout<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"Hidden layer"<<endl;
    for(unsigned int i=0;i<hiddenLayer.size();i++)
    {

        hiddenLayer[i].showAll();
        cout<<endl;
    }
    cout<<endl;
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"output layer"<<endl;
    for(unsigned int i=0;i<outLayer.size();i++)
    {

        outLayer[i].showAll();
        cout<<endl;
    }

}


void NeuralNet::saveWeights(string in, string hidd, string out)
{
    ofstream outIn,outHidd,outOut;

    //Write the Input layer
    outIn.open(in.c_str());

    if(!outIn.is_open())
    {
        cout<<"Unable Open "<<in.c_str();
        exit(1);
    }

    for(unsigned int i=0; i<inLayer.size();i++)
    {
        for(unsigned int j=0;j<inLayer[i].getWeights().size();j++)
        {
            outIn<<inLayer[i].getWeight(j)<<",";
        }
        outIn<<inLayer[i].getTheta()<<endl;
    }
    outIn.close();


    //Write the hidden layer
    outHidd.open(hidd.c_str());

    if(!outHidd.is_open())
    {
        cout<<"Unable Open "<<hidd.c_str();
        exit(1);
    }

    for(unsigned int i=0; i<hiddenLayer.size();i++)
    {
        for(unsigned int j=0;j<hiddenLayer[i].getWeights().size();j++)
        {
            outHidd<<hiddenLayer[i].getWeight(j)<<",";
        }
        outHidd<<hiddenLayer[i].getTheta()<<endl;
    }
    outHidd.close();

    //Write the output layer
    outOut.open(out.c_str());

    if(!outOut.is_open())
    {
        cout<<"Unable Open "<<out.c_str();
        exit(1);
    }

    for(unsigned int i=0; i<outLayer.size();i++)
    {
        for(unsigned int j=0;j<outLayer[i].getWeights().size();j++)
        {
            outOut<<outLayer[i].getWeight(j)<<",";
        }
        outOut<<outLayer[i].getTheta()<<endl;
    }
    outOut.close();



    cout<<"The weights are saved";

}




void NeuralNet::backPropagationTraining(string name,int it)
{
    CsvHandler csv;

    csv.loadCsv(name);


    vector<double> aux;
    vector<double> x;
    vector<double> auxW; //auxilar for weigths adapt
    double o;
    int k=0;

    double sum=0;

    double gError=0.0;
    double outGError=0.0;


    aux.resize(csv.getNumCols());
    x.resize(csv.getNumCols()-1);


    // Step 1: Set All weight and node offset to small random values
    setRandomWeights(csv.getNumCols()-1);



    //Step 2 Present Input and Desired Outputs
    while(k!=it)
    {
        for(int j=0;j<csv.getNumRows();j++) //examples
        {
            aux=CsvHandler::toDouble(csv.getRow(j));
            copy(aux.begin(),aux.end()-1,x.begin());
            o=aux[aux.size()-1];

            //Step 3 Calcule actual Outputs
            SolveNeuralNet(x);


            // Step 4 Calculate the error
            //output layer
            for(unsigned int i=0;i<outLayer.size();i++)
            {
                gError=o - this->O[i];
                outLayer[i].setDelta((gError)*this->O[i]*(1-this->O[i]));
                globalError+=gError;
                gError=0.0;
            }

            //hidden layer
            for(unsigned int i=0;i<hiddenLayer.size();i++)
            {
                sum=0;

                for(unsigned int j=0;j<outLayer.size();j++)
                {
                    sum+=outLayer[j].getDelta()*outLayer[j].getWeight(i);
                }

                hiddenLayer[i].setDelta(hiddenLayer[i].getO()*(1-hiddenLayer[i].getO())*sum);
            }


            //input layer
            for(unsigned int i=0;i<inLayer.size();i++)
            {
                sum=0;

                for(unsigned int j=0;j<hiddenLayer.size();j++)
                {
                    sum+=hiddenLayer[j].getDelta()*hiddenLayer[j].getWeight(i);
                }

                inLayer[i].setDelta(inLayer[i].getO()*(1-inLayer[i].getO())*sum);
            }

            // Step 5 Adapt Weights

            //Out Layer
            for(unsigned int i=0;i<outLayer.size();i++) //neurone
            {
                auxW.clear();

                auxW=outLayer[i].getWeights();
                for(unsigned int j=0;j<outLayer[i].getInputs().size();j++) //inputs
                {
                    auxW[j]+=ALPHA*outLayer[i].getDelta()*outLayer[i].getInput(j);
                }
                outLayer[i].setWeight(auxW); //insert the calculate new weights in the neurone

                //adapt bias
                outLayer[i].setTheta(outLayer[i].getTheta()-ALPHA*outLayer[i].getDelta());
            }

            //Hidden Layer
            for(unsigned int i=0;i<hiddenLayer.size();i++) //neurone
            {
                auxW.clear();

                auxW=hiddenLayer[i].getWeights();
                for(unsigned int j=0;j<hiddenLayer[i].getInputs().size();j++) //inputs
                {
                    auxW[j]+=ALPHA*hiddenLayer[i].getDelta()*hiddenLayer[i].getInput(j);
                }
                hiddenLayer[i].setWeight(auxW); //insert the calculate new weights in the neurone

                //adapt bias
                hiddenLayer[i].setTheta(hiddenLayer[i].getTheta()-ALPHA*hiddenLayer[i].getDelta());
            }

            //input layer
            for(unsigned int i=0;i<inLayer.size();i++) //neurone
            {
                auxW.clear();

                auxW=inLayer[i].getWeights();
                for(unsigned int j=0;j<inLayer[i].getInputs().size();j++) //inputs
                {
                    auxW[j]+=ALPHA*inLayer[i].getDelta()*inLayer[i].getInput(j);
                }
                inLayer[i].setWeight(auxW); //insert the calculate new weights in the neurone

                //adapt bias
                inLayer[i].setTheta(inLayer[i].getTheta()-ALPHA*inLayer[i].getDelta());
            }



        } //end examples

        //Step 6, Calculate Global Error

        for(unsigned int i=0;i<this->O.size();i++)
        {            
            cout<<k<<" "<<"Global Error:"<<globalError<<endl;
        }
        globalError=0.0;

        k++;

        //Repeat by going to step 2
    }

    //save Weights
    saveWeights();

}
