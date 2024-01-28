#include "Gates.hpp"

void NotGate::logic()
{
	outputs[0] = !inputs[0];
}

void AndGate::logic()
{
	outputs[0] = inputs[0] && inputs[1];
}

void OrGate::logic()
{
	outputs[0] = inputs[0] || inputs[1];
}

void TestGate::logic()
{
	outputs[0] = inputs[0] && inputs[1] && inputs[2] && inputs[3];
}
