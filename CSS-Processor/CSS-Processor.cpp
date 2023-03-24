#include <iostream>
#include "String.h"

using std::cout;
using string = String;

int main()
{
    char c;
    char* buffer = new char[100];
    int counter = 0;
    
    string test;
    while (c = getchar())
    {
        if (c == '\n' || c == ' ')
        {
            buffer[counter] = '\0';
            counter++;
            test = buffer;
            counter = 0;
            delete[] buffer;
            buffer = new char[100];
            cout << test;
            continue;
        }

        buffer[counter] = c;
        counter++;
    }

    delete[] buffer;
    return 0;
}