//Exercice 2.4 (Géométrie du plan)

#include <math.h>
#include <string>
#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;
};

void print_point(Point p)
{
    cout << "(" << p.x << ";" << p.y << ")" << endl;
}

Point enter_point()
{
    Point p;
    cout << "Enter a point, separated by [ENTER]" << endl;
    string::size_type sz;
    string x_str, y_str;
    cin >> x_str;
    cin >> y_str;
    p.x = std::stoi (x_str,&sz);
    p.y = std::stoi (y_str,&sz);

    //return {x,y};
    return p;
}

int distance(Point & p1, Point & p2)
{
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

void print_options()
{
    cout << "0- Quit" << endl;
    cout << "1- Enter another point" << endl;
    cout << "Option: " << endl;
}

int main()
{
    Point p_origin = enter_point();
    Point p1 = p_origin;
    Point p2 = p_origin;
    int perimeter = 0;
    int option = 0;
    do
    {
        print_options();
        cin >> option;

        switch(option)
        {
            case 0:
                p2 = p_origin;
                break;
            case 1:
                p2 = enter_point();
                break;
            default:
                cout << "-- I don't think so :/" << endl;
        }
        perimeter += distance(p1, p2);
        p1 = p2;
    }while(option != 0);
    cout << "The perimeter is: " << perimeter << endl;
}
