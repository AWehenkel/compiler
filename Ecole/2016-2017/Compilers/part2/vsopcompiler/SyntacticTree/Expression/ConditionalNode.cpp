#include "ConditionalNode.hpp"

using namespace std;

string ConditionalNode::getLiteral() const{
  string literal = "If(" + e_condition->getLiteral() + "," + e_action->getLiteral();
  string end = e_else_action ? "," + e_else_action->getLiteral() : "";
  return literal + end + ")";
}
