// RAM[RAM[0],...,RAM[1]] = 1,...,1    assumendo RAM[1] > RAM[0]
//
// RAM[0] = 5
// RAM[1] = 10
// 
// From RAM[5] to RAM[10] and set each register to 1 
(LOOP)
    @1      // A <- 1
    D=M     // D = RAM[1]

    @0      // A <- 0
    A=M     // A <- RAM[0]
    M=D-A   // RAM[1] - RAM[0]
    D=M     // D = RAM[1] - RAM[0]

    @SET_RAM1
    D;JLE  // If D <= 0 goto END
    
    // Set the value of RAM[i] to 1
    @0      // A <- 0
    A=M     // A <- RAM[i]
    M=1     // RAM[i] = 1
    
    // Increase the value of RAM[0]
    @0      // A <- 0
    M=M+1   // RAM[0] = RAM[0] + 1

    @LOOP
    0;JMP
(SET_RAM1)
    @1      // A <- 1
    A=M     // A <- RAM[1]
    M=1     // RAM[1] = 1
(END)
    @END
    0;JMP