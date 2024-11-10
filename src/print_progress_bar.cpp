#include <iostream>

using namespace std;

void print_progress_bar(float percent)
{
    cout << "\r|";
    for (int i = 0; i < 100; i++){
        if (i < percent * 100)
            cout << "=";
        else
            cout << " ";
    }
    cout << "| " << percent*100 << "%";
    cout.flush();
}
