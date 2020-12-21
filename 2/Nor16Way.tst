load Nor16Way.hdl,
output-file Nor16Way.out,
compare-to Nor16Way.cmp,
output-list in%B1.16.1 out%B2.1.2;

set in %B0000000000000000,
eval,
output;

set in %B1111111100000000,
eval,
output;

set in %B0000000011111111,
eval,
output;

set in %B1111111111111111,
eval,
output;

set in %B1010101010101010,
eval,
output;

set in %B0101010101010101,
eval,
output;

set in %B1100110011001100,
eval,
output;

set in %B0011001100110011,
eval,
output;

set in %B1101111111011111,
eval,
output;