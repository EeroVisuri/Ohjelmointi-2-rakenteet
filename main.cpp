#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    int temperature;
    cin >> temperature;
    float fahrenheit = temperature * 1.8 + 32;
    float celcius = (temperature - 32) / 1.8;

    cout << temperature << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit" <<endl;
    cout << temperature << " degrees Fahrenheit is " << celcius << " degrees Celcius" <<endl;

    return 0;
}
