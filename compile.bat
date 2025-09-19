@echo off
echo =====================================
echo    COMPILANDO BATALHA NAVAL
echo =====================================
echo.

REM Limpar execut�veis anteriores
del /q *.exe 2>nul

echo Compilando e criando execut�vel...
gcc -Wall -Wextra -std=c99 battleShip_main.c battleShip_functions.c -o batalha_naval.exe
if errorlevel 1 (
    echo ERRO: Falha na compilacao
    pause
    exit /b
)

echo.
echo =====================================
echo    COMPILA��O CONCLU�DA!
echo =====================================
echo Execut�vel criado: batalha_naval.exe
echo.

if "%1"=="run" (
    echo Executando o programa...
    echo.
    batalha_naval.exe
)

pause

