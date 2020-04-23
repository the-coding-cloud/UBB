package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.ILockTable;
import Model.ADT.IStack;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.Value;

public class LockStatement implements IStatement {
    private String ID;

    public LockStatement(String varID){
        ID = varID;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        ILockTable lockTable = state.getLockTable();
        IStack<IStatement> stack = state.getExeStack();
        IDictionary<String, Value> symbolTable = state.getSymbolTable();

        if (symbolTable.containsKey(ID)){

            IntValue lockTableAddress = (IntValue) symbolTable.getValue(ID);
            Integer foundIndex = lockTableAddress.getValue();

            if (lockTable.containsKey(foundIndex)) {
                Integer lockValue = lockTable.getValue(foundIndex);
                if (lockValue == -1)
                {
                    lockTable.update(foundIndex, state.getProcessID());
                }
                else
                    stack.push(new LockStatement(ID));
            }

            else throw new ToyException("No lock was found");
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
        return "lock(" + ID + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new LockStatement(ID);
    }
}
