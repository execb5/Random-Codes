#include<Level.h>

Level::Level(char* name)
{
	ifstream infile(name);
	float a, b, c, d, e, f, g, h, j;
	while(infile >> a >> b >> c >> d >> e >> f >> g >> h >> j)
	{
		Triangle t;
		t.p1.x = a;
		t.p1.y = b;
		t.p1.z = c;
		t.p2.x = d;
		t.p2.y = e;
		t.p2.z = f;
		t.p3.x = g;
		t.p3.y = h;
		t.p3.z = j;
		triangles.push_back(t);
	}
}

Level::~Level()
{

}

bool Level::checkCollision(Point p)
{
	return false;
}
