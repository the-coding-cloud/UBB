package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.IList;
import Model.Exception.ToyException;
import Model.Expression.Exp;
import Model.ProgramState.ProgramState;
import Model.Type.Type;
import Model.Value.Value;

public class PrintStatement implements IStatement {
    private Exp expression;

    public PrintStatement(Exp exp){
        expression = exp;
    }

    public String toString() {
        return "Print "  + expression.toString();
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IList<Value> out = state.getOutput();
        out.add(expression.evaluate(state.getSymbolTable(), state.getHeap()));
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {

        expression.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(expression.deepCopy());
    }
}
