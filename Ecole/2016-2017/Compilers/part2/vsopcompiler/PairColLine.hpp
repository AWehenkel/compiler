#ifndef paircolline_hpp
#define paircolline_hpp

class PairColLine {
private :
  int col;
  int line;
public :
  PairColLine(int _col = 0, int _line = 0) : col(_col), line(_line) {};
  int getCol() {return col;}
  int getLine() {return line;}
};

#endif // paircolline_hpp
