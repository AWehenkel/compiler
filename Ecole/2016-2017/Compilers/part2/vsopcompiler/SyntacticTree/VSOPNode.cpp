#include "VSOPNode.hpp"

using namespace std;

ostream& operator<<(ostream &out, VSOPNode const &node) {
	out << node.getLiteral();
	return out;
}
