// Solve Random 15 Puzzles : Nigel Galloway - October 18th., 2017
class fifteenSolver{
  const int Nr[16]{3,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3}, Nc[16]{3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2};
  int n{},_n{}, N0[100]{},N3[100]{},N4[100]{};
  unsigned long N2[100]{};
  const bool fY(){
    if (N2[n]==0x123456789abcdef0) {std::cout<<"Solution found in "<<n<<" moves :"; for (int g{1};g<=n;++g) std::cout<<(char)N3[g]; std::cout<<std::endl; return true;};
    if (N4[n]<=_n) return fN();
    return false;
  }
  const bool                     fN(){
    if (N3[n]!='u' && N0[n]/4<3){fI(); ++n; if (fY()) return true; --n;}
    if (N3[n]!='d' && N0[n]/4>0){fG(); ++n; if (fY()) return true; --n;}
    if (N3[n]!='l' && N0[n]%4<3){fE(); ++n; if (fY()) return true; --n;}
    if (N3[n]!='r' && N0[n]%4>0){fL(); ++n; if (fY()) return true; --n;}
    return false;
  }
  void fI(){
    const int           g = (11-N0[n])*4;
    const unsigned long a = N2[n]&((unsigned long)15<<g);
    N0[n+1]=N0[n]+4; N2[n+1]=N2[n]-a+(a<<16); N3[n+1]='d'; N4[n+1]=N4[n]+(Nr[a>>g]<=N0[n]/4?0:1);
  } 
  void fG(){
    const int           g = (19-N0[n])*4;
    const unsigned long a = N2[n]&((unsigned long)15<<g);
    N0[n+1]=N0[n]-4; N2[n+1]=N2[n]-a+(a>>16); N3[n+1]='u'; N4[n+1]=N4[n]+(Nr[a>>g]>=N0[n]/4?0:1);
  } 
  void fE(){
    const int           g = (14-N0[n])*4;
    const unsigned long a = N2[n]&((unsigned long)15<<g);
    N0[n+1]=N0[n]+1; N2[n+1]=N2[n]-a+(a<<4); N3[n+1]='r'; N4[n+1]=N4[n]+(Nc[a>>g]<=N0[n]%4?0:1);
  } 
  void fL(){
    const int           g = (16-N0[n])*4;
    const unsigned long a = N2[n]&((unsigned long)15<<g);
    N0[n+1]=N0[n]-1; N2[n+1]=N2[n]-a+(a>>4); N3[n+1]='l'; N4[n+1]=N4[n]+(Nc[a>>g]>=N0[n]%4?0:1);
  }
public:
  fifteenSolver(int n, unsigned long g){N0[0]=n; N2[0]=g;}
  void Solve(){for(;not fY();++_n);}
};
 

 
int main (){
  fifteenSolver start(8,0xfe169b4c0a73d852);
  start.Solve();
}


/*

     0 12  9 13
    15 11 10 14
     3  7  2  5
     4  8  6  1
     
    Solution found in 52 moves: rrruld d luu u ldrurddd ru l l  ulurrrd d ld       luurddlulurruldr d r   d
                                rrruld   luu   ldrurddd    l  u ulurrrd   ld druld luurddlulurruldr   r d d
     
    https://rosettacode.org/wiki/15_puzzle_solver#C.2B.2B
    
*/

 
