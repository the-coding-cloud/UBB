package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.Type;
import Model.Value.Value;

public class VarExp implements Exp {
    private String ID;

    public VarExp(String ID){
        this.ID = ID;
    }

    @Override
    public String toString() {
        return ID;
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table, IHeap heap) throws ToyException {
        if (table.containsKey(ID))
            return table.getValue(ID);
        else
            throw new ToyException("Variable " + ID + " was not declared");
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeEnv) throws ToyException {
        return typeEnv.getValue(ID);
    }

    @Override
    public Exp deepCopy() {
        return new VarExp(ID);
    }
}
