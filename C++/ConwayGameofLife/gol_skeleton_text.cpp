/*    CSC 16 Lab 7: Conway's Game of Life  (Text Version)

You are to implement the most important function of the game_of_life program.
This skeleton will print the GOL world as a 2D array, without using any 
graphical library.

IN A SEPARATE .cpp FILE write the function

unsigned int next_generation(bool* A, bool* B, int rows, int columns) {...}

That implements "one generation" of the game of life.  The current generation
is in array A and the second generation will be in array B.  The swapping of
these pointers between generations will be done outside of the function.  

The function should return the number of changes between A and B.  The program
will stop when there are no more changes (stable state reached).

The skeleton program is capable of loading a ".gol" file.

Say your file is called nextgen.cpp compile it with

  g++ gol_skeleton_text.cpp nextgen.cpp -o goltext
g++ circles.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o prog -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

and the run the program, in a large text window, with

  ./goltext "gosper.gol" 1

The last number controls the number of generations that will pass before
the array is displayed.  The default is 1, which is recommended when you're
debugging.

Type Control-C to quit the program.


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
#include<cstdio>
using namespace std;

// dimensions of GOL world:
int rows = 60;
int columns = 90;

// order directions n, ne, e, se, s, sw, w, nw
//const int8_t DX[] = {0,1,1,1,0,-1,-1,-1};
//const int8_t DY[] = {-1,-1,0,1,1,1,0,-1};
// place these in your own file

// This function will be written by students IN A SEPARATE FILE
unsigned int next_generation(bool* A, bool* B, int rows, int columns);
/////////


void render(bool* A, int gens) // as text grid
{
  cout << "\nAfter "<< gens << " generations:\n";
  for(int i=0;i<rows;i++) {
    for(int k=0;k<columns;k++) {
      if (A[i*columns+k]) cout << "*"; else cout << ".";
      if (columns<=80) cout << " ";
    }//for k
    cout << endl;
  }//for i
  cout << "Press Enter to Continue ... ";   getchar();
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
  int render_interval = 1; // display after every 1 generation
  if (argc>2) { render_interval = stoi(argv[2]); }

  //Abuf = load("/Users/sandroamaglobeli/CLionProjects/ConwayGameofLife/gosper.gol");
  //Bbuf = new bool[rows * columns];

    unsigned int changes = 1;
  bool currentA = true;
  unsigned int cx = 0; // counts generations
  while (changes>0)
    {   cx++;
	//int changes0 = changes;
	if (currentA) {
	  if ((cx%render_interval)==0) render((bool*)Abuf,cx);
	  changes = next_generation((bool*)Abuf,(bool*)Bbuf,rows,columns);
	}
	else {
	  if ((cx%render_interval)==0) render((bool*)Bbuf,cx);
	  changes = next_generation((bool*)Bbuf,(bool*)Abuf,rows,columns);
	}
	currentA = !currentA; //flip to B
    }//while changes
    cout << "\nStable state reached after " << cx << " generations\n";
    delete(Abuf);
    delete(Bbuf);
    return 0;
}//mai