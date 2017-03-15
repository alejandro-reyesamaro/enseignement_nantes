/*
#include <iostream>
#include <string>

using namespace std;

string top(int size)
{
    string output = "";
    for(int i = 0; i < size; i++)
        output += " ";
    output += "*";
    return output;
}

string roof_tiles(int in, int out)
{
    string output = "";
    for(int i = 0; i < out; i++)
        output += " ";
    output += "/";
    for(int i = 0; i < in; i++)
        output += " ";
    output += "\\";
    return output;
}

string line(int size, char border, char inner)
{
    string output = "";
    output += border;
    for (int i = 0; i < size; i++)
        output += inner;
    output += border;
    return output;
}

string horizontal(int size)
{    
    //string output = "+";
    //for (int i = 0; i < size; i++)
    //    output += "-";
    //output = "+";
    //return output;
    return line(size, '+', '-');
}

string vertical(int size)
{
    //string output = "|";
    //for (int i = 0; i < size; i++)
    //    output += " ";
    //output = "|";
    //return output;
    return line(size, '|', ' ');
}

void print_ceiling(int tiles)
{
    string output = "";
    output = top(tiles);
    cout << output << endl;
    int in = 1;
    int out = tiles - 1;
    while (out >= 0)
    {
        output = roof_tiles(in, out);
        out --;
        in += 2;
        cout << output << endl;
    }
}

void print_walls(int stages)
{
    int size = 2 * stages - 1;
    cout << horizontal(size) << endl;
    for(int i = 0; i < size; i++)
        cout << vertical(size) << endl;
    cout << horizontal(size) << endl;
}

int main(int argc, char *argv[])
{
    int size;
    cout << "Enter the size of the house" << endl;
    cin >> size;
    print_ceiling(size);
    print_walls(size);
    return 0;
}

*/
