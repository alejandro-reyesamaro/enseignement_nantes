#include <iostream>

/* C.C. 3 */

struct Tableau
{
    int T[7] = {1, 3, 4, 1, 1, 5, 1};
    int N = 7;
};

int occur(Tableau T, int e, int pos_init)
{
    if(pos_init == T.N) return 0;
    else
    {
        if(T.T[pos_init] == e)
            return 1 + occur(T, e, pos_init + 1);
        else
            return occur(T, e, pos_init + 1);
    }
}

int main(int argc, char *argv[])
{
    Tableau T;
    int occ = occur(T,1,0);
    std::cout << occ << std::endl;
    return 0;
}
