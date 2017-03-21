#pragma once

struct SparseRow
{
    int * indices;
    int * values;
    int m;
};

struct SparseMatrix
{
    SparseRow * rows;
    int n;
    int m;
};
