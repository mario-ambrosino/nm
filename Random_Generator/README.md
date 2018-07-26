# random
Pseudo-Random Generator for "Numerical Methods in Physics" Course

## Instruction
1. Clone the repository;
1. Run 'make.sh' to compile;
1. Run scripts in master directory;

## Status
- [x] First-Generation (pseudo)random generators;
- [x] Random test: Momenta on Uniform;
- [x] Random test: Chi-Squared on Uniform;
- [x] Random test: Maximum Period;
- [x] N/uniform generator: Exponential using "Inversion" method;
- [x] N/uniform generator: Normal using "Box-Muller" method;
- [x] N/uniform generator: Normal using "Marsaglia" method and check timing vs Box-Muller;
- [x] N/uniform generator: Gamma using "hit-or-miss" method;

Problems:
- [x] Problem: integrate area or volume using "hit-or-miss";
- [x] Problem: Random Walker (*TODO: analysis*) 
- [x] Problem: Central Limit Theorem;

## Actual Working Scripts:
- *make.sh*: generates executables to run shell scripts;
- *make_sequence.sh*: generates a sequence of N random numbers - between 0 and 1 using L'Ecuyer (best GCL in this project);
- *make_uniform_vect.sh*: generates 2-dim and 3-dim random data structures in ./dataset;
- *make_analysis.sh*: Makes average, standard deviation and chi-squared of the random distribution chosen.
Warning: Modify sources and recompile for each generator chosen to change generator. 
- *check_period.sh*: checks the maximum period of a GLC "y = (ax + b) mod m", choosing a,b,m as parameters
- *script_period.sh*: Divertissment: recursive check_period with random parameters a,b,m. Number of recursion as argument of the script.
- *make_histograms.sh*: generates an histogram with fixed bin numbers and input sequence;
- *central_limit_theorem*: Tests if the distribution fullfills the "Central Limit Theorem", generating histogram of the averages. It needs two input integer to set number of tests and number of random number generated for each test.
- *hitormiss.sh*: generates a measure of a circle and a sphere of custom radius using "hit-or-miss" method. 
- *make_walk.sh*: generates a 2-dim random walk using two different random walkers.

