// Disegna sullo schermo un rettangolo largo 16 pixel e alto R[0] pixel
    // If RAM[0] <= 0 there is nothing to print
    @0
    D=M
    @END
    D;JLE

    // Set address variable with the value of the screen (16384)
    @SCREEN
    D=A
    @address
    M=D
(LOOP)
    // If RAM[0] == 0 goto END
    @0
    D=M
    @END
    D;JEQ

    // Print to the screen the current address
    // Goto the RAM[address] and set it to 111..1
    @address
    A=M
    M=-1

    // Goto next row (each row has 0-31 address)
    @32
    D=A
    @address
    M=M+D

    // Decrease the value of RAM[0] by one
    @0
    M=M-1

    @LOOP
    0;JMP
(END)
    @END
    0;JMP
