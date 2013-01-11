#include <cstdlib>
#include <iostream>
#include "VectorUtils.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    wxPoint p1=wxPoint(1,1);
    wxPoint p2=wxPoint(-5,1);
    cout << VectorUtils::ScalarProduct(p1,p2) << "  Press the enter key to continue ...  "<< VectorUtils::AngleBetweenVectors(p1,p2);
    cin.get();
    return EXIT_SUCCESS;
}
