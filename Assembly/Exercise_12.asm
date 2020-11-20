// Adds +1...+100
// int i = 1
// int sum = 0
// while (i <= 100) {
//     sum = sum + i
//     i = i + 1
// }
    @100
    D=A

    // Variable i = 100
    @i
    M=D    

    @sum
    M=0
(LOOP)
    // D = 100
    @i
    D=M

    // If D == 0 goto END
    @END
    D;JEQ

    @sum
    M=M+D

    @i
    M=M-1

    @LOOP
    0;JMP
(END)
    @END
    0;JMP