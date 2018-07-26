gcc -lm ./sources/reduced_analysis.c -I ./  -o ./exec/reduced_analysis.exe -Wall
gcc -lm ./sources/test_derivative.c -I ./ -o ./exec/test_derivative.exe -Wall
echo "Derivative Exe ... "
gcc -lm ./sources/test_integration.c -I ./ -o ./exec/test_integration.exe -Wall
echo "Integration Exe ... "
gcc -lm ./sources/zero_search.c -I ./ -o ./exec/zero_search.exe -Wall
echo "Zero Search Exe ... "
gcc -lm ./sources/zero_search.c -I ./ -o ./exec/zero_search.exe -Wall
echo "Minima Search Exe ... "
echo "Compilation Completed."
