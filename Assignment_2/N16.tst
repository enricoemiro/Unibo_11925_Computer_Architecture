load N16.hdl,
output-file N16.out,
compare-to N16.cmp,
output-list in%B1.16.1 n%B3.1.3 out%B1.16.1;

set in %B0000000000000000,
set n 0,
eval,
output;

set in %B1111111100000000,
set n 1,
eval,
output;

set in %B0000000011111111,
set n 1,
eval,
output;

set in %B1111111111111111,
set n 0,
eval,
output;

set in %B1010101010101010,
set n 1,
eval,
output;

set in %B0101010101010101,
set n 1,
eval,
output;

set in %B1100110011001100,
set n 0,
eval,
output;

set in %B0011001100110011,
set n 1,
eval,
output;

set in %B1101111111011111,
set n 1,
eval,
output;