#include "printnode.h"

void PrintNode::ValidateSemantics()
{
    Value->ValidateSemantics();
}

void PrintNode::Interpret()
{
    ExpresionValue *value = Value->Interpret();
    cout<<value<<endl;
}
