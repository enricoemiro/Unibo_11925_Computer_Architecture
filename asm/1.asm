// RAM[2] = RAM[0] + RAM[1]
    @2      // A <- 0
    M=0     // RAM[2] = 0

    @0      // A <- 0
    D=M     // D = RAM[0]

    @1      // A <- 1 
    M=D+M   // RAM[1] = RAM[1] + RAM[0]
    D=M     // D = RAM[1]

    @2      // A <- 0
    M=D     // RAM[2] = D
(END)
    @END
    0;JMP