#include <iostream>
#include <string>
#include <cmath>

/* C.C. 1 */

using namespace std;

int rotations(string word, string rotation)
{
    if (word.length() != rotation.length())
        return -1;
    int size = word.length();
    string aux = "";
    int rot = 0;
    for(rot = 1; rot < size; rot++)
    {
        for(int i = 0; i < size; i++)
            aux += word[(i + rot) % size];
        if (aux == rotation)
            return rot;
        aux = "";
    }
    return -1;
}

int main(int argc, char *argv[])
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
    {
        if(rot_left <= rot_right)
            cout << rot_left << " gauche" << endl;
        else
            cout << rot_right << " droite" << endl;
    }
    return 0;
}
