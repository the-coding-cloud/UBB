package Model.Statement;

import Model.ADT.IDictionary;
import Model.ADT.IStack;
import Model.Exception.ToyException;
import Model.Expression.Exp;
import Model.Expression.RelationalExp;
import Model.Expression.VarExp;
import Model.ProgramState.ProgramState;
import Model.Type.IntType;
import Model.Type.Type;

public class ForStatement implements IStatement {
    private String ID;
    private Exp expression1;
    private Exp expression2;
    private Exp expression3;
    private IStatement statement;

    public ForStatement(String varID, Exp e1, Exp e2, Exp e3, IStatement s){
        ID = varID;
        expression1 = e1;
        expression2 = e2;
        expression3 = e3;
        statement = s;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyException {
        IStack<IStatement> stack = state.getExeStack();
        //IDictionary<String, Value> symbolTable = state.getSymbolTable();

        IStatement forStatement = new CompStatement(new VarDeclStatement(ID, new IntType()),
                new CompStatement(new AssignStatement(ID, expression1), new WhileStatement(new RelationalExp(1, new VarExp(ID), expression2), new CompStatement(statement, new AssignStatement(ID, expression3)))));

        stack.push(forStatement);
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) {
        typeEnv.insert(ID,new IntType());

        Type exp1Type = expression1.typeCheck(typeEnv);
        Type exp2Type = expression2.typeCheck(typeEnv);
        Type exp3Type = expression3.typeCheck(typeEnv);

        if (exp1Type.equals(new IntType())) {
            if (exp2Type.equals(new IntType())) {
                if (exp3Type.equals(new IntType())) {
                    statement.typeCheck(typeEnv.deepCopy());
                    return typeEnv;
                }
                else throw new ToyException("Exp 3 not int");
            }
            else
                throw new ToyException("Exp 2 not int");
        }
        else
            throw new ToyException("Exp 1 not int");

        //TODO: add type of v to the typechecker environment --- DONE
    }

    @Override
    public String toString() {
        return "for(" + ID + "=" + expression1.toString() + ";" + ID + "<" + expression2.toString() + ";" + ID + "=" + expression3.toString() + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new ForStatement(ID, expression1, expression2, expression3, statement);
    }
}
