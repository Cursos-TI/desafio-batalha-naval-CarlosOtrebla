@echo off
echo =====================================
echo       COMPILANDO BATALHA NAVAL
echo =====================================
echo.

REM Limpar executaveis anteriores
del /q *.exe 2>nul

echo Compilando e criando executavel...
gcc -Wall -Wextra -std=c99 battleShip_main.c battleShip_functions.c -o batalha_naval.exe
if errorlevel 1 (
    echo ERRO: Falha na compilação
    pause
    exit /b
)

echo.
echo =====================================
echo       COMPILACAO CONCLUIDA!
echo =====================================
echo Executavel criado: batalha_naval.exe
echo.

if "%1"=="run" (
    echo Executando o programa...
    echo.
    batalha_naval.exe
)

pause
