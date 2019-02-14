REM %1 path to ocloc
REM %2 path to .cl file WITHOUT EXTENSION
%1 -device skl -file %2.cl
del *.bin
del *.gen
move %2_Gen9core.spv %2.spv