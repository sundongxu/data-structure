#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>
using namespace std;

#define DEFAULT_SIZE 5
#define DEFAULT_INFINITY 100000

#define SUCCESS 100
#define NOT_PRESENT 200
#define ENTRY_FOUND 300
#define RANGE_ERROR 400
#define OVER_FLOW 500
#define UNDER_FLOW 600

#define UNVISITED 0
#define VISITED 1

#define TOPO_SUCCESS 2
#define TOPO_FAIL 3

// string StatusCode2Str(int statusCode)
// {
//     switch (statusCode)
//     {
//     case SUCCESS:
//         return "Success!";
//     case NOT_PRESENT:
//         return "Not Present!";
//     case ENTRY_FOUND:
//         return "Entry Found!";
//     case RANGE_ERROR:
//         return "Range Error!";
//     case OVER_FLOW:
//         return "Overflow!";
//     case UNDER_FLOW:
//         return "Underflow!";
//     case TOPO_SUCCESS:
//         return "Topology Sort Finished!";
//     case TOPO_FAIL:
//         return "Topology Sort Failed!";
//     }
//     return "";
// }

#endif // CONSTANT_H