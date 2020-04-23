package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.ILockTable;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.Value;

public class NewLockStatement implements IStatement{
    private String ID;

    public NewLockStatement(String varID){
        ID = varID;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        ILockTable lockTable = state.getLockTable();
        IDictionary<String, Value> symbolTable = state.getSymbolTable();

        if (symbolTable.containsKey(ID)){
            Integer address = lockTable.insert(-1);
            symbolTable.update(ID, new IntValue(address));
        }

        else throw new ToyException("Lock variable was not declared");

        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        Type varType = typeEnv.getValue(ID);

        if (varType == null)
            throw new ToyException("Variable was not declared");

        if (varType.equals(new IntType()))
        return typeEnv;

        else
            throw new ToyException("Variable not of int type");
    }

    @Override
    public String toString(){
        return "newLock(" + ID + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new NewLockStatement(ID);
    }
}
