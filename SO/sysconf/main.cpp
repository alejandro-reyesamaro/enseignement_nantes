#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    long r = sysconf(_SC_NPROCESSORS_CONF);
    long th = sysconf(_SC_THREADS);
    cout << r << ", " << th << endl;

    return 0;
}
