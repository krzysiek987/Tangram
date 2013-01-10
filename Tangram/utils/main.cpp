#include <cstdlib>
#include <iostream>
#include "VectorUtils.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    wxPoint p1=wxPoint(1,1);
    
    cout << VectorUtils::Norm(p1) << "  Press the enter key to continue ...  "<< sqrt(1*1+1*1);
    cin.get();
    return EXIT_SUCCESS;
}
