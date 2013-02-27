#include "csvhandler.h"


CsvHandler::CsvHandler()
{
}

void CsvHandler::loadCsv(string name)
{
    ifstream in;
    string line;
    vector <string> record;

    in.open(name.c_str(),ios::in);

    if(in.is_open())
    {
        while(!in.eof())
        {

            if(!getline(in,line)) break;

            istringstream tok(line);

            while(tok)
            {
                if(!getline(tok,line,',') )break;
                record.push_back(line);
            }

            data.push_back(record);
            record.clear();

        }

        rows=data.size();
        cols=data.at(0).size();
    }

    in.close();
}

void CsvHandler::saveCsv(vector<vector<string> > data, string file)
{
    ofstream out;
    out.open(file.c_str());


    if(out.is_open())
    {
        for(unsigned int i=0;i<data.size();i++)
        {
            for(unsigned int j=0;j<data[i].size();j++)
            {
                out<<data[i][j];

                if(j<data[i].size()-1)
                {
                    out<<",";
                }


            }
            out<<endl;
        }
    }

}

void CsvHandler::saveCsv(vector<vector<int> > data, string file)
{
    ofstream out;
    out.open(file.c_str());


    if(out.is_open())
    {
        for(unsigned int i=0;i<data.size();i++)
        {
            for(unsigned int j=0;j<data[i].size();j++)
            {
                out<<data[i][j];

                if(j<data[i].size()-1)
                {
                    out<<",";
                }
            }
            out<<endl;
        }
    }


}

void CsvHandler::saveCsv(vector<vector<float> > data, string file)
{
    ofstream out;
    out.open(file.c_str());


    if(out.is_open())
    {
        for(unsigned int i=0;i<data.size();i++)
        {
            for(unsigned int j=0;j<data[i].size();j++)
            {
                out<<data[i][j];

                if(j<data[i].size()-1)
                {
                    out<<",";
                }
            }
            out<<endl;
        }
    }

}

void CsvHandler::saveCsv(vector<vector<double> > data, string file)
{
    ofstream out;
    out.open(file.c_str());


    if(out.is_open())
    {
        for(unsigned int i=0;i<data.size();i++)
        {
            for(unsigned int j=0;j<data[i].size();j++)
            {
                out<<data[i][j];

                if(j<data[i].size()-1)
                {
                    out<<",";
                }
            }
            out<<endl;
        }
    }

}

void CsvHandler::displayCsv()
{

    cout<<"Num columns: "<<cols<<endl;
    cout<<"Num rows: "<<rows<<endl<<endl;

    cout<<"-------------------------------------------------------------------------------"<<endl;

    for(unsigned int i=0;i<data.size();i++)
    {
        for(unsigned int j=0;j<data[i].size();j++)
        {
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }

}

void CsvHandler::displayCols()
{
    cout<<"Num columns: "<<cols<<endl;
}

void CsvHandler::displayRows()
{
    cout<<"Num rows: "<<rows<<endl;
}

void CsvHandler::setNumCols(int c)
{
    cols=c;
}

void CsvHandler::setNumRows(int r)
{
    rows=r;
}

int CsvHandler::getNumCols()
{
    return cols;
}

int CsvHandler::getNumRows()
{
    return rows;
}


vector<string> CsvHandler::getCol(int num)
{
    vector<string> colSel;
    colSel.resize(getNumRows());    

    for(int i=0;i<getNumRows();i++)
    {
        colSel[i]=data[i][num];
    }

    return colSel;

}

vector<string> CsvHandler::getRow(int num)
{
    vector<string> rowSel;
    rowSel.resize(getNumCols());


    for(int i=0;i<getNumCols();i++)
    {
        rowSel[i]=data[num][i];
    }

    return rowSel;

}

void CsvHandler::clear()
{
    rows=0;
    cols=0;
    data.clear();
}

vector<double> CsvHandler::toDouble(vector<string> csv)
{
    vector<double> toDoub;
    toDoub.resize(csv.size());


    for(unsigned int i=0;i<csv.size();i++)
    {
        stringstream str(csv[i]);

        str>>toDoub[i];
    }

    return toDoub;
}

vector<float> CsvHandler::toFloat(vector<string> csv)
{
    vector<float> toDoub;
    toDoub.resize(csv.size());


    for(unsigned int i=0;i<csv.size();i++)
    {
        stringstream str(csv[i]);

        str>>toDoub[i];
    }

    return toDoub;

}

vector<int> CsvHandler::toInt(vector<string> csv)
{
    vector<int> toint;
    toint.resize(csv.size());


    for(unsigned int i=0;i<csv.size();i++)
    {
        stringstream str(csv[i]);

        str>>toint[i];
    }

    return toint;
}


