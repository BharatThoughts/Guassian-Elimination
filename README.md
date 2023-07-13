# Guassin-Elimination
An C/C++ implementation for solving N equations with N unknowns with the help of Gaussian elimination.

## Input File Format

The input file should be a CSV (Comma-Separated Values) file containing the augmented matrix of the system of equations. The matrix should have `n` rows and `n+1` columns, where the last column represents the constants on the right-hand side of the equations. The elements of the matrix should be numeric values.

For reference or for testing, use input file [Book2.csv](Book2.csv).

## Supported Error Handling

The program handles the following errors:

- If the input file does not exist, an error message is displayed, and the program terminates.
- If the system of equations has no solution or infinite solutions, an appropriate message is displayed, and the program terminates.


## License

This program is released under the [MIT License](https://opensource.org/licenses/MIT).

## Author

This program was written by [Bharat Singh](https://twitter.com/BharatThoughts_).
