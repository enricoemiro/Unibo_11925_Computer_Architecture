// RAM[2] = RAM[1] / RAM[0]
// RAM[3] = RAM[1] mod RAM[0] divisione intera
// 
// Pseudocode
// 
// x = -12, y = 3, res = 0, mod = 0
// 
// if (x < 0) {x=-x, flag=1}
// if (y < 0) {y=-y, flag=1-flag}
// if (x - y < 0) {return res}
// 
// while (x > 0) {
//   x = x - y
//   res = res + 1
//   if (x - y < 0) {
//      mod = x
//      break
//   }
// }
// 
// if (flag > 0) res=-res;
    // Result of the division
    @2
    M=0

    // Remainder of the division
    @3
    M=0

    // Flag (0 or 1)
    @4
    M=0
    
    // Check if x - y < 0
    @5
    M=0
(X) // x = RAM[1]
    @1
    D=M

    // If x < 0 goto SET_X_POS
    @SET_X_POS
    D;JLT
(Y) // y = RAM[0]
    @0
    D=M

    // If y < 0 goto SET_Y_POS
    @SET_Y_POS
    D;JLT

    // If neither x nor y are less
    // than zero goto CHECK_X_LT_Y
    @CHECK_X_LT_Y
    0;JMP
(SET_X_POS) // x = -x
    @1
    M=-M
    D=M

    // Flag = 1
    @4
    M=1

    // Goto Y
    @Y
    0;JMP
(SET_Y_POS) // y = -y
    @0
    M=-M

    // Flag = 1 - Flag
    @4
    D=1
    M=D-M
(CHECK_X_LT_Y) // x - y < 0
    @1
    D=M   // set D with X

    @5
    M=D   // set RAM[5] with x

    @0
    D=M   // set D with y

    @5
    M=M-D // x - y

    @5
    D=M   // set D with x - y

    // Check if D < 0
    @END
    D;JLT
(LOOP) // while(x > 0)
    @1    
    D=M

    // if d <= 0 goto CHECK_FLAG
    @CHECK_FLAG
    D;JLE

    // x = x - y
    @0
    D=M
    @1
    M=M-D

    // res = res + 1
    @2
    M=M+1

    // if (x - y < 0) goto SET_MOD
    @1
    D=M
    @5
    M=D
    @0
    D=M
    @5
    M=M-D
    D=M
    @SET_MOD
    D;JLT

    @LOOP
    0;JMP
(SET_MOD) // mod = x
    @1
    D=M
    @3
    M=D
(CHECK_FLAG) // if flag > 0 {res = -res}
    @4
    D=M
    
    // if flag == 0 goto END
    @END
    D;JEQ

    @2
    M=-M
(END)
    @END
    0;JMP