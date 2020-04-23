package Model.Statement;

import Model.ADT.IDictionary;
import Model.Exception.ToyException;
import Model.Expression.Exp;
import Model.ProgramState.ProgramState;
import Model.Type.IntType;
import Model.Type.StringType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.StringValue;
import Model.Value.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFile implements IStatement{
    private Exp expression;
    private String variableName;

    public ReadFile(Exp e, String varName){
        expression = e;
        variableName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        IDictionary<String, Value> symbolTable = state.getSymbolTable();
        Value expressionValue = expression.evaluate(state.getSymbolTable(), state.getHeap());

        if (expressionValue.getType().equals(new StringType())){
            if (fileTable.containsKey((StringValue)expressionValue)){
                if (symbolTable.containsKey(variableName)) {
                    if (symbolTable.getValue(variableName).getType().equals(new IntType())) {
                        StringValue filePath = (StringValue) expressionValue;
                        BufferedReader fileDescriptor = fileTable.getValue(filePath);
                        try {
                            String line = fileDescriptor.readLine();
                            if (line == null){
                                int number = 0;
                                IntValue varValue = new IntValue(number);
                                symbolTable.update(variableName, varValue);
                            }
                            else {
                                int number = Integer.parseInt(line);
                                IntValue varValue = new IntValue(number);
                                symbolTable.update(variableName, varValue);

                            }
                        }
                        catch (IOException | NumberFormatException io){
                            System.out.println(io.getMessage());
                        }
                    }
                    else throw new ToyException("Variable not int type");
                }
                else throw new ToyException("Variable not declared");
            }
            else throw new ToyException("File not opened");
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

    @Override
    public String toString() {
        return "readFile("+expression.toString()+", "+variableName+")";
    }

    @Override
    public IStatement deepCopy() {
        return new ReadFile(expression, variableName);
    }
}
