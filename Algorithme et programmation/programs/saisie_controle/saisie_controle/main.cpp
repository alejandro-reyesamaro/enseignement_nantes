#include <iostream>

using namespace std;

int ask_positive_number()
{
    int number;
    do
    {
        cout << "Enter an integer positive number" << endl;
        cin >> number;
    }while(number < 0);
    return number;
}

int ask_number_into(int a, int b)
{
    int number;
    do
    {
        cout << "Enter an integer number between " << a << " and " << b << endl;
        cin >> number;
    }while(number < a || number > b);
    return number;
}

int main(int argc, char *argv[])
{
    int number;
    //number = ask_positive_number();
    number = ask_number_into(-1, 5);
    cout << "OK" << endl;

    return 0;
}
