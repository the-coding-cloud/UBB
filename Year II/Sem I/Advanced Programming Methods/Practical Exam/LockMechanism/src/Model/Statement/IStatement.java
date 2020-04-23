package Model.Statement;

import Model.ADT.IDictionary;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Type.Type;

public interface IStatement {
    ProgramState execute (ProgramState state) throws ToyException;
    IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv);
    IStatement deepCopy();
}

// TODO: Print type environment