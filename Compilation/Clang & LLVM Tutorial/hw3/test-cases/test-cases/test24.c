int foo(int a, int b) {
   int x = 0;
   int y = 100;   // range of y is [100..100]
   int z = 100;   // range of z is [100..100]
   if (a) {
      x = 0;
   } else {
      x = 10;
   }
   // range of x is [0..10] 
   y = x + 1;  //range of y is [1..11] 
   z = x * y;  // range of z is [0..110] 
   y = 5*x;    // range of y is [0 .. 50] 

   if (z > y) {
      //range of z is [1..110]
      z = z - 80;   //range of z is [-79..30]
   }
   // range of z is [0..50]if the branch is not taken
   return z;       //range of z is[-79..50]
}

/// Expected output
/// [-79..50]
