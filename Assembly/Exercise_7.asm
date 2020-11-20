// RAM[2] = RAM[1] – RAM[0] - 2
    @2      // A <- 2
    M=0     // RAM[2] = 0

    @1      // A <- 1
    D=M     // D = RAM[1]

    @0      // A <- 1
    D=D-M   // D = RAM[1] - RAM[0]

    @2      // A <- 2
    D=D-1   // D = D - 1
    D=D-1   // D = D - 1
    M=D     // RAM[2] = D
(END)
    @END
    0;JMP