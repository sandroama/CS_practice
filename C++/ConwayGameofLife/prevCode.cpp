// Game of Life, first version, global allocation, renders square by square

// second version, with dynamically allocated arrays

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include <SFML/Graphics.hpp>
using namespace std;


// Web1
// #1 If the cell is alive, then it stays alive if it has either 2 or 3 live neighbors
// #2 If the cell is dead, then it springs to life only in the case that it has 3 live neighbors


// Web2
//1.Any live cell with fewer than two live neighbours dies, as if caused by under-population.
//
//2.Any live cell with two or three live neighbours lives on to the next generation.
//
//3.Any live cell with more than three live neighbours dies, as if by over-population.
//
//4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

// global constants
const int width = 900; // window width
const int height = 600; // window height
// dimensions of GOL world:

int rows = 60;
int columns = 90;

// order directions n, ne, e, se, s, sw, w, nw
const int8_t DX[] = {0,1,1,1,0,-1,-1,-1};
const int8_t DY[] = {-1,-1,0,1,1,1,0,-1};

// // testing the left
// if(x > 0 && game [x-1] [y] == 1) alive+=1;
// // testing the right
// if (X < GAME_WIDTH && game [x+1][y] == 1) alive+=1;
// // testing top
// if (y > 0 && game [x][y-1] == 1) alive+=1;
// // testing bottom
// if (y < GAME_HEIGHT && game [x][y+1] == 1) alive+=1;
// // testing top left
// if (y > 0 && x > 0 && game [x-1] [y -1] == 1) alive+=1;
// // testing top right
// if (y > 0 && x < GAME_WIDTH && game [x+1] [y-1] == 1) alive+=1;
// // testing bottom left
// if(y < GAME HEIGHT && × > 0 && game [x-1][y+1] == 1) alive +=1;
// // testing bottom right
// if(y < GAME_HEIGHT && x < GAME_WIDTH && game [×+11 y+11 == 1) alive+=1;
// // alive and fewer than 2 die
// if (game [x][y] == 1 && alive < 2) return false;
// // alive and 2 or 3 then live
// if (game [x][y] == 1 && (alive == 2 || alive == 3)) return true;


unsigned int nextgen(bool* A, bool* B)// returns number of changes
{
    unsigned int changes = 0; // counts changes
    for(int x=0;x<columns;x++)
        for(int y=0;y<rows;y++)
        {
            // current coordinates x,y as 1D memory address:
            int current = y*columns+x;
            int alive = 0;
            for(int n=0;n<8;n++) { // for each neighbor
                int nx = x+ DX[n];
                int ny = y+DY[n];
                if (nx>=0 && nx<columns && ny>=0 && ny<rows &&
                    A[ny*columns+nx]) alive++;
            }//for n

            B[current] = A[current]; // same by default
            if (A[current] && (alive<2 || alive>3)) { //die by under/overpopulation
                B[current] = 0;  changes++;
            }
            else if (!A[current] && alive==3) { // come to life with 3 live neighbors
                B[current] = 1; changes++;
            }
        } // for k, i
    return changes;
}// GOL next generation, swapping between Abuf and Bbuf

void render(bool* A, sf::RenderWindow& win)
{
    float w = width*1.0/columns;
    float h = height*1.0/rows;
    sf::RectangleShape sqr(sf::Vector2f(w,h));
    sf::Color color = sf::Color::Yellow;
    for (int y=0;y<rows;y++)
        for(int x=0;x<columns;x++) {
            int current = y*columns+x;
            if (A[current]) { // fillcolor
                sqr.setFillColor(color);
            }
            else {  // draw border only
                sqr.setFillColor(sf::Color::Transparent);
                sqr.setOutlineThickness(0.5);
                sqr.setOutlineColor(color);
            }
            // calculate position, upper left-hand corner
            sqr.setPosition(2+x*w, 2+y*h);
            win.draw(sqr);
        }// for y,x
}//render

// read from file
bool* load(string filename) // return A buf
{
    ifstream fd;
    int length;
    char *Fbuf;
    fd.open(filename,ios::in|ios::binary);
    fd.seekg(0,ios::end);
    length = (int)fd.tellg();
    fd.seekg(0,ios::beg);
    Fbuf = new char[4];  // heap allocation
    fd.read(Fbuf,4); // read all data
    //fd.close();
    // decode first 4 bytes as row, column
    rows = ((uint16_t)Fbuf[0])*256 + (uint16_t)Fbuf[1];
    columns = ((uint16_t)Fbuf[2])*256 + (uint16_t)Fbuf[3];
    // decode other bytes bit by bit
    int mblen = (rows*columns)/8 + 1;
    char* Mbuf = new char[mblen];
    memset(Mbuf,0,mblen*sizeof(char));
    //fd.seekg(4,ios::beg);  //no effect
    fd.read(Mbuf,mblen);
    int bytecount = (int)fd.gcount();
    fd.close();
    bool* matrix = new bool[rows * columns];
    int mi = rows * columns - 1;
    mblen = bytecount;
    int bi = mblen-1; // byte index
    int bitcx = 0;
    unsigned char onebyte = (unsigned char)(Mbuf[bi]);
    while (mi>=0) {
        matrix[mi] = onebyte%2;
        onebyte =onebyte/2;
        bitcx++;
        if (bitcx==8 && bi>0) {
            bitcx=0; bi--; onebyte = (unsigned char)Mbuf[bi];
        }
        mi--;
    }//while mi>=0  should fill top part with zeros
    return matrix;
}//load

int main(int argc, char* argv[])
{
    int framerate =1;
    sf::RenderWindow window(sf::VideoMode(width+4, height+4),"Conway's Game of Life");
    bool* Abuf;
    bool* Bbuf;
    if (argc>1) {
        string filen = string(argv[1]);
        Abuf = load(filen);
        Bbuf = new bool[rows * columns];
    } // filename given
    else {
        Abuf = new bool[rows * columns];
        Bbuf = new bool[rows * columns];
        memset(Abuf,0,rows*columns*sizeof(bool));
        for(int i=0;i<rows;i++) {Abuf[i*columns+i] = 1; Abuf[(i+1)*columns+i]=1;}
    } // no file given, generate default configuration
    if (argc>2) {  framerate = stoi(argv[2]);  } // sets animation speed
    window.setFramerateLimit(framerate); // sets base animation speed

    unsigned int changes = 1;
    bool currentA = true;
    unsigned int cx = 0;
    while (changes>0 && window.isOpen())
    {   cx++;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type==sf::Event::KeyPressed) {
                if (event.key.code==sf::Keyboard::Up) { // speed up, smaller
                }
                else if (event.key.code==sf::Keyboard::Down) { //slow down, bigger
                }
            }// keyboard event handler
        }// events handling loop

        window.clear(sf::Color::Black);  // don't move this line

        //int changes0 = changes;
        if (currentA) {
            render((bool*)Abuf,window);
            changes = nextgen((bool*)Abuf,(bool*)Bbuf);
        }
        else {
            render((bool*)Bbuf,window);
            changes = nextgen((bool*)Bbuf,(bool*)Abuf);
        }
        currentA = !currentA; //flip to B
        //if (changes==0 && changes0!=0)
        //  cout << "Stable state after " << cx << " generations\n";

        // your animation code goes here ...

        window.display();                // don't move this line
    }//while changes
    cout << "Stable state reached after " << cx << " generations\n";
    return 0;
}//main
/*
csc16@liangVM:~/sfml$ g++ gol2.cpp -o gol2 -lsfml-graphics -lsfml-window -lsfml-system
csc16@liangVM:~/sfml$ ./gol2
https://www.sfml-dev.org/index.php
*/
