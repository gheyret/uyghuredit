set CMDPATH=D:\gheyret\MinGW\bin\
set PATH=%PATH%;%CMDPATH%

:beshi
%CMDPATH%mingw32-make.exe -f UMakefile.win %1

pause

goto beshi