set SGDK=d:\code\retro\megadrive\sgdk
set MAKE=%SGDK%\bin\make

rmdir out
rmdir src\boot

%MAKE% -f %SGDK%\makefile.gen
