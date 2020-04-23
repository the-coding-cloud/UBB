package Model.Statement;

import Model.ADT.IDictionary;
import Model.Exception.ToyException;
import Model.Expression.Exp;
import Model.ProgramState.ProgramState;
import Model.Type.StringType;
import Model.Type.Type;
import Model.Value.StringValue;
import Model.Value.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class CloseFile implements IStatement {
    private Exp expression;

    public CloseFile(Exp e){
        expression = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable() ;
        Value val = expression.evaluate(state.getSymbolTable(), state.getHeap());

        if (val.getType().equals(new StringType())){
            if (fileTable.containsKey((StringValue)val)) {
                try {
                    StringValue filePath = (StringValue) val;
                    BufferedReader fileDescriptor = fileTable.getValue(filePath);
                    fileDescriptor.close();

                    fileTable.remove(filePath);
                }

                catch (IOException io){
                    System.out.println(io.getMessage());
                }
            }
            else throw new ToyException("Non-existent file");
        }
        else throw new ToyException("Expression value not StringType");

        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        Type expType = expression.typeCheck(typeEnv);

        if(expType.equals(new StringType()))
            return typeEnv;
        else throw new ToyException("Expression not StringType");
    }
    // TODO MODIFY TO THROW EXCEPTION

    @Override
    public String toString() {
        return "closeFile(" + expression.toString() + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new CloseFile(expression);
    }
}

