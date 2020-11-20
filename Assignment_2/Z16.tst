load Z16.hdl,
output-file Z16.out,
compare-to Z16.cmp,
output-list in%B1.16.1 z%B3.1.3 out%B1.16.1;

set in %B0000000000000000,
set z 0,
eval,
output;

set in %B1111111100000000,
set z 0,
eval,
output;

set in %B0000000011111111,
set z 1,
eval,
output;

set in %B1111111111111111,
set z 0,
eval,
output;

set in %B1010101010101010,
set z 0,
eval,
output;

set in %B0101010101010101,
set z 1,
eval,
output;

set in %B1100110011001100,
set z 1,
eval,
output;

set in %B0011001100110011,
set z 1,
eval,
output;