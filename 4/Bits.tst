load Bits.hdl,
output-file Bits.out,
compare-to Bits.cmp,
output-list instruction%B1.16.1 A%B1.1.1 C%B1.1.1 out%B1.13.1;

set instruction %B0000000000000000,
set A %B1,
set C %B0,
eval,
output;

set instruction %B0010000000000000,
set A %B1,
set C %B0,
eval,
output;

set instruction %B0100000000000000,
set A %B1,
set C %B0,
eval,
output;

set instruction %B0110000000000000,
set A %B1,
set C %B0,
eval,
output;

set instruction %B1000000000000000,
set A %B0,
set C %B0,
eval,
output;

set instruction %B1010000000000000,
set A %B0,
set C %B0,
eval,
output;

set instruction %B1100000000000000,
set A %B0,
set C %B0,
eval,
output;

set instruction %B1110000000000000,
set A %B0,
set C %B1,
eval,
output;

set instruction %B1110000000001111,
set A %B0,
set C %B1,
eval,
output;

set instruction %B1110000011111111,
set A %B0,
set C %B1,
eval,
output;

set instruction %B1111111111111111,
set A %B0,
set C %B1,
eval,
output;