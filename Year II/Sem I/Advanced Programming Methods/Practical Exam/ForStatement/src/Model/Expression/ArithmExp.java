package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.Value;

public class ArithmExp implements Exp {
    private Exp exp1;
    private Exp exp2;
    private int op; // 1 - add, 2 - subtract, 3 - multiply, 4 - divide

    public ArithmExp(int o, Exp e1, Exp e2)
    {
        exp1 = e1;
        exp2 = e2;
        op = o;
    }

    @Override
    public String toString() {
        if (op == 1)
            return "(" + exp1.toString() + "+" + exp2.toString() + ")";
        else if(op == 2)
            return exp1.toString() + "-" + exp2.toString();
        else if (op == 3)
            return exp1.toString() + "*" + exp2.toString();
        else if (op == 4)
            return exp1.toString() + "/" + exp2.toString();

        return null;
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
                n1= i1.getValue();
                n2 = i2.getValue();
                if (op == 1) return new IntValue(n1+n2);
                else if (op == 2) return new IntValue(n1-n2);
                else if (op == 3) return new IntValue(n1*n2);
                else if (op == 4)
                    if(n2==0) throw new ToyException("Division by zero");
                    else return new IntValue(n1/n2);
            }

            else
                throw new ToyException("Second operand is not an integer");
        }
        else
            throw new ToyException("First operand is not an integer");

        return null;
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeEnv) throws ToyException {
        Type type1, type2;

        type1 = exp1.typeCheck(typeEnv);
        type2 = exp2.typeCheck(typeEnv);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new IntType();
            }
            else throw new ToyException("Second operand is not an integer");
        }
        else throw new ToyException("First operand is not an integer");
    }

    @Override
    public Exp deepCopy() {
        return new ArithmExp(op, exp1.deepCopy(), exp2.deepCopy());
    }
}
