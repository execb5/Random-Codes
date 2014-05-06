#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, const char *argv[])
{
	ifstream infile("lvl1");
	float a, b, c, d, e, f;
	while(infile >> a >> b >> c >> d >> e >> f)
	{
		cout << a << " + " << b << " + " << c << " + " << d << " + " << e << " + " << f << endl;
	}
	return 0;
}
