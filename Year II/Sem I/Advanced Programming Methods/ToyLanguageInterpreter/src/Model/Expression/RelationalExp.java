package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.BoolType;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.BoolValue;
import Model.Value.Value;

public class RelationalExp implements Exp {
    private Exp exp1;
    private Exp exp2;
    private int op; // 1 - < | 2 - <= | 3 - == | 4 - != | 5 - > | 6 - >=

    public RelationalExp(int o, Exp e1, Exp e2)
    {
        exp1 = e1;
        exp2 = e2;
        op = o;
    }

    @Override
    public String toString() {
        if (op == 1)
            return exp1.toString() + "<" + exp2.toString();
        else if (op == 2)
            return exp1.toString() + "<=" + exp2.toString();
        else if (op == 3)
            return exp1.toString() + "==" + exp2.toString();
        else if (op == 4)
            return exp1.toString() + "!=" + exp2.toString();
        else if (op == 5)
            return exp1.toString() + ">" + exp2.toString();
        else if (op == 6)
            return exp1.toString() + ">=" + exp2.toString();
        else return null;
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table, IHeap heap) throws ToyException {
        Value v1,v2;
        v1 = exp1.evaluate(table, heap);

        if (v1.getType().equals(new IntType())) {
            v2 = exp2.evaluate(table, heap);
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue)v1;
                IntValue i2 = (IntValue)v2;
                int n1, n2;
                n1 = i1.getValue();
                n2 = i2.getValue();
                if (op == 1) return new BoolValue(n1<n2);
                if (op == 2) return new BoolValue(n1<=n2);
                if (op == 3) return new BoolValue(n1==n2);
                if (op == 4) return new BoolValue(n1!=n2);
                if (op == 5) return new BoolValue(n1>n2);
                if (op == 6) return new BoolValue(n1>=n2);
            }
            else
                throw new ToyException("Second operand is not int");
        }
        else
            throw new ToyException("First operand is not int");
        return null;
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeEnv) throws ToyException {
        Type type1, type2;

        type1 = exp1.typeCheck(typeEnv);
        type2 = exp2.typeCheck(typeEnv);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new BoolType();
            }
            else throw new ToyException("Second operand is not an integer");
        }
        else throw new ToyException("First operand is not an integer");
    }


    @Override
    public Exp deepCopy() {
        return new RelationalExp(op, exp1.deepCopy(), exp2.deepCopy());
    }
}
