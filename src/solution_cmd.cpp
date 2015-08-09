#include "solution_cmd.h"

#include <array>
#include <cstdlib>

namespace {

using MoveOperationCmdSymbols = std::vector<char>;

static const std::array<
    MoveOperationCmdSymbols,
    static_cast<size_t>(EMoveOperations::COUNT)
>
MOVE_TO_CMD_SYMBOLS{
    MoveOperationCmdSymbols{'b', 'c', 'e', 'f', 'y', '2'}, // SLIDE_EAST
    MoveOperationCmdSymbols{'p', '\'','!', '.', '0', '3'}, // SLIDE_WEST
    MoveOperationCmdSymbols{'l', 'm', 'n', 'o', ' ', '5'}, // SLIDE_SOUTHEAST
    MoveOperationCmdSymbols{'a', 'g', 'h', 'i', 'j', '4'}, // SLIDE_SOUTHWEST
    MoveOperationCmdSymbols{'d', 'q', 'r', 'v', 'z', '1'}, // ROTATE_CLOCKWISE
    MoveOperationCmdSymbols{'k', 's', 't', 'u', 'w', 'x'}  // ROTATE_ANTI_CLOCKWISE
};

} // unnamed namespace

std::string MakeSolutionCmdFrom(const TWayGraph::TWay& way) {
    std::string ret;
    for (EMoveOperations operation : way) {
        size_t sizetOperation = static_cast<size_t>(operation);
        const auto& thisOpSymbols = MOVE_TO_CMD_SYMBOLS.at(sizetOperation);
        size_t symbolIndex = rand() % thisOpSymbols.size();
        ret += thisOpSymbols.at(symbolIndex);
    }

    return ret;
}
