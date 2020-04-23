package Model.Statement;

import Model.ADT.*;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Type.Type;
import Model.Value.StringValue;
import Model.Value.Value;

import java.io.BufferedReader;

public class ForkStatement implements IStatement {
    IStatement statement;

    public ForkStatement(IStatement statement){
        this.statement = statement;
    }
    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IDictionary<String, Value> symbolTable = state.getSymbolTable().deepCopy();
        IStack<IStatement> exeStack = new GenericStack<IStatement>();
        IList<Value> output = state.getOutput();
        IHeap heap = state.getHeap();
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();

        return new ProgramState(exeStack, symbolTable, output, fileTable, heap, statement);
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        return statement.typeCheck(typeEnv);
     }

    @Override
    public String toString() {
        return "fork(" + statement.toString() + ")";
    }

    @Override
    public IStatement deepCopy() {
        return null;
    }
}
