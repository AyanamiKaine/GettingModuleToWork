// src/math/math.cppm
export module math; // Declares this file as the primary interface for the 'math' module

// Exporting a class
export class Calculator {
public:
    Calculator() = default;
    int multiply(int a, int b);
};

// Internal helper function (NOT exported, completely invisible outside this module)
int helper_log(int value);
