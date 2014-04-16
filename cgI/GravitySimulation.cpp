#include <GL/glut.h>
#include <vector>
#include <cmath>
 
struct Particle {
        float x;
        float y;
        float r;
        float vx;
        float vy;
        float m;
        float color[3];
};
 
struct Line {
        float x1;
        float y1;
        float x2;
        float y2;
} line;
 
void timer(int = 0);
void display();
void mouse(int, int, int, int);
void mouseMotion(int, int);
void addParticle(float, float, bool = true, float = 0, float = 0);
void removeParticles();
void keyboard(unsigned char, int, int);
 
int Mx, My, WIN;
bool PRESSED_LEFT = false, PRESSED_RIGHT = false,
     PRESSED_MIDDLE = false, SPEED_PARTICLES = false;
 
std::vector<Particle> particles;
 
int main(int argc, char **argv)
{
        Particle p;
        //initial centered Huge mass particle
        p.x = 0;
        p.y = 0;
        p.vx = p.vy = 0;
        p.m = 10000;
        p.r = 10;
        p.color[0] = 1;
        p.color[1] = 1;
        p.color[2] = 0;
        particles.push_back(p);
 
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(50, 50);
        WIN = glutCreateWindow("Gravity");
 
        glClearColor(0, 0, 0, 1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-250.0, 250.0, 250.0, -250.0, 0, 1);
       
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMotion);
        glutKeyboardFunc(keyboard);
        timer();
       
        glutMainLoop();
        return 0;
}
 
void timer(int)
{
        display();
        if(PRESSED_LEFT && !SPEED_PARTICLES)
        {
                addParticle(10, 3); //add tiny particle
                PRESSED_LEFT = false;
        }
 
        if(PRESSED_RIGHT)
        {
                addParticle(10000, 10, 0); //add huge particle
                PRESSED_RIGHT = false;
        }
 
        if(PRESSED_MIDDLE)
                removeParticles(); //remove all particles
 
        for(int i = 0; i < particles.size(); i++)
        {
                Particle &p = particles[i];
                bool not_fall = true;
                for(int j = 0; j < particles.size(); j++)
                {
                        if(j == i || p.m >= 10000) // we consider the 10000 as infinit (big mass) so this particles won't move
                                continue;
 
                        const Particle &p1 = particles[j];
 
                        float d = sqrt((p1.x - p.x)*(p1.x - p.x) + (p1.y - p.y)*(p1.y - p.y));
 
                        if(d > p1.r)
                        {
                                p.vx += 0.03 * p1.m / (d*d) * (p1.x - p.x)/d; //f = ma => a = f/m
                                p.vy += 0.03 * p1.m / (d*d) * (p1.y - p.y)/d;
                        }
                        else
                                not_fall = false;
                }
 
                if(not_fall)   
                {
                        p.x += p.vx;
                        p.y += p.vy;
                }
                else
                        particles.erase(particles.begin()+i);
        }
 
        glutTimerFunc(1, timer, 0);
}
 
void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
 
        //draw the drag line
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
                glVertex2f(line.x1, line.y1);
                glVertex2f(line.x2, line.y2);
        glEnd();
 
        //draw particles
        for(int i = 0; i < particles.size(); i++)
        {
                Particle &p = particles[i];
                glColor3f(p.color[0], p.color[1], p.color[2]);
                glBegin(GL_POLYGON);
                for(float a = 0; a < 2*M_PI; a+=0.2)
                        glVertex2f(p.r*cos(a) + p.x, p.r*sin(a) + p.y);
                glEnd();       
        }
 
        glFlush();
        glutSwapBuffers();
}
 
void mouse(int button, int state, int x, int y)
{
        //set the coordinates
        Mx = x - 250;
        My = y - 250;
 
        //add speed particles by line draging
        if(SPEED_PARTICLES)
        {
                if(line.x2 != 0 && line.y2 != 0 && state == GLUT_UP && PRESSED_LEFT)
                        addParticle(100, 5, 1, line.x1 - line.x2, line.y1 - line.y2); //add a speed particle
                else
                {
                        line.x1 = line.x2 = Mx;
                        line.y1 = line.y2 = My;
                }
        }
 
        //check which button is pressed
        if(button == GLUT_LEFT_BUTTON)
                PRESSED_LEFT = state == GLUT_DOWN;
        else if(button == GLUT_RIGHT_BUTTON)
                PRESSED_RIGHT = state == GLUT_DOWN;
        else if(button == GLUT_MIDDLE_BUTTON)
                PRESSED_MIDDLE = state == GLUT_DOWN;
}
 
void mouseMotion(int x, int y)
{
        Mx = x - 250;
        My = y - 250;  
 
        //end of line with draging
        if(SPEED_PARTICLES && PRESSED_LEFT)
        {
                line.x2 = Mx;
                line.y2 = My;
        }
}
 
void addParticle(float m, float r, bool randColor, float vx, float vy)
{
        Particle p;
        p.x = Mx;
        p.y = My;
        p.vx = vx / 30; // /30 in case it is a speed particle,
        p.vy = vy / 30; // slow down the speed a little
        p.m = m;
        p.r = r;
        if(randColor)
        {
                p.color[0] = rand()%200 / 200.0;
                p.color[1] = rand()%200 / 200.0;
                p.color[2] = rand()%200 / 200.0;
        }
        else // if is huge particle make it yellow
        {
                p.color[0] = 1;
                p.color[1] = 1;
                p.color[2] = 0;
        }
        particles.push_back(p);
 
        if(line.x1 != 0)
                line.x1 = line.x2 = line.y1 = line.y2 = 0;     
}
 
void removeParticles()
{
        for(int i = 0; i < particles.size(); i++)
                particles.pop_back();
}
 
void keyboard(unsigned char key, int x, int y)
{
        switch(key)
        {
                case 's':
                        SPEED_PARTICLES = !SPEED_PARTICLES;
                        break; 
                case 27:
                        removeParticles();
                        glutDestroyWindow(WIN);
                        exit(0);
                        break;
        }
}

