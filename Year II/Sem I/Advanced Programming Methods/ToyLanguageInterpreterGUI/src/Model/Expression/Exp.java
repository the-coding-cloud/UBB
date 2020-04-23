package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.Type;
import Model.Value.Value;

public interface Exp {
    Value evaluate(IDictionary<String,Value> table, IHeap heap) throws ToyException;
    Type typeCheck(IDictionary<String,Type> typeEnv) throws ToyException;
    Exp deepCopy();
}
