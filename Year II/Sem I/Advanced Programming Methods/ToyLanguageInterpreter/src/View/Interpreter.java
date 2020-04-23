package View;

import Controlller.Controller;
import Model.ADT.*;
import Model.Exception.ToyException;
import Model.Expression.*;
import Model.ProgramState.ProgramState;
import Model.Statement.*;
import Model.Type.*;
import Model.Value.BoolValue;
import Model.Value.IntValue;
import Model.Value.StringValue;
import Model.Value.Value;
import Repository.IRepository;
import Repository.Repository;

import java.io.BufferedReader;

class Interpreter {
    public static void main(String[] args) {
        IRepository repo1 = new Repository("log1.txt");
        IStack<IStatement> stk1 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict1 = new GenericDictionary<String, Value>();
        IList<Value> list1 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft1 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h1 = new Heap();
        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(2))), new PrintStatement(new VarExp("v"))));
        ex1.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg1 = new ProgramState(stk1, dict1, list1, ft1, h1, ex1);
        repo1.addProgramState(prg1);
        Controller ctr1 = new Controller(repo1);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo2 = new Repository("log2.txt");
        IStack<IStatement> stk2 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict2 = new GenericDictionary<String, Value>();
        IList<Value> list2 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft2 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h2 = new Heap();
        IStatement ex2 = new CompStatement(new VarDeclStatement("a", new IntType()),
                new CompStatement(new VarDeclStatement("b", new IntType()),
                        new CompStatement(new AssignStatement("a", new ArithmExp(1, new ValueExp(new IntValue(2)),
                                new ArithmExp(3, new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStatement(new AssignStatement("b", new ArithmExp(1, new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStatement(new VarExp("b"))))));
        ex2.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg2 = new ProgramState(stk2, dict2, list2, ft2, h2, ex2);
        repo2.addProgramState(prg2);
        Controller ctr2 = new Controller(repo2);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo3 = new Repository("log3.txt");
        IStack<IStatement> stk3 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict3 = new GenericDictionary<String, Value>();
        IList<Value> list3 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft3 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h3 = new Heap();
        IStatement ex3 = new CompStatement(new VarDeclStatement("a", new BoolType()), new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new AssignStatement("a", new ValueExp(new BoolValue(true))), new CompStatement(new IfStatement(new VarExp("a"),
                        new AssignStatement("v", new ValueExp(new IntValue(2))), new AssignStatement("v", new ValueExp(new IntValue(3)))),
                        new PrintStatement(new VarExp("v"))))));
        ex3.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg3 = new ProgramState(stk3, dict3, list3, ft3, h3, ex3);
        repo3.addProgramState(prg3);
        Controller ctr3 = new Controller(repo3);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo4 = new Repository("log4.txt");
        IStack<IStatement> stk4 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict4 = new GenericDictionary<String, Value>();
        IList<Value> list4 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft4 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h4 = new Heap();
        IStatement ex4 = new CompStatement(new VarDeclStatement("varf", new StringType()),
                new CompStatement(new AssignStatement("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStatement(new OpenRFile(new VarExp("varf")),
                                new CompStatement(new VarDeclStatement("varc", new IntType()),
                                        new CompStatement(new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStatement(new PrintStatement(new VarExp("varc")),
                                                        new CompStatement(new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStatement(new PrintStatement(new VarExp("varc")), new CloseFile(new VarExp("varf"))))))))));
        ex4.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg4 = new ProgramState(stk4, dict4, list4, ft4, h4, ex4);
        repo4.addProgramState(prg4);
        Controller ctr4 = new Controller(repo4);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo5 = new Repository("log5.txt");
        IStack<IStatement> stk5 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict5 = new GenericDictionary<String, Value>();
        IList<Value> list5 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft5 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h5 = new Heap();
        IStatement ex5 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new NewStatement("v", new ValueExp(new IntValue(20))),
                        new CompStatement(new PrintStatement(new ReadHeap(new VarExp("v"))),
                                new CompStatement(new WriteHeapStatement("v", new ValueExp(new IntValue(30))),
                                        new PrintStatement(new ArithmExp(1, new ReadHeap(new VarExp("v")), new ValueExp(new IntValue(30))))))));
        ex5.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg5 = new ProgramState(stk5, dict5, list5, ft5, h5, ex5);
        repo5.addProgramState(prg5);
        Controller ctr5 = new Controller(repo5);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo6 = new Repository("log6.txt");
        IStack<IStatement> stk6 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict6 = new GenericDictionary<String, Value>();
        IList<Value> list6 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft6 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h6 = new Heap();
        IStatement ex6 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new NewStatement("v", new ValueExp(new IntValue(20))),
                        new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                new CompStatement(new NewStatement("a", new VarExp("v")),
                                        new CompStatement(new NewStatement("v", new ValueExp(new IntValue(30))),
                                                new CompStatement(new PrintStatement(new ReadHeap(new ReadHeap(new VarExp("a")))),
                                                        new NewStatement("v", new ValueExp(new IntValue(40)))))))));
        ex6.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg6 = new ProgramState(stk6, dict6, list6, ft6, h6, ex6);
        repo6.addProgramState(prg6);
        Controller ctr6 = new Controller(repo6);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo7 = new Repository("log7.txt");
        IStack<IStatement> stk7 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict7 = new GenericDictionary<String, Value>();
        IList<Value> list7 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft7 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h7 = new Heap();
        IStatement ex7 = new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(3))),
                        new CompStatement(new WhileStatement(new RelationalExp(5, new VarExp("v"), new ValueExp(new IntValue(0))), new CompStatement(new PrintStatement(new VarExp("v")), new AssignStatement("v", new ArithmExp(2, new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStatement(new VarExp("v")))));
        ex7.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg7 = new ProgramState(stk7, dict7, list7, ft7, h7, ex7);
        repo7.addProgramState(prg7);
        Controller ctr7 = new Controller(repo7);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo8 = new Repository("log8.txt");
        IStack<IStatement> stk8 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict8 = new GenericDictionary<String, Value>();
        IList<Value> list8 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft8 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h8 = new Heap();
        IStatement ex8 = new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new VarDeclStatement("a", new RefType(new IntType())),
                        new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(10))),
                                new CompStatement(new NewStatement("a", new ValueExp(new IntValue(22))),
                                    new CompStatement(new ForkStatement(new CompStatement(new WriteHeapStatement("a", new ValueExp(new IntValue(30))), new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(32))), new CompStatement(new PrintStatement(new VarExp("v")), new PrintStatement(new ReadHeap(new VarExp("a"))))))),
                                        new CompStatement(new PrintStatement(new VarExp("v")), new PrintStatement(new ReadHeap(new VarExp("a")))))))));
        ex8.typeCheck(new GenericDictionary<String, Type>());
        ProgramState prg8 = new ProgramState(stk8, dict8, list8, ft8, h8, ex8);
        repo8.addProgramState(prg8);
        Controller ctr8 = new Controller(repo8);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IRepository repo9 = new Repository("log9.txt");
        IStack<IStatement> stk9 = new GenericStack<IStatement>();
        IDictionary<String, Value> dict9 = new GenericDictionary<String, Value>();
        IList<Value> list9 = new GenericList<Value>();
        IDictionary<StringValue, BufferedReader> ft9 = new GenericDictionary<StringValue, BufferedReader>();
        IHeap h9 = new Heap();
        IStatement ex9 = new CompStatement(new VarDeclStatement("a", new StringType()),
                new CompStatement(new VarDeclStatement("b", new IntType()),
                        new CompStatement(new AssignStatement("a", new ArithmExp(1, new ValueExp(new IntValue(2)),
                                new ArithmExp(3, new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStatement(new AssignStatement("b", new ArithmExp(1, new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStatement(new VarExp("b"))))));
        try {
            ex9.typeCheck(new GenericDictionary<String, Type>());
        }
        catch(ToyException e){
            System.out.println( "Error at statement 9: " + e.getMessage());
        }


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
        menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
        menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
        menu.addCommand(new RunExample("4", ex4.toString(), ctr4));
        menu.addCommand(new RunExample("5", ex5.toString(), ctr5));
        menu.addCommand(new RunExample("6", ex6.toString(), ctr6));
        menu.addCommand(new RunExample("7", ex7.toString(), ctr7));
        menu.addCommand(new RunExample("8", ex8.toString(), ctr8));
        menu.show();
    }
}
