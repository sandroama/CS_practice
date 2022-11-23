/*    CSC 16 Lab 7: Conway's Game of Life  (Graphical Version)

You are to implement the most important function of the game_of_life program.
This skeleton requires the SFML multimedia library.  If you don't have that
installed already, DO NOT WASTE TIME INSTALLING IT. Write the text-based program
first and come back to it later.

IN A SEPARATE .cpp FILE write the function

unsigned int next_generation(bool* A, bool* B, int rows, int columns) {...}

That implements "one generation" of the game of life.  The current generation
is in array A and the second generation will be in array B.  The swapping of
these pointers between generations will be done outside of the function.

The function should return the number of changes between A and B.  The program
will stop when there are no more changes (stable state reached).

The skeleton program is capable of loading a ".gol" file.

Say your file is called nextgen.cpp compile it with

  g++ gol_skeleton_sfml.cpp nextgen.cpp -o golsfml -lsfml-graphics -lsfml-window -lsfml-system


 g++ gol_skeleton_sfml.cpp nextgen.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o prog -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

g++ gol_skeleton_text.cpp nextgen.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o prog -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system


and the run the program, in a large text window, with

  ./golsfml "gosper.gol" 15

The number at the end controls the frame rate: the default is 1, which is
recommended when you're debugging.


RULES OF THE GAME (REPHRASED):

Each cell is represented by a boolean in a 2D array (true=alive).  Eeach
cell has 8 immediate neighbors to the north, northeast, e, se, s, sw, w, nw.
Try to use the DX and DY arrays in your programs.

* Any dead cell becomes alive if it has exactly 3 live neighbors,
  otherwise, it stays dead

* Any live cell becomes dead if it has less than 2 or greater than
  3 live neighbors, otherwise, it stays alive.

Consult https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
for more information and equivalent descriptions of the rules.


Part II.

Rewrite the skeleton program so that, if no configuration file is
given, generate a random world with live and dead cells.  Consult Lab
4 for how to generate random numbers.  But basically:
#include<cstdlib>
#include<ctime>
srand(time(nullptr));
bool alive = rand()%2;

Figure out how to bias the random number generation so that intially
there are more dead cells than life ones (2/3 dead, 1/3 alive, etc.).
The average ratio should be modifiable.
*/

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdlib>
#include <SFML/Graphics.hpp>
using namespace std;

// global constants  (graphical window size, NOT the GOL 2D array size)
const int width = 900; // window width
const int height = 700; // window height

// default number of rows/columns in GOL 2D array, mutable
int rows = 60;
int columns = 90;

// x,y offset of 8 neighbors in order north, northeast, e, se, s, sw, w, nw:
// place these in your own file
//const int8_t DX[] = {0,1,1,1,0,-1,-1,-1};
//const int8_t DY[] = {-1,-1,0,1,1,1,0,-1};

// This function will be written by students IN A SEPARATE FILE
unsigned int next_generation(bool* A, bool* B, int rows, int columns);
/////////

void render(bool* A, sf::RenderWindow& win)
{
  float w = width*1.0/columns;
  float h = height*1.0/rows;
  sf::RectangleShape sqr(sf::Vector2f(w,h));
  sf::CircleShape circ(h/2.0-0.25);
  if ((w/h) > 1.5) circ.setScale(w/h,1.0); // make oval shape if necessary
  sf::Color color = sf::Color::Yellow;
  for (int y=0;y<rows;y++)
    for(int x=0;x<columns;x++) {
      int current = y*columns+x;

      sqr.setFillColor(sf::Color::Transparent);
      sqr.setOutlineThickness(0.5);
      sqr.setOutlineColor(sf::Color(0,200,0)); // green border
      sqr.setPosition(2+x*w, 2+y*h);
      win.draw(sqr);
      if (A[current]) { // current cell is alive
	circ.setFillColor(color);
        circ.setPosition(2+x*w, 2+y*h);
	win.draw(circ);
      }
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
  rows = 60;  columns = 90; //default values
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
	  changes = next_generation((bool*)Abuf,(bool*)Bbuf,rows,columns);
	}
	else {
	  render((bool*)Bbuf,window);
	  changes = next_generation((bool*)Bbuf,(bool*)Abuf,rows,columns);
	}
	currentA = !currentA; //flip to B
	//if (changes==0 && changes0!=0)
	//  cout << "Stable state after " << cx << " generations\n";

	// your animation code goes here ...

        window.display();                // don't move this line

	// Optional:
	//cout << "Press Enter to Continue ...";  getchar();

    }//while changes
    if (changes==0)
      cout << "Stable state reached after " << cx << " generations\n";
    delete(Abuf);
    delete(Bbuf);
    return 0;
}//main
