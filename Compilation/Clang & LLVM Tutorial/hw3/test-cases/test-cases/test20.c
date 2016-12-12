int foo(int a) {
   int x = 10;                
   if (a < 10 && a > 0 ) {
      x = a;                 // range of x is [0..9] 
   } 
   return x;                 // range of x is [0..10]
}

/// Expected output
/// [0..10]
