package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.IStack;
import Model.Exception.ToyException;
import Model.Expression.Exp;
import Model.ProgramState.ProgramState;
import Model.Type.BoolType;
import Model.Type.Type;
import Model.Value.BoolValue;
import Model.Value.Value;

public class WhileStatement implements IStatement {
    private Exp expression;
    private IStatement statement;

    public WhileStatement(Exp e, IStatement s){
        expression = e;
        statement = s;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IStack<IStatement> stack = state.getExeStack();
        IDictionary<String, Value> symbolTable = state.getSymbolTable();

        if(expression.evaluate(symbolTable, state.getHeap()).getType().equals(new BoolType()))
        {
            BoolValue condition = (BoolValue) expression.evaluate(symbolTable, state.getHeap());
            if(condition.getValue()) {
                stack.push(new WhileStatement(expression, statement));
                stack.push(statement);
            }
        }
        else
            throw new ToyException("Expression does not evaluate to a bool value");

        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        Type expType = expression.typeCheck(typeEnv);
        if (expType.equals(new BoolType())) {
            statement.typeCheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new ToyException("While statement condition is not boolean");
    }

    @Override
    public String toString() {
        return "( while(" + expression.toString() + ")" + statement.toString() + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(expression, statement);
    }
}
