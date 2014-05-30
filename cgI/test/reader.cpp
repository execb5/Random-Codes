//reader.cpp

#include <GL/freeglut.h>
#include <fstream>

#include "reader.h"

using namespace std;

Reader::Reader()
{
    for(int i = 0; i < 256; i++ ) {
        vertex[i].x = 0;
        vertex[i].y = 0;
        vertex[i].z = 0;
    }
}

Reader::~Reader()
{

}

void Reader::load(char* filename)
{
    ifstream file;
    file.open(filename);

    string str;

    while(!file.eof()) //while we are still in the file
    {
        getline(file,str); //move one line down
        if(str[0] == 'v') break; //if we have a vertex line, stop
    }

    int v = 0;

    while(str[0] == 'v') {

        int i = 0;

        while(true)
        {
            while(str[i] == ' ' )
            {
                i++; //move a space over
            }
            i++;
            i++;
            int j = i, k = i;
            while(str[i] != ' ') {  
                i++;
                k = i;
            }
            vertex[v].x = atof(str.substr(j, k-j).c_str());

            //moving on to the y coord

            while(str[i] == ' ' ) {
                i++;
            }

            int q = i, w = i;
            while(str[i] != ' ' ) {
                i++;
                w = i;
            }
            vertex[v].y = atof(str.substr(q, w-q).c_str());

            while(str[i] == ' ' ) {
                i++;
            }

            int a = i, s = i;
            while(str[i] != ' ' ) {
                i++;
                s = i;
            }
            vertex[v].z = atof(str.substr(a, s-a).c_str());

            break;
        }
        v++; 
        getline(file, str);  
    }
}

void Reader::draw(char *filename)
{
    ifstream file;
    file.open(filename);

    string str;

    while(true)
    {
        getline(file, str);
        if(str[0] == 'f' ) {
            break;
        }
    }

    int i = 0;

    while(str[0] == 'f')
    {

        while(str[i] == 'f') i++;
        while(str[i] == ' ') i++;
        int j = i, k = i;

        while(str[i] != ' ') {  
            i++;
            k = i;
        }

        int one = atof(str.substr(j, k - j).c_str());

        i +=1;

        j = i;
        k = i;

        while(str[i] != ' ') { 
            i++;
            k = i;
        }

        int two = atof(str.substr(j, k - j).c_str());

        i+=1;

        j = i;
        k = i;

        while(str[i] != ' ') {  
            i++;
            k = i;
        }

        int three = atof(str.substr(j, k - j).c_str());

        i+=1;

        j = i;
        k = i;

        while(str[i] != ' ') {  
            i++;
            k = i;
        }

        int four = atof(str.substr(j, k - j).c_str());

        glBegin(GL_POLYGON);
		glVertex3d(vertex[one - 1].x, vertex[one - 1].y, vertex[one - 1].z);
		glVertex3d(vertex[two - 1].x, vertex[two - 1].y, vertex[two - 1].z);
		glVertex3d(vertex[three - 1].x, vertex[three - 1].y, vertex[three - 1].z);
		glVertex3d(vertex[four - 1].x, vertex[four - 1].y, vertex[four - 1].z);
        glEnd();

        getline(file, str);
        i = 0;
    }

}
