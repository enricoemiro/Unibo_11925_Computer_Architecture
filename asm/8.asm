// RAM[2] = RAM[1] nand RAM[0]
    @2      // A <- 2
    M=0     // RAM[0] = 0

    @1      // A <- 1
    D=M     // D = RAM[1]

    @0      // A <- 0
    D=D&M   // & bit-wise

    @2      // A <- 0
    M=!D    // RAM[2] = Not(D)
(END)
    @END;
    0;JMP