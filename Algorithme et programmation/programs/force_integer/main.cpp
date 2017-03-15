#include <iostream>
#include <string>

using namespace std;

bool is_a_number(string str)
{
    char* p;
    strtol(str.c_str(), &p, 10);
    return !(*p);
}

void string_to_int(string str, int & val, bool & success)
{
    if (is_a_number(str))
    {
        string::size_type pos;
        val = std::stoi (str, &pos);
        success = true;
    } else success = false;
}

int main()
{
    bool is_number;
    string str_in;
    int value;
    do{
        cout << "Enter a number" << endl;
        cin >> str_in;
        string_to_int(str_in, value, is_number);
        if(is_number)
            cout << "Thanks!" << endl;
        else
            cout << "NaN. ";
    }
    while (!is_number);
}
