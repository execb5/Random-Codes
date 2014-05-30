//reader.h

#ifndef READER_H
#define READER_H

#define MAX_VERT 100000

struct Vertex {

    float x;
    float y;
    float z;

};


class Reader {
    private:
        Vertex vertex[256];

    public:
        Reader();
        ~Reader();

        void load(char* filename);
        void draw(char* filename);


};

#endif
