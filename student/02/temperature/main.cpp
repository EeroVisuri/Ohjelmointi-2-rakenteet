#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    int temperature;
    cin >> temperature;
    float fahrenheit = temperature * 1.8 + 32;
    float celsius = (temperature - 32) / 1.8;

    cout << temperature << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit" <<endl;
    cout << temperature << " degrees Fahrenheit is " << celsius << " degrees Celsius" <<endl;

    return 0;
}
