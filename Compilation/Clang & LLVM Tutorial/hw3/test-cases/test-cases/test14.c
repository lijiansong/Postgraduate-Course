int foo(int a, int b) {
   int x = 0;
   int y = 100;   // range of y is [100..100]
   int z = 100;   // range of z is [-10..100]
   if (a) {
      x = 0;
   } else {
      x = 10;
   }
   // range of x is [0..10] 
   if (b) {
      y = x + 1;  //range of y is [1..11] 
   } else {
      y = x -1;  // range of y is [-1..9]
      z = y * x; //range of z is [-10..90]
   }
   // range of z is [-10.. 100] 
   y = z * z;    // range of y is [0..10000]
   return z;    
}

/// Expected output
/// [0..10000]
