#include "Gates.hpp"

void NotGate::logic()
{
	outputs[0] = !inputs[0];
}

void AndGate::logic()
{
	outputs[0] = inputs[0] && inputs[1];
}
