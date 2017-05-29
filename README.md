# N Queens
A program that solves the classic N queens problem by finding the number solutions for a given value of n.  

I implemented a backtracking solution in three different ways out of curiosity.  I wanted to see how fast each method compared to the others.  Not surprisingly, the solutions using vectors and arrays were blown away in terms of time and space efficiency by the solution using bitshifts.

| Method        | 11 queens     | 12 Queens  |
| ------------- |:-------------:| ----------:|
| vectors       | 12.815 sec.   | 78.937 sec.|
| array         | 5.0614 sec.   | 31.561 sec.|
| bitshift      | 0.004513 sec. | 0.022068 sec.|
