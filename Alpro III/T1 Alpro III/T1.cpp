#include <iostream>
#include <ctime>

using namespace std;

int main(void)
{
	for (int monkey = 1; monkey < 7; ++monkey)
	{
		clock_t start;
		double ttime;
		start = clock();
		int crew = 9;
		bool ready;
		long unsigned mulberrys, morningMulberry, individualPortion;
		for (int i = 1; ; ++i)
		{
			mulberrys = i * crew;
			morningMulberry = mulberrys;
			ready = true;
			for (int j = 0; j < crew; ++j)
			{
				if (mulberrys % (crew - 1) != 0)
				{
					ready = false;
					break;
				}
				individualPortion = mulberrys / (crew - 1);
				mulberrys += individualPortion + monkey;
			}
			if (ready)
			{
				break;
			}
		}
		ttime = (clock() - start) / (double) CLOCKS_PER_SEC;
		cout << "Mulberrys in the morning: " << morningMulberry << endl;
		cout << "Mulberrys: " << mulberrys << endl;
		cout << "Time: " << ttime << "s" << endl;
		for (int i = 1; i <= crew; ++i)
		{
			cout << "T" << i << ": " << mulberrys/crew + morningMulberry/crew<< endl;
			mulberrys = mulberrys - mulberrys/crew - monkey;
		}
		cout << endl;
	}
	return 0;
}