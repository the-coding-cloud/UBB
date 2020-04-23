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

public class IfStatement implements IStatement {
    private Exp expression;
    private IStatement thenS;
    private IStatement elseS;

    public IfStatement(Exp exp, IStatement t, IStatement e){
        expression = exp;
        thenS = t;
        elseS = e;
    }

    @Override
    public String toString() {
        return "if (" + expression.toString() + ") then (" + thenS.toString() + ") else (" + elseS.toString() + ")";
    }

   public ProgramState execute(ProgramState state) throws ToyException{
        IStack<IStatement> stack = state.getExeStack();
        IDictionary<String, Value> symbolTable = state.getSymbolTable();

        Value condition = expression.evaluate(symbolTable, state.getHeap());

        if (condition.getType().equals(new BoolType())){
            BoolValue cond = (BoolValue) condition;

            if (cond.getValue())
                stack.push(thenS);
            else
                stack.push(elseS);
        }

        else throw new ToyException("Conditional expression is not a boolean");

        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        Type expType = expression.typeCheck(typeEnv);
        if (expType.equals(new BoolType())) {
            thenS.typeCheck(typeEnv.deepCopy());
            elseS.typeCheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new ToyException("Condition of IF not of type bool");
    }

    @Override
    public IStatement deepCopy() {
        return new IfStatement(expression.deepCopy(), thenS.deepCopy(), elseS.deepCopy());
    }
}
