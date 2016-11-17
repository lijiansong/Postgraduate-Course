/* Variables */
var x1 >= 0;
var x2 >= 0;
var x3 >= 0;

/* Object function */
maximize z: 3*x1 + x2 + 2*x3;

/* Constrains */
s.t. con1: x1 + x2 + 3*x3 <= 30;
s.t. con2: 2*x1 + 2*x2 + 5*x3  <= 24;
s.t. con3: 4*x1 + 1*x2 + 2*x3  <= 36;

end;

