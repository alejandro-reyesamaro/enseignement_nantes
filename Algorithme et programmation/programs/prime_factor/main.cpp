#include <iostream>
#include <math.h>

using namespace std;

bool is_prime(int n)
{
    for(int i = 2; i <= sqrt(n); i++)
        if(n % i == 0) return false;
    return true;
}

int next_prime(int n)
{
    do
    {
        n++;
    }while(!is_prime(n));
    return n;
}

int main()
{
    int n;
    cout << "Enter a number" << endl;
    cin >> n;

    int q = n;
    int c = 0;
    int factor = 2;

    cout << n << " = ";
    while(q > 1)
    {
        while(n % factor == 0)
        {
            q = n / factor;
            c ++;
            n = q;
        }
        cout << factor << " ^ " << c << " * ";
        c = 0;
        if(n > 1)
        {
            do{
                factor = next_prime(factor);
            }while(n % factor != 0);
        }
    }

    cout << "1" << endl;
}
