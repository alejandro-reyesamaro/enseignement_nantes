#include "parser.h"

#include <vector>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <fstream>

using namespace std;

Parser::Parser(){}

void trim_string(std::string & code)
{
    boost::trim(code);
}

int str2int(string str)
{
    string::size_type sz;   // alias of size_t
    int i_dec = std::stoi (str,&sz);
    return i_dec;
}

SparseRow sparse_row_from_text(string str)
{
    boost::trim(str);
    stringstream ss(str);
    string item;
    char separator = ' ';
    SparseRow sr;

    // extracting m
    if(std::getline(ss, item, separator))
    {
        boost::trim(item);
        sr.m = str2int(item);
    }
    sr.indices = new int[sr.m];
    sr.values  = new int[sr.m];

    // extracting the indexes
    for(int i = 0; i < sr.m; i++)
    {
        if (std::getline(ss, item, separator))
        {
            boost::trim(item);
            sr.indices[i] = str2int(item);
        }
    }

    // extracting the values
    for(int i = 0; i < sr.m; i++)
    {
        if (std::getline(ss, item, separator))
        {
            boost::trim(item);
            sr.values[i] = str2int(item);
        }
    }
    return sr;
}

pair<SparseMatrix, SparseMatrix> sparse_matrix_from_text(string path)
{
    SparseMatrix sm1;
    SparseMatrix sm2;

    string line;
    ifstream infile(path);
    if (getline(infile, line))
    {
        boost::trim(line);
        stringstream ss(line);
        string item;
        char separator = ' ';

        // extracting n
        if(std::getline(ss, item, separator))
        {
            boost::trim(item);
            sm1.n = str2int(item);
            sm1.rows = new SparseRow[sm1.n];
            sm2.n = str2int(item);
            sm2.rows = new SparseRow[sm2.n];
        }
        // extracting m
        if(std::getline(ss, item, separator))
        {
            boost::trim(item);
            sm1.m = str2int(item);
            sm2.m = str2int(item);
        }
    }

    // extracting matrix 1
    for(int i = 0; i < sm1.n; i++)
    {
        if (getline(infile, line))
            sm1.rows[i] = sparse_row_from_text(line);
    }
    // extracting matrix 2
    for(int i = 0; i < sm2.n; i++)
    {
        if (getline(infile, line))
            sm2.rows[i] = sparse_row_from_text(line);
    }
    return {sm1, sm2};
}

pair<SparseMatrix, SparseMatrix> Parser::parse(string path)
{
    return sparse_matrix_from_text(path);
}
