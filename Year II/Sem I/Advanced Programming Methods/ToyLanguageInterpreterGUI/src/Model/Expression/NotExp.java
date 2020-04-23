package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.BoolType;
import Model.Type.Type;
import Model.Value.BoolValue;
import Model.Value.Value;

public class NotExp implements Exp {
    private Exp exp;

    public NotExp(Exp e)
    {
        exp = e;
    }

    @Override
    public String toString() {
        return "!" + exp.toString();
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table, IHeap heap) throws ToyException {
        Value v = exp.evaluate(table, heap);

        if (v.getType().equals(new BoolType()))
        {
            BoolValue b = (BoolValue) v;
            return new BoolValue(!b.getValue());
        }

        else throw new ToyException("not boolean");
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeEnv) throws ToyException {
        Type type = exp.typeCheck(typeEnv);

        if (type.equals(new BoolType())) {
            return new BoolType();
        }
        else throw new ToyException("Expression is not boolean");
    }

    @Override
    public Exp deepCopy() {
        return new NotExp(exp.deepCopy());
    }
}
