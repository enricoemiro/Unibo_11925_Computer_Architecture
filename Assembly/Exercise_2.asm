// RAM[2] = RAM[0] * RAM[1] (Assumendo RAM[1] diverso da 0)
// 
// C++
// x = 5
// y = 10
// result = 0
// while (y >  0) {
//   result = result + x
//   y--
// }
    @2      // A <- 2
    M=0     // RAM[2] = 0
(LOOP)
    @1      // A <- 1
    D=M     // D=RAM[1]

    @END
    D;JEQ   // If (RAM[1] == 0) goto (END)

    @0      // A <- 0
    D=M     // D=RAM[0]

    @2      // A <- 2
    M=D+M   // RAM[2]=RAM[0]+RAM[2]
    
    @1      // A <- 1
    M=M-1   // RAM[1] = RAM[1] - 1
    
    @LOOP
    0;JMP   // Goto (LOOP)
(END)
    @END
    0;JMP   // Infinite loop