// RAM[10] = RAM[9] + RAM[8] + ... + RAM[1] + RAM[0]
    @10     // A <- 10
    M=0     // RAM[10] = 0

    @9      // A <- 9
    D=A     // D = 9

    @11     // A <- 11
    M=D     // RAM[11] = 9
(LOOP)
    @11     // A <- 11
    D=M     // D = RAM[11]

    @END
    D;JEQ   // If D == 0 goto (END)

    @10     // A <- 10
    A=D     // A = D
    D=M     // D = RAM[A] => save the value of RAM[A] in D

    @10     // A <- 10
    M=D+M   // RAM[M] = RAM[M] + D

    // Decrease the value of RAM[1] by one
    @11
    M=M-1

    @LOOP
    0;JMP
(END)
    @END
    0;JMP