#pragma once

#include "way_graph.h"
#include "move_operations.h"

#include <string>
#include <vector>

// Remove when the actual TWay is ready
using TWay = std::vector<EMoveOperations>;

std::string MakeSolutionCmdFrom(const TWay& way);
