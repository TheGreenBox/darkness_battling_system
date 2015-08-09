#include "types.h"

#include <lib/json/json/json.h>

#include <iostream>
#include <memory>

struct TProblemSolution {
    size_t ProblemId;  // The `id` of the game configuration
    TSeed Seed;  // The seed for the particular game
    std::string Solution;
    std::string Tag = "";  // A tag for this solution.
};

void AnswerFormattedPrint(
    const std::vector<TProblemSolution>& solutions,
    std::ostream& out
);
