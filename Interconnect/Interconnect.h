
#ifndef INTERCONNECT_H
#define INTERCONNECT_H
//#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "Parser.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

namespace INTC
{
	struct Node;

	struct Node
	{
		std::string Name;
		std::vector<Node *> Nodes;
		
		//Access path
		//std::vector<std::vector<std::string>> AccessPaths;

		Node() {}
		Node(std::string name) : Name(name) {}

		std::vector<std::string> GetSubNodeNames();
	};
}


#endif // !INTERCONNECT_H

