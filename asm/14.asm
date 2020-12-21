// Colora lo schermo di nero se si preme un tasto
    @word
    M=-1            // word = 11..1

    @SCREEN
    D=A
    @address        // address = 16834
    M=D
(LOOP)
    // If no keys are press stop the draw processing
    @24576          // Keyboard
    D=M
    @STOP
    D;JEQ

    // Draw
    @word
    D=M
    @address
    A=M
    M=D

    // Update address
    @1
    D=A
    @address
    M=M+D

    @LOOP
    0;JMP
(STOP)
    @LOOP
    0;JMP