#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    string str = "HELLO, WORLD!";

    // Convert the string to lowercase
    transform(str.begin(), str.end(), str.begin(),[](unsigned char c)
    {return tolower(c); });

    cout<<str<<endl;

    return 0;
}
