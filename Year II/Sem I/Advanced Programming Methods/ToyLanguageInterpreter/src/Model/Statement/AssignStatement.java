package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.Expression.Exp;
import Model.ProgramState.ProgramState;
import Model.Type.Type;
import Model.Value.Value;

public class AssignStatement implements IStatement {
    private String ID;
    private Exp expression;

    public AssignStatement(String ID, Exp exp){
        this.ID = ID;
        this.expression = exp;
    }

    public String toString() {
        return ID + " = " + expression.toString();
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IDictionary<String, Value> symbolTable = state.getSymbolTable();

        if (symbolTable.containsKey(ID)) {
            Value val = expression.evaluate(symbolTable, state.getHeap());
            Type typeID = symbolTable.getValue(ID).getType();

            if (val.getType().equals(typeID))
                symbolTable.update(ID, val);
            else
                throw new ToyException("Declared type of variable " + ID + " does not match the type of the assigned expression\n");
        }
        else
            throw new ToyException("Variable " + ID + " was not declared before\n");
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        Type varType = typeEnv.getValue(ID);
        Type expType = expression.typeCheck(typeEnv);
        if (varType.equals(expType))
            return typeEnv;
        else
            throw new ToyException("Assignment: right hand side and left hand side have different types");
    }

    @Override
    public IStatement deepCopy() {
        return new AssignStatement(ID, expression.deepCopy());
    }
}
