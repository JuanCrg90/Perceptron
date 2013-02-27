/**
* @file csvhandler.h
* @brief Class for manage csv files
* @author Juan Carlos Ruiz González
* Universidad De Guanajuato
* Email: juancarlosruiz14@gmail.com
* @date 7/02/2013
*/

#ifndef CSVHANDLER_H
#define CSVHANDLER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<algorithm>

using namespace std;



class CsvHandler
{

private:
    int cols;
    int rows;
    vector< vector<string> > data;

public:

    /**
    * @brief Constructor
    */
    CsvHandler();

    /**
    * @brief Load a CSV file
    * @param name name of the csv file, include extensión
    */
    void loadCsv(string name);


    /**
    * @brief save vector to file
    * @param vector< vector<string> > data info to save
    * @param string file name of file
    */
    void saveCsv(vector< vector<string> > data, string file="out.csv");

    /**
    * @brief save vector to file
    * @param vector< vector<int> > data info to save
    * @param string file name of file
    */
    void saveCsv(vector< vector<int> > data, string file="out.csv");

    /**
    * @brief save vector to file
    * @param vector< vector<float> > data info to save
    * @param string file name of file
    */
    void saveCsv(vector< vector<float> > data, string file="out.csv");

    /**
    * @brief save vector to file
    * @param vector< vector<double> > data info to save
    * @param string file name of file
    */
    void saveCsv(vector< vector<double> > data, string file="out.csv");





    /**
    * @brief Display General Info
    */
    void displayCsv();

    /**
    * @brief Display num of Columns
    */
    void displayCols();

    /**
    * @brief Display num of Rows
    */
    void displayRows();

    /**
    * @brief Set num of columns
    */
    void setNumCols(int c);

    /**
    * Set num of rows
    */
    void setNumRows(int r);

    /**
    * @brief Get num of cols
    * @return int
    */
    int getNumCols();

    /**
    * @brief Get num of rows
    * @return int
    */
    int getNumRows();

    /**
    * @brief Return Data in the selected Column
    * @param num selected col
    * @return vector<string>
    */
    vector<string> getCol(int num);

    /**
    * @brief Return Data in the selected Row
    * @param num selected row
    * @return vector<string>
    */
    vector<string> getRow(int num);


    /**
    * @brief Clear the object
    */
    void clear();

    /**
      * @brief convert to vector<double> a vector<string>
      * @param csv vector of strings
      * @return vector<double>
      */
    static vector<double> toDouble(vector<string> csv);

    /**
      * @brief convert to vector<float> a vector<string>
      * @param csv vector of strings
      * @return vector<double>
      */

    static vector<float> toFloat(vector<string> csv);

    /**
      * @brief convert to vector<int> a vector<string>
      * @param csv vector of strings
      * @return vector<int>
      */
    static vector<int> toInt(vector<string> csv);










};

#endif // CSVHANDLER_H
