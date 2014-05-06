#include<vector>

typedef struct
{
	float x;
	float y;
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
		void loadLevel(string name);
		bool checkCollision(Point p);

	private:
		vector<Triangle> triangles;
}
