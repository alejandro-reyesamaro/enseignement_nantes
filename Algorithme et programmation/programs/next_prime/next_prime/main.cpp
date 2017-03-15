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
    int base = n / 6;
    int rest = n % 6;
    if (rest == 0 && is_prime(n+1))
        return n+1;
    while(true)
    {
        base += 1;
        if(is_prime(6*base-1)) return 6*base-1;
        if(is_prime(6*base+1)) return 6*base+1;
    }
}

int main()
{
    int n;
    cout << "Enter a number" << endl;
    cin >> n;
    cout << "The next prime is: " << next_prime(n) << endl;
}
