#include "node.h"

node::node()
{
    weight = '1';
    isHighway = 'n';
    index = '0';
    fN=gN=hN= Maximum;
    parent = nullptr;
}



node::~node()
{
}
