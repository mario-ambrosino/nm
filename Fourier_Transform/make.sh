
gcc ./sources/function_maker.c -Wall -I./ -lm -o ./exe/function_maker.exe
gcc ./sources/step_maker.c -Wall -I./ -lm -o ./exe/step_maker.exe
gcc ./sources/sinus_maker.c -Wall -I./ -lm -o ./exe/sinus_maker.exe
gcc ./sources/door_maker.c -Wall -I./ -lm -o ./exe/door_maker.exe
gcc ./sources/uniform_maker.c -Wall -I./ -lm -o ./exe/uniform_maker.exe
gcc ./sources/bit_reverse.c -Wall -I./ -lm -o ./exe/bit_reverse.exe
gcc ./sources/histogram.c -Wall -I./ -lm -o ./exe/histogram.exe

gcc ./sources/dft.c -Wall -I./ -lm -o ./exe/dft.exe -O3
gcc ./sources/fft.c -Wall -I./ -lm -o ./exe/fft.exe -O3
