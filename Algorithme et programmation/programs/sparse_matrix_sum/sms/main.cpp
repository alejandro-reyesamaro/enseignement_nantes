#include "types.h"
#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// a) Implementing a function to verify if a matrix have been properly declared
bool valid_matrix(SparseMatrix M)
{
    bool valid = true;
    for (int i = 0; i < M.n; i++)
        valid = valid && (M.rows[i].m <= M.m);
    return valid;
}

// b) Implementing a function to verify if tow matrix can be added
bool valid_sum(SparseMatrix M1, SparseMatrix M2)
{
    return valid_matrix(M1) && valid_matrix(M2) && M1.n == M2.n && M1.m == M2.m;
}

// (given function)
int value_at(SparseRow row, int col)
{
    for(int i = 0; i < row.m; i++)
        if (row.indices[i] == col)
            return row.values[i];
    return 0;
}

// c) Implementing a function to sum tow sparse matrix (result: int **)
//    proposing to the exam: sparse matrix as result
int ** sum(SparseMatrix M1, SparseMatrix M2)
{
    if(valid_sum(M1, M2))
    {
        int n = M1.n;
        int m = M1.m;
        int ** res = new int*[n];
        for(int i = 0; i < n; i++)
        {
            res[i] = new int[m];
            for(int j = 0; j < m; j++)
                res[i][j] = value_at(M1.rows[i],j) + value_at(M2.rows[i],j);
        }
        return res;
    }
    else return NULL;
}

// --- TESTING ---

int main(int argc, char *argv[])
{
    /*
    SparseRow m1_sr1;
    m1_sr1.indices = new int[2]{0,3}; m1_sr1.values = new int[2]{2,1}; m1_sr1.m = 2;
    SparseRow m1_sr2;
    m1_sr2.indices = new int[1]{2}; m1_sr2.values = new int[1]{1}; m1_sr1.m = 1;
    SparseRow m1_sr3;
    m1_sr3.indices = new int[3]{0,3,4}; m1_sr3.values = new int[3]{3,1,2}; m1_sr1.m = 3;
    SparseRow m1_sr3;
    m1_sr3.indices = new int[3]{0,3,4}; m1_sr3.values = new int[3]{3,1,2}; m1_sr1.m = 3;
    */

    Parser p;
    pair<SparseMatrix, SparseMatrix> my_pair = p.parse("/home/reyesamaro-a/Documents/DepInfo/Algorithme et programmation/programs/sparse_matrix_sum/sms/test.txt");
    SparseMatrix M1 = my_pair.first;
    SparseMatrix M2 = my_pair.second;
    int ** sum_m = sum(M1, M2);

    // printing result
    for(int i = 0; i < M1.n; i++)
    {
        for(int j = 0; j < M1.m; j++)
        {
            cout << sum_m[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
