// RAM[10] = max(RAM[9], RAM[8], ..., RAM[0]) 
    @9      // A <- 9
    D=M     // D = RAM[9]

    @10     // A <- 10
    M=D     // RAM[10] = D

    @11     // A <- 11
    M=A-1   // RAM[11] = 10
    M=M-1   // RAM[11] = 9
(LOOP)
    // i
    @11     // A <- 11
    D=M     // D = A[i]

    @END
    D;JLT   // If D < 0 goto END

    @10     // A <- 10
    A=D     // A <- A[i]
    D=M     // D = RAM[i]

    // RAM[10] - RAM[i] < 0
    @10     // A <- 10
    D=M-D   // D = RAM[10] - RAM[i]

    @SET_NEW_MAX
    D;JLE   // If d <= 0 goto SET_NEW_MAX

    // Decrease the value of RAM[11] by 1
    @11     // A <- 11
    M=M-1   // RAM[11] = RAM[11] - 1

    @LOOP
    0;JMP
(SET_NEW_MAX)
    @11     // A <- 11
    D=M     // D = RAM[11]

    @10     // A <- 10
    A=D     // A <- A[i]
    D=M     // D = RAM[i]

    @10     // A <- 10
    M=D     // RAM[10] = D

    @11     // A <- 11
    M=M-1   // RAM[11] = RAM[11] - 1

    @LOOP
    0;JMP
(END)
    @END
    0;JMP