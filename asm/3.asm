// RAM[0..9] = [10, 9, ..., 1]
    @10     // A <- 10
    M=A     // RAM[10] = 10
(SET)       // Set the value of RAM[0..9] to 0
    @10     // A <- 10
    D=M     // D = RAM[10]

    @SET_LOOP
    D;JEQ   // If D == 0 goto (LOOP)

    @10     // A <- 10
    A=M-1   // A = RAM[A] - 1
    M=0     // RAM[A] = 0

    @10     // A <- 10
    M=M-1   // RAM[10] = RAM[10] - 1

    @SET
    0;JMP   // goto (SET)
(SET_LOOP)  // Set the value for the loop
    @10     // A <- 10
    M=A     // RAM[10] = 10

    @11     // A <- 11
    M=A-1   // RAM[11] = A - 1
    M=M-1   // RAM[11] = RAM[11] - 1
(LOOP)
    @10     // A <- 10
    D=M     // D = RAM[10]

    @END
    D;JEQ   // If (D == 0) goto (END)

    @11     // A <- 11
    A=D-1   // A = D - 1
    M=A     // RAM[A] = A

    @10     // A <- 10
    M=M-1   // RAM[10] = RAM[10] - 1

    @LOOP
    0;JMP   // goto (LOOP)
(END)
    @END
    0;JMP   // Infinite loop