// Scrivere un programma hack che traccia sullo schermo una linea
// diagonale (a 45 gradi) che parte dall'angolo in alto a sinistra lunga
// 50 pixel.
    // Set the value of the counter
    @50
    D=A
    @counter
    M=D

    // Set the value of the counter column
    @counter_column
    M=0

    // Set the value of the address
    @SCREEN
    D=A         // D=16834
    @address
    M=D
(SET_INITIAL_WORD)
    // Word = 1
    @1
    D=A
    @word
    M=D
(LOOP)
    // If counter == 0 goto END
    @counter
    D=M
    @END
    D;JEQ

    // Draw
    @word
    D=M
    @address
    A=M         // A = RAM[ADDRESS]
    M=D         // RAM[A] = word

    // Update the word
    @word
    D=M
    M=M+D

    // Set the address on the next row
    @32
    D=A
    @address
    M=M+D

    // Decrease the counter variable by 1
    @counter
    M=M-1

    // Increment the counter_column variable
    // if counter_column - 16 == 0 goto SET_NEW_VALUES
    @counter_column
    M=M+1
    D=M
    @16
    D=D-A
    @SET_NEW_VALUES
    D;JEQ

    @LOOP
    0;JMP
(SET_NEW_VALUES)
    // Reset the counter_column to 0
    @counter_column
    M=0

    // Set the new value of the address
    @address
    M=M+1

    // Goto set initial_word
    @SET_INITIAL_WORD
    0;JMP
(END)
    @END
    0;JMP