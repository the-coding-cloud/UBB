package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Expression.Exp;
import Model.ProgramState.ProgramState;
import Model.Type.RefType;
import Model.Type.Type;
import Model.Value.RefValue;
import Model.Value.Value;

public class WriteHeapStatement implements IStatement{
    String ID;
    Exp expression;
    public WriteHeapStatement(String v, Exp e)
    {
        ID = v;
        expression = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IDictionary<String, Value> symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();

        if(symbolTable.containsKey(ID))                         // variable is declared
        {
            Value value = symbolTable.getValue(ID);
            if(value.getType() instanceof RefType)              // variable is RefType
            {
                RefValue refVal = (RefValue) value;
                Type innerType = ((RefType)refVal.getType()).getInnerType();

                if(heap.containsKey(refVal.getAddress()))       // variable points to valid address in heap
                {
                    Value expValue = expression.evaluate(symbolTable, heap);
                    if(expValue.getType().equals(innerType))
                    {
                        heap.update(refVal.getAddress(), expValue);
                        return null;
                    }
                    else throw new ToyException("Invalid inner type");
                }
                else throw new ToyException("Invalid address");
            }
            else throw new ToyException("Invalid variable type");
        }
        else throw new ToyException("Variable not declared");
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        Type varType = typeEnv.getValue(ID);
        Type expType = expression.typeCheck(typeEnv);

        if(varType.equals(new RefType(expType))) {
            return typeEnv;
        }

        throw new ToyException("New allocation failed. The type is not reference");
    }

    @Override
    public String toString() {
        return "wH("+ ID +", "+ expression.toString()+")";
    }

    @Override
    public IStatement deepCopy() {
        return new WriteHeapStatement(ID, expression.deepCopy());
    }
}

