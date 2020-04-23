package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.Type;
import Model.Value.Value;

public class ValueExp implements Exp {
    private Value val;

    public ValueExp(Value v){
        val = v;
    }

    @Override
    public String toString() {
        return val.toString();
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table, IHeap heap) throws ToyException {
        return val;
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeEnv) throws ToyException {
        return val.getType();
    }

    @Override
    public Exp deepCopy() {
        return new ValueExp(val);
    }
}
