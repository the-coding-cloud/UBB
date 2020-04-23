package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.IStack;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Type.Type;

public class CompStatement implements IStatement{
    private IStatement firstStmt;
    private IStatement secondStmt;

    public CompStatement(IStatement first, IStatement second){
        firstStmt = first;
        secondStmt = second;
    }

    public String toString(){
        return firstStmt.toString() + "; " + secondStmt.toString();
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException{
        IStack<IStatement> stk = state.getExeStack();
        stk.push(secondStmt);
        stk.push(firstStmt);
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        return secondStmt.typeCheck(firstStmt.typeCheck(typeEnv));
    }

    @Override
    public IStatement deepCopy() {
        return new CompStatement(firstStmt.deepCopy(), secondStmt.deepCopy());
    }
}
