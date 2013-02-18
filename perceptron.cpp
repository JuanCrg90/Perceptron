#include "perceptron.h"

Perceptron::Perceptron()
{
    this->x.clear();
    this->w.clear();
    this->theta=0.0;
    this->y=0.0;
    this->O=-1.0;
    this->delta=0.0;

}


Perceptron::~Perceptron()
{

}

/////////////////////////////////////////////////////////////////////////////////////

void Perceptron::setInput(double xi)
{
    x.push_back(xi);
}


void Perceptron::setInput(vector<double> xi)
{
    x.clear();
    x.resize(xi.size());

    copy(xi.begin(),xi.end(),x.begin());

}

void Perceptron::setWeight(double wi)
{
    w.push_back(wi);
}

void Perceptron::setWeight(vector<double> wi)
{
    w.clear();
    w.resize(wi.size());
    copy(wi.begin(),wi.end(),w.begin());
}


void Perceptron::setTheta(double theta)
{
    this->theta=theta;
}


void Perceptron::setO(double o)
{
    O=o;
}


void Perceptron::setPerceptron(vector<double> xi, vector<double> wi, double theta)
{
    x.clear();
    x.resize(xi.size());
    copy(xi.begin(),xi.end(),x.begin());

    w.clear();
    w.resize(wi.size());
    copy(wi.begin(),wi.end(),w.begin());

    this->theta=theta;
}


void Perceptron::setRandomWeights(int num)
{
    srand(time(NULL));

    for(int i=0;i<num;i++)
    {
        setWeight((rand()%11)/10.0);
    }

    setTheta((rand()%11)/10.0);
    //setTheta(1.0);

}


/////////////////////////////////////////////////////////////////////////////////////
double Perceptron::getInput(int i)
{
    return x.at(i);
}

vector<double> Perceptron::getInputs()
{
    return x;
}


double Perceptron::getWeight(int i)
{
    return w.at(i);
}

vector<double> Perceptron::getWeights()
{
    return w;
}

double Perceptron::getTheta()
{
    return this->theta;
}


double Perceptron::getO()
{
    return O;
}

/////////////////////////////////////////////////////////////////////////////////////
void Perceptron::clear()
{
    this->x.clear();
    this->w.clear();
    this->theta=0.0;
    this->y=0.0;
    this->O=-1.0;
}


void Perceptron::clearInputs()
{
    x.clear();
}

/////////////////////////////////////////////////////////////////////////////////////

double Perceptron::solve(int opt,double d)
{
    double sum=0.0;


    for(unsigned int i=0;i<x.size();i++)
    {
        sum+=w[i]*x[i];
    }

    this->y=sum-theta;

    switch(opt)
    {
    case LINEARAF:
        this->O=linear(d,y);
        break;
    case STEPAF:
        this->O=step(d,y);
        break;
    case SIGMOIDAF:
        this->O=sigmoid(d,y);
        break;
    case SIGMOIDBIPAF:
        this->O=sigmoidBip(d,y);
        break;

    }

    return O;

}


/////////////////////////////////////////////////////////////////////////////////////

double Perceptron::linear(double alpha, double x)
{
    return alpha*x;
}

int Perceptron::step(double offset, double x)
{
    double r=(x>=0.0-offset)?1:0;

    return r;
}

double Perceptron::sigmoid(double lambda, double y)
{
    return (1/(1+exp(-lambda*y)));

}

double Perceptron::sigmoidBip(double lambda, double y)
{
    return (2/(1+exp(-lambda*y))-1);
}

double Perceptron::diffSigmoid(double lambda, double y)
{
    return sigmoid(lambda,y)*(1-sigmoid(lambda,y));
}

double Perceptron::diffSigmoidBip(double lambda, double y)
{
    return 0.5*(1+sigmoidBip(lambda,y))*(1-sigmoidBip(lambda,y));
}

/////////////////////////////////////////////////////////////////////////////////////

void Perceptron::showInputs()
{

    cout<<"Inputs:"<<endl;
    for(unsigned int i=0;i<x.size();i++)
    {
        cout<<"x"<<i<<"="<<x.at(i)<<endl;
    }

}

void Perceptron::showWeights()
{
    cout<<"Weights:"<<endl;
    for(unsigned int i=0;i<w.size();i++)
    {
        cout<<"w"<<i<<" = "<<w.at(i)<<endl;
    }
}

void Perceptron::showThetha()
{
    cout<<"theta = "<<theta<<endl;
}

void Perceptron::showO()
{
    cout<<"O = "<<O<<endl;
}

void Perceptron::showAll()
{

    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"General Information"<<endl;

    cout<<"theta = "<<theta<<endl;
    cout<<"O = "<<O<<endl<<endl;
    cout<<"Inputs"<<"\t\t\t"<<"Weights"<<endl;


    for(unsigned int i=0;i<x.size();i++)
    {
        cout<<"x"<<i<<" = "<<x.at(i)<<"\t\t"<<"w"<<i<<" = "<<w.at(i)<<endl;
    }
    cout<<endl;

}

void Perceptron::showResults()
{

    for(unsigned int i=0;i<x.size();i++)
    {
        cout<<"x"<<i<<"\t";
    }
    cout<<"y"<<"\t";
    cout<<"O"<<endl;

    for(unsigned int i=0;i<x.size();i++)
    {
        cout<<x.at(i)<<"\t";
    }
    cout<<y<<"\t";
    cout<<O<<endl;

}

/////////////////////////////////////////////////////////////////////////////////////

void Perceptron::loadData()
{


}

void Perceptron::saveData()
{

}


/////////////////////////////////////////////////////////////////////////////////////

void Perceptron::saveResults(string name)
{

    ofstream out;
    out.open(name.c_str(),ios::app);

    for(unsigned int i=0;i<x.size();i++)
    {
        out<<x.at(i)<<",";
    }

    out<<O<<endl;


    out.close();
}



void Perceptron::clearFile(string name)
{
    ofstream out;
    out.open(name.c_str(),ios::out);
    out.close();
}


void Perceptron::train(string file, int it)
{
    CsvHandler csv;
    vector<double> aux;
    vector<double> x;
    int i=0;
    double o;

    csv.loadCsv(file);

    aux.resize(csv.getNumCols());
    x.resize(csv.getNumCols()-1);

    setRandomWeights(x.size());
    showWeights();
    showThetha();

    while(i!=it)
    {
        for(int j=0;j<csv.getNumRows();j++)
        {
            aux=CsvHandler::toDouble(csv.getRow(j));
            copy(aux.begin(),aux.end()-1,x.begin());
            o=aux[aux.size()-1];
            trainNeuron(x,o);
        }

        i++;
    }
}


void Perceptron::trainNeuron(vector<double> x, double O)
{
    vector<double> delta;
    double error;
    double sum=0.0;

    this->setInput(x);

    delta.resize(x.size());

    for(unsigned int i=0;i<x.size();i++)
    {
        sum+=w[i]*x[i];
    }

    this->y=sum-theta;

    this->O=sigmoid(LAMBDA,y);

    error=O-this->O;
    cout<<"error: "<<error<<endl;

    this->theta-=ALPHA*error;


    for(unsigned int i=0;i<x.size();i++)
    {
        delta[i]=ALPHA*error*diffSigmoid(LAMBDA,y)*x[i];
        //delta[i]=ALPHA*error*x[i];
    }

    for(unsigned int i=0;i<x.size();i++)
    {
        w[i]+=delta[i];
    }

}

void Perceptron::setDelta(double delta)
{
    this->delta=delta;
}

double Perceptron::getDelta()
{
    return this->delta;
}



