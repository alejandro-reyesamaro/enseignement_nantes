#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int rotations(string word, string rotation)
{
    if (word.length() != rotation.length())
        return -1;
    int size = word.length();
    string aux = "";
    for(int rot = 1; rot < size; rot++)
    {
        for(int i = 0; i < size; i++)
            aux += word[(i + rot) % size];
        if (aux == rotation)
            return rot;
        aux = "";
    }
    return -1;
}

void algo_1()
{
    string word, rotated;
    cout << "word: ";
    cin >> word;
    cout << "rotated: ";
    cin >> rotated;

    int rot_left = rotations(word, rotated);
    int rot_right = rotations(rotated, word);

    if(rot_left == -1 && rot_right == -1)
        cout << "impossible" << endl;
    else
        if(rot_left <= rot_right)   cout << rot_left << " gauche" << endl;
        else                        cout << rot_right << " droite" << endl;
}

void algo_2()
{
    string word, rotated;
    cout << "word: ";
    cin >> word;
    cout << "rotated: ";
    cin >> rotated;

    if (word.length() != rotated.length())
        cout << "impossible" << endl;
    else
    {
        int size = word.length();
        string aux = "";
        int rot_left = 0;
        int rot_right = 0;
        int rotations = -1;

        // analisis a la izquierda
        int r = 1;
        while(r < size && rotations == -1)
        {
            int i = 0;
            while(i < size)
            {
                aux += word[(i + r) % size];
                i++;
            }

            if (aux != rotated)
                rotations = -1;
            else
                rotations = r;
            aux = "";
            r ++;
        }
        rot_left = rotations;
        rotations = -1;

        // analisis a la derecha
        r = 1;
        while(r < size && rotations == -1)
        {
            int i = 0;
            while(i < size)
            {
                aux += rotated[(i + r) % size];
                i++;
            }

            if (aux != word)
                rotations = -1;
            else
                rotations = r;
            aux = "";
            r ++;
        }
        rot_right = rotations;

        if(rot_left == -1 && rot_right == -1)
            cout << "impossible" << endl;
        else
            if(rot_left <= rot_right)   cout << rot_left << " gauche" << endl;
            else                        cout << rot_right << " droite" << endl;
    }
}

int main(int argc, char *argv[])
{
    algo_2();
    return 0;
}
