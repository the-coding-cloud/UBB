package Model.Statement;

import Model.ADT.IDictionary;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Type.Type;
import Model.Value.Value;

public class VarDeclStatement implements IStatement {
    private String ID;
    private Type type;

    public VarDeclStatement(String ID, Type type){
        this.ID = ID;
        this.type = type;
    }

    @Override
    public String toString() {
        return type.toString() + " " + ID;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IDictionary<String, Value> symbolTable = state.getSymbolTable();

        if (symbolTable.containsKey(ID)) {
            throw new ToyException("Variable " + ID + " was declared before\n");
        }
        else {
            symbolTable.insert(ID, type.getDefaultValue());
        }
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        typeEnv.insert(ID,type);
        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new VarDeclStatement(ID, type.deepCopy());
    }
}
