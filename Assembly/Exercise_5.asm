// RAM[2] = max(RAM[0], RAM[1])
// RAM[0] - RAM[1] < 0
    @2      // A <- 2
    M=0     // RAM[2] = 0

    @2      // A <- 2 
    A=A-1   // A <- 1
    D=M     // D = RAM[1]

    @2      // A <- 2
    M=D     // RAM[2] = RAM[1]

    @2      // A <- 2
    A=A-1
    A=A-1   // A <- 0
    D=M     // D = RAM[0]

    @2      // A <- 2
    D=D-M   // D = RAM[0] - RAM[1]

    @IF_FALSE
    D;JLE

    @2      // A <- 2
    A=A-1
    A=A-1   // A <- 0
    D=M     // D = RAM[0]

    @2
    M=D     // RAM[2] = RAM[0]

    @END
    0;JMP
(IF_FALSE)
    @2      // A <- 2
    A=A-1   // A <- 1
    D=M     // D = RAM[1]

    @2      // A <- 2
    M=D     // RAM[2] = RAM[1]
(END)
    @END
    0;JMP