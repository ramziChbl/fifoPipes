typedef struct 
{ char o;
  int g;
  int d;
  long int r;
} operation;

typedef operation tabl[10];

void savop(char op, int opg, int opd, long int res);

void lireop(tabl* x);


