load Z.hdl,
output-file Z.out,
compare-to Z.cmp,
output-list in%B3.1.3 z%B3.1.3 out%B3.1.3;

set in 0,
set z 0,
eval,
output;

set in 0,
set z 1,
eval,
output;

set in 1,
set z 0,
eval,
output;

set in 1,
set z 1,
eval,
output;