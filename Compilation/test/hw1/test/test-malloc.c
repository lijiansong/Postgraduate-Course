extern int GET();
extern int MALLOC();
extern void FREE(int);
extern void PRINT(int);

int main() {
   int a;
   int b;
   int *ptr;
   int **dptr;

   ptr = MALLOC(sizeof(int));
   dptr = MALLOC(sizeof(int *));
   *dptr = ptr;
   a = GET();
   *ptr = a;
   b = **dptr;
   PRINT(b);
   FREE(ptr);
   FREE(dptr);
}
