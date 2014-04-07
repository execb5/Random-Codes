#include <iostream>
#include <ctime>

using namespace std;

int main(void)
{
	clock_t start;
	double ttime;
	start = clock();
	int crew = 10;
	bool ready = false;
	long mulberrys, remaining, newNumber, individualPortion, monkey;
	for (mulberrys = crew; ready == false; ++mulberrys)
	{
		newNumber = mulberrys;
		remaining = mulberrys % crew;
		if (remaining != 0)
		{
			for (int i = 0; i < crew; ++i)
			{
				monkey = newNumber % crew;
				if (monkey != remaining)
					break;
				individualPortion = newNumber / crew;
				newNumber = newNumber - monkey - individualPortion;
				if ((i == (crew - 1)) && ((newNumber % crew) == 0))
				{
					ready = true;
				}
			}
		}
	}
	ttime = (clock() - start); // (double) CLOCKS_PER_SEC;
	cout << "Mulberrys in the morning: " << newNumber << endl;
	cout << "Remaining: " << remaining << endl;
	cout << "Mulberrys: " << mulberrys - 1 << endl;
	cout << "Time: " << ttime << "ms" << endl;
	return 0;
}