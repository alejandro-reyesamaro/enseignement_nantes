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

void move_point(Point & p, int shift_x, int shift_y)
{
    p.x += shift_x;
    p.y += shift_y;
}

void perform_movement(Point & p)
{
    int shift_x, shift_y;
    cout << "Enter shifts separated by [ENTER]" << endl;
    cin >> shift_x;
    cin >> shift_y;
    move_point(p, shift_x, shift_y);
    cout << "The resulting point is: ";
    print_point(p);
}

void rotate_point(Point & p, float angle)
{
    p.x = p.x * cos(angle) - p.y * sin(angle);
    p.y = p.x * cos(angle) + p.y * sin(angle);
}

void perform_rotation(Point & p)
{
    float angle;
    cout << "Enter the angle and then [ENTER]" << endl;
    cin >> angle;
    rotate_point(p, angle);
    cout << "The resulting point is: ";
    print_point(p);
}

void rotate_point(Point & p, Point & center, int angle)
{
    p.x -= center.x;
    p.y -= center.y;
    rotate_point(p, angle);
    p.x += center.x;
    p.y += center.y;
}

void perform_rotation_around_origin(Point & p)
{
    float angle;
    cout << "Enter the angle and then [ENTER]" << endl;
    cin >> angle;
    Point center = enter_point();
    rotate_point(p, center, angle);
    cout << "The resulting point is: ";
    print_point(p);
}

void print_options()
{
    cout << "0- Quit" << endl;
    cout << "1- Move a point" << endl;
    cout << "2- Rotate point around origin" << endl;
    cout << "3- Rotate point around other point" << endl;
    cout << "Option: " << endl;
}

int main()
{
    Point p = enter_point();
    int option = 0;
    do
    {
        print_options();
        cin >> option;
        switch(option)
        {
            case 0:
                cout << "Good bye :)" << endl;
                break;
            case 1:
                perform_movement(p);
                break;
            case 2:
                perform_rotation(p);
                break;
            case 3:
                perform_rotation_around_origin(p);
                break;
            default:
                cout << "-- I don't think so :/" << endl;
        }
    }while(option != 0);
}
