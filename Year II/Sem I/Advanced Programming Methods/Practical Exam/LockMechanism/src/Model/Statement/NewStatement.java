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

public class NewStatement implements IStatement{
    private String ID;
    private Exp expression;

    public NewStatement(String varName, Exp e){
        ID = varName;
        expression = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IDictionary<String, Value> symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();

        if (symbolTable.containsKey(ID)) {                                  // variable was declared
            if(symbolTable.getValue(ID).getType() instanceof RefType){      // variable is of type RefType
                Value expValue = expression.evaluate(symbolTable, heap);
                RefType variableType = (RefType) symbolTable.getValue(ID).getType();

                if(expValue.getType().equals(variableType.getInnerType()))  // variable inner type matches expression type
                {
                    Integer address = heap.insert(expValue);
                    symbolTable.update(ID, new RefValue(expValue.getType(), address));
                }
                else
                    throw new ToyException("Value types not matching");
            }
            else
                throw new ToyException("Variable not of ref type");
        }
        else
            throw new ToyException("Variable not declared");
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        Type varType = typeEnv.getValue(ID);
        Type expType = expression.typeCheck(typeEnv);

        if (varType.equals(new RefType(expType)))
            return typeEnv;
        else
            throw new ToyException("New: Variable type does not match expression type");
    }

    @Override
    public String toString() {
        return "new(" + ID + " " + expression.toString() + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new NewStatement(ID, expression);
    }
}
