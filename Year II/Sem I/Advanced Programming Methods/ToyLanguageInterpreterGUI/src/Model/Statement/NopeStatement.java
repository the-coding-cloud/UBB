package Model.Statement;

import Model.ADT.IDictionary;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Type.Type;

public class NopeStatement implements IStatement {

    @Override
    public String toString() {
        return "Nope";
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new NopeStatement();
    }
}
