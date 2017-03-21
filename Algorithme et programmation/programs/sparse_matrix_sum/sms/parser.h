#pragma once

#include "types.h"

#include <string>

class Parser
{
    public:
        Parser();
        std::pair<SparseMatrix,SparseMatrix> parse(std::string path);
};
