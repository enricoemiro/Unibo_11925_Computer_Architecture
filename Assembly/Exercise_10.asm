// RAM[2] = RAM[1] * (2^RAM[0])

// 2^RAM[0]
//
// Pseudocode
// 
// exponent = 4
// incrementer = 2
// result = 0
// 
// if (exponent == 0) {
//    result = RAM[1]
// } else {
//   while (exponent != 0)
//   {
//       result = 2 * result
//       exponent--
//   }
// }
    // ram[2] = ram[1] * (2^ram[0])
    @2      // A <- 2
    M=A     // RAM[2] = 2
    
    // If RAM[1] = 0 goto END
    @1
    D=M
    @END
    D;JEQ

    // If RAM[0] == 0 goto EXP_0
    @0
    M=M-1
    D=M
    @EXP_0
    D;JEQ
(POWER)
    // exponent
    @0      // A <- 0
    D=M     // D = RAM[0]

    @MULTIPLY
    D;JEQ   // If (exponent == 0) goto MULTIPLY

    // result = 2 * result
    @2      // A <- 2
    D=M
    M=D+M   // RAM[4] = 2 * RAM[4]
    D=M     // D = RAM[4]

    // decrease the value of exponent
    @0      // A <- 0
    M=M-1   // RAM[0]-=1

    @POWER
    0;JMP
(MULTIPLY)
    @1
    D=M

    @END
    D;JEQ

    @0
    D=M
    @2
    M=D+M

    @1
    M=M-1 

    @MULTIPLY
    0;JMP
(EXP_0)
    // result = RAM[1]
    @1      // A <- 1
    D=M     // D = RAM[1]

    @2      // A <- 2
    M=D     // RAM[2] = RAM[1]
(END)
    @END
    0;JMP