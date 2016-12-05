int foo(int flag) {
   int x = 10; 
   int y = 10;
   int z;

   if (flag) {
      x = 1;
   } 

   if (flag) {
     y = 2;
   }


   if (flag) {
      z = x;
   } else {
      z = y;
   }

   return x + y;
}
