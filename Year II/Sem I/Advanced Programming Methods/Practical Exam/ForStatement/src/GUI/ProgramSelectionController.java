package GUI;

import Controller.Controller;
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
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;

import java.io.BufferedReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

public class ProgramSelectionController implements Initializable {
    private List<IStatement> programStatements;
    private ProgramExecutionController programExecutionWindowController;
    @FXML
    private Button executeButton;
    @FXML
    private ListView<String> programList;

    private void generateStatements() {
        programStatements = new ArrayList<>();

        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(2))), new PrintStatement(new VarExp("v"))));
        IDictionary<String, Type> typeEnv = ex1.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex1);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex2 = new CompStatement(new VarDeclStatement("a", new IntType()),
                new CompStatement(new VarDeclStatement("b", new IntType()),
                        new CompStatement(new AssignStatement("a", new ArithmExp(1, new ValueExp(new IntValue(2)),
                                new ArithmExp(3, new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStatement(new AssignStatement("b", new ArithmExp(1, new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStatement(new VarExp("b"))))));
        typeEnv = ex2.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex2);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex3 = new CompStatement(new VarDeclStatement("a", new BoolType()), new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new AssignStatement("a", new ValueExp(new BoolValue(true))), new CompStatement(new IfStatement(new VarExp("a"),
                        new AssignStatement("v", new ValueExp(new IntValue(2))), new AssignStatement("v", new ValueExp(new IntValue(3)))),
                        new PrintStatement(new VarExp("v"))))));
        typeEnv = ex3.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex3);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex4 = new CompStatement(new VarDeclStatement("varf", new StringType()),
                new CompStatement(new AssignStatement("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStatement(new OpenRFile(new VarExp("varf")),
                                new CompStatement(new VarDeclStatement("varc", new IntType()),
                                        new CompStatement(new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStatement(new PrintStatement(new VarExp("varc")),
                                                        new CompStatement(new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStatement(new PrintStatement(new VarExp("varc")), new CloseFile(new VarExp("varf"))))))))));
        typeEnv = ex4.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex4);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex5 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new NewStatement("v", new ValueExp(new IntValue(20))),
                        new CompStatement(new PrintStatement(new ReadHeap(new VarExp("v"))),
                                new CompStatement(new WriteHeapStatement("v", new ValueExp(new IntValue(30))),
                                        new PrintStatement(new ArithmExp(1, new ReadHeap(new VarExp("v")), new ValueExp(new IntValue(30))))))));
        typeEnv = ex5.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex5);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex6 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new NewStatement("v", new ValueExp(new IntValue(20))),
                        new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                new CompStatement(new NewStatement("a", new VarExp("v")),
                                        new CompStatement(new NewStatement("v", new ValueExp(new IntValue(30))),
                                                new CompStatement(new PrintStatement(new ReadHeap(new ReadHeap(new VarExp("a")))),
                                                        new NewStatement("v", new ValueExp(new IntValue(40)))))))));
        typeEnv = ex6.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex6);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex7 = new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(3))),
                        new CompStatement(new WhileStatement(new RelationalExp(5, new VarExp("v"), new ValueExp(new IntValue(0))), new CompStatement(new PrintStatement(new VarExp("v")), new AssignStatement("v", new ArithmExp(2, new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStatement(new VarExp("v")))));
        typeEnv = ex7.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex7);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex8 = new CompStatement(new VarDeclStatement("v", new IntType()),
                new CompStatement(new VarDeclStatement("a", new RefType(new IntType())),
                        new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(10))),
                                new CompStatement(new NewStatement("a", new ValueExp(new IntValue(22))),
                                        new CompStatement(new ForkStatement(new CompStatement(new WriteHeapStatement("a", new ValueExp(new IntValue(30))), new CompStatement(new AssignStatement("v", new ValueExp(new IntValue(32))), new CompStatement(new PrintStatement(new VarExp("v")), new PrintStatement(new ReadHeap(new VarExp("a"))))))),
                                                new CompStatement(new PrintStatement(new VarExp("v")), new PrintStatement(new ReadHeap(new VarExp("a")))))))));
        typeEnv = ex8.typeCheck(new GenericDictionary<String, Type>());
        System.out.println(typeEnv.toString());
        programStatements.add(ex8);

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex9 = new CompStatement(new VarDeclStatement("a", new StringType()),
                new CompStatement(new VarDeclStatement("b", new IntType()),
                        new CompStatement(new AssignStatement("a", new ArithmExp(1, new ValueExp(new IntValue(2)),
                                new ArithmExp(3, new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStatement(new AssignStatement("b", new ArithmExp(1, new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStatement(new VarExp("b"))))));
        try {
            ex9.typeCheck(new GenericDictionary<String, Type>());
            programStatements.add(ex9);
        }
        catch(ToyException e){
            System.out.println( "TypeCheck error at statement 9: " + e.getMessage());
        }

        // -------------------------------------------------------------------------------------------------------------------------------//

        IStatement ex10 = new CompStatement(new VarDeclStatement("a", new RefType(new IntType())),
                new CompStatement(new NewStatement("a", new ValueExp(new IntValue(20))),
                        new CompStatement(new ForStatement("v", new ValueExp(new IntValue(0)), new ValueExp(new IntValue(3)), new ArithmExp(1, new VarExp("v"), new ValueExp(new IntValue(1))),
                                new ForkStatement(new CompStatement(new PrintStatement(new VarExp("v")), new AssignStatement("v", new ArithmExp(3, new VarExp("v"), new ReadHeap(new VarExp("a"))))))),
                        new PrintStatement(new ReadHeap(new VarExp("a"))))));

        ex10.typeCheck(new GenericDictionary<String, Type>());
        programStatements.add(ex10);

    }

    private List<String> getStatementStrings() {
        return programStatements.stream().map(IStatement::toString).collect(Collectors.toList());
    }

    private Controller generateController(int statementIndex){

        IRepository repo = new Repository("log" + (statementIndex+1) + ".txt");
        IStack<IStatement> exeStack = new GenericStack<>();
        IDictionary<String, Value> symTable = new GenericDictionary<>();
        IList<Value> output = new GenericList<>();
        IDictionary<StringValue, BufferedReader> fileTable = new GenericDictionary<>();
        IHeap heap = new Heap();
        ProgramState program = new ProgramState(exeStack, symTable, output, fileTable, heap, programStatements.get(statementIndex));
        repo.addProgramState(program);

        return new Controller(repo);
    }

    public void setProgramExecutionWindowController(ProgramExecutionController controller) {
        programExecutionWindowController = controller;
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        generateStatements();
        programList.setItems(FXCollections.observableArrayList(getStatementStrings()));

        executeButton.setOnAction(actionEvent -> {
            int index = programList.getSelectionModel().getSelectedIndex();

            if (index < 0) {
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Warning");
                alert.setHeaderText("You have not selected any program to execute");
                alert.showAndWait();
            }
            else
                programExecutionWindowController.setProgramController(generateController(index));
        });
    }


}
