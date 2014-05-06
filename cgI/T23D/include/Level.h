#include<vector>
#include<fstream>

using namespace std;

typedef struct
{
	float x;
	float y;
	float z;
} Point;

typedef struct
{
	Point p1;
	Point p2;
	Point p3;
} Triangle;

class Level
{
	public:
		Level(char* name);
		~Level();
		bool checkCollision(Point p);

	private:
		vector<Triangle> triangles;
};
