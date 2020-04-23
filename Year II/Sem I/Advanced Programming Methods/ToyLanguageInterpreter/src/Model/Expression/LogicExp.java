package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.BoolType;
import Model.Type.Type;
import Model.Value.BoolValue;
import Model.Value.Value;

public class LogicExp implements Exp {
    private Exp exp1;
    private Exp exp2;
    private int op; // 1 - and, 2 - or

    public LogicExp(int o, Exp e1, Exp e2)
    {
        exp1 = e1;
        exp2 = e2;
        op = o;
    }

    @Override
    public String toString() {
        if (op == 1)
            return exp1.toString() + "and" + exp2.toString();
        else if (op == 2)
            return exp1.toString() + "or" + exp2.toString();
        else return null;
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table, IHeap heap) throws ToyException {
        Value v1,v2;
        v1 = exp1.evaluate(table, heap);

        if (v1.getType().equals(new BoolType())) {
            v2 = exp2.evaluate(table, heap);
            if (v2.getType().equals(new BoolType())) {
                BoolValue i1 = (BoolValue)v1;
                BoolValue i2 = (BoolValue)v2;
                Boolean n1, n2;
                n1= i1.getValue();
                n2 = i2.getValue();
                if (op == 1) return new BoolValue(n1&&n2);
                if (op == 2) return new BoolValue(n1||n2);
            }
            else
                throw new ToyException("Second operand is not boolean");
        }
        else
            throw new ToyException("first operand is not boolean");
        return null;
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeEnv) throws ToyException {
        Type type1, type2;

        type1 = exp1.typeCheck(typeEnv);
        type2 = exp2.typeCheck(typeEnv);

        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new BoolType();
            }
            else throw new ToyException("Second operand is not boolean");
        }
        else throw new ToyException("First operand is not an boolean");
    }

    @Override
    public Exp deepCopy() {
        return new LogicExp(op, exp1.deepCopy(), exp2.deepCopy());
    }
}
