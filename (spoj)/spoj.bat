echo ### Testes do spoj ### > "arq.txt"

@FOR %%A IN (*.in) DO call:tiraExt "%%A"

pause
goto :eof

:tiraExt
set var0=%~1
set var0=%var0:~0,-3%
call :doIt "%var0%"
goto :eof

:doIt
set var1=%~1

echo. >> "arq.txt"
echo teste %var1% >> "arq.txt"
spoj.exe < "%var1%.in" >> "arq.txt"
type "%var1%.sol" >> "arq.txt"


