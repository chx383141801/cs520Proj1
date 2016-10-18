#include "node.h"
#ifndef Maximum
#define Maximum 10000
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


#endif