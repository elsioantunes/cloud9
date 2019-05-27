@echo off
set path=%path%;E:\salvador\ffmpeg
set ext=cpp


@FOR %%A IN (*.%ext%) DO call:doIt "%%A"


pause
goto :eof

:doIt
set var0=%~1
set var0=%var0:~0,-4%

echo /************************************* >> arq.txt
echo  ** %var0% >> arq.txt
echo  *************************************/ >> arq.txt
type "%var0%.cpp" >> arq.txt

