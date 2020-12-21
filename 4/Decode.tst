load Decode.hdl,
output-file Decode.out,
compare-to Decode.cmp,
output-list instruction%B1.16.1 A%B1.1.1 C%B1.1.1;

set instruction %B0000000000000000,
eval,
output;

set instruction %B0010000000000000,
eval,
output;

set instruction %B0100000000000000,
eval,
output;

set instruction %B0110000000000000,
eval,
output;

set instruction %B1000000000000000,
eval,
output;

set instruction %B1010000000000000,
eval,
output;

set instruction %B1100000000000000,
eval,
output;

set instruction %B1110000000000000,
eval,
output;
