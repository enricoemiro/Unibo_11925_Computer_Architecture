// Scrivere un programma hack che traccia una riga verticale
// in colonna 20 lunga 50px
    // Set the counter to 50
    @50
    D=A
    @counter
    M=D
    
    @SCREEN     // Screen = 16834
    D=A
    @1
    D=D+A
    @address    // Address = 16834 + 1 => col / 16
    M=D

    // Set the word to 5 => 1000 (in Screen will be read as 000100000000000)
    @4
    D=A
    @word
    M=D
(LOOP)
    // If counter == 0 goto END
    @counter
    D=M
    @END
    D;JEQ

    // Get the word
    @word
    D=M

    // Draw the line
    @address
    A=M
    M=D

    // Go to the next row
    @32
    D=A
    @address
    M=M+D

    // Decrease the value of the counter by 1
    @counter
    M=M-1

    @LOOP
    0;JMP
(END)
    @END
    0;JMP