package Model.Expression;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Type.RefType;
import Model.Type.Type;
import Model.Value.RefValue;
import Model.Value.Value;

public class ReadHeap implements Exp {
    private Exp expression;

    public ReadHeap(Exp e) {
        expression = e;
    }

    @Override
    public String toString() {
        return "rH("+ expression.toString()+")";
    }

    @Override
    public Value evaluate(IDictionary<String, Value> table, IHeap heap) throws ToyException {
        Value value = expression.evaluate(table, heap);
        if (value instanceof RefValue)              // the value of the expression is a RefValue --- get the heap address
        {
            RefValue refValue = (RefValue) value;
            int address = refValue.getAddress();    // get the heap address
            if(heap.containsKey(address))           // check if address is valid
            {
                return heap.getValue(address);      // return the value from that address
            }
            else throw new ToyException("Invalid address");
        }
        else throw new ToyException("Not a RefValue");
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeEnv) throws ToyException {
        Type type = expression.typeCheck(typeEnv);
        if (type instanceof RefType) {
            RefType refType = (RefType) type;
            return refType.getInnerType();
        }
        else throw new ToyException("The readHeap argument is not of refType");
    }

    @Override
    public Exp deepCopy() {
        return new ReadHeap(expression.deepCopy());
    }
}
