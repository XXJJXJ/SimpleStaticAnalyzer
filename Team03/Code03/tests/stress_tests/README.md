# Stress test results

## Source
- ~500 lines of code with 5 procedures
- ~500 variables
- nested container statements

## Cross Product
- `stmt s; Select s` (500): 18.000000 ms
- `stmt s1, s2; Select <s1, s2>` (500x500): 2868.000000 ms 

## Clause Optimisation
- many duplicated clauses:
	- without optimisation: 3045.000000 ms
	- with optimisation: 2703.000000 ms
- many restrictable clauses:
	- without optimisation: 356.000000 ms
	- with optimisation: 276.000000 ms

## Join Optimisation