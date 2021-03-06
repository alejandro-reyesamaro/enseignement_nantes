#include <iostream>
#include <cmath>
#include <string>

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
    cin >> p.x;
    cin >> p.y;
    return p;
}

bool equals(Point p1, Point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

float compute_distance(Point p1, Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

int main(int argc, char *argv[])
{
    cout << "Enter a polygon (first point equals to the last one)" << endl;
    Point p0 = enter_point();

    Point p1 = p0;
    Point p2;
    float distance = 0;
    do
    {
        p2 = enter_point();
        distance += compute_distance(p1, p2);
        p1 = p2;
    }while(!equals(p2,p0));

    cout << "Distance = " << distance << endl;
    return 0;
}
