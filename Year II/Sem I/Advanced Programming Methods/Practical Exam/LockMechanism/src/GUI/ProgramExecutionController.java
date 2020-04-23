package GUI;

import Controller.Controller;
import Model.ProgramState.ProgramState;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.util.Pair;

import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

public class ProgramExecutionController implements Initializable {
    private Controller controller;

    @FXML
    private TextField programStateNumber;
    @FXML
    private TableView<Pair<String, String>> heapTableView;
    @FXML
    private TableColumn<Pair<String, String>, String> heapAddressColumn;
    @FXML
    private TableColumn<Pair<String, String>, String> heapValueColumn;
    @FXML
    private TableView<Pair<String, String>> lockTableView;
    @FXML
    private TableColumn<Pair<String, String>, String> lockAddressColumn;
    @FXML
    private TableColumn<Pair<String, String>, String> lockValueColumn;
    @FXML
    private ListView<String> fileListView;
    @FXML
    private TableView<Pair<String, String>> symbolTableView;
    @FXML
    private TableColumn<Pair<String, String>, String> symbolTableVariableColumn;
    @FXML
    private TableColumn<Pair<String, String>, String> symbolTableValueColumn;
    @FXML
    private ListView<String> outputListView;
    @FXML
    private ListView<Integer> programStateIDListView;
    @FXML
    private ListView<String> executionStackListView;
    @FXML
    private Button executeOneStepButton;

    public void setProgramController(Controller controller) {
        this.controller = controller;
        updateProgramStateID();
        updateProgramStateNumber();

        if (controller.getProgramStateIDs().size() == 1)
            updateExecutionStack(controller.getProgramByIndex(0));
        else
            executionStackListView.getItems().clear();

        symbolTableView.getItems().clear();
        outputListView.getItems().clear();
        heapTableView.getItems().clear();
        fileListView.getItems().clear();

    }

    private void executeOneStep() {
        if (!controller.finishedExecution())
                controller.oneStepExecution();
        else {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Message");
            alert.setHeaderText("Already finished execution");

            alert.showAndWait();
        }

    }

    private void updateProgramStateID() {
        programStateIDListView.setItems(FXCollections.observableList(controller.getProgramStateIDs()));
    }

    private void updateProgramStateNumber() {
        programStateNumber.setText(String.valueOf(controller.getProgramStateIDs().size()));
    }

    private void updateOutput() {
        outputListView.setItems(FXCollections.observableList(controller.getStringOutput()));
    }

    private void updateFileTable() {
        fileListView.setItems(FXCollections.observableList(controller.getStringFileTable()));
    }

    private void updateHeap() {
        List<Pair<String, String>> heapList = controller.getHeap().getContent().entrySet().stream().map(p -> new Pair<String, String>(Integer.toString(p.getKey()), p.getValue().toString())).collect(Collectors.toList());
        heapTableView.setItems(FXCollections.observableList(heapList));
    }

    private void updateExecutionStack(ProgramState selectedProgram) {
        executionStackListView.setItems(FXCollections.observableList(selectedProgram.getExeStack().getStackContents().stream().map(Object::toString).collect(Collectors.toList())));
    }

    private void updateSymbolTable(ProgramState selectedProgram) {
        List<Pair<String, String>> symbolTableList = selectedProgram.getSymbolTable().getContent().entrySet().stream().map(p -> new Pair<String, String>(p.getKey(), p.getValue().toString())).collect(Collectors.toList());
        symbolTableView.setItems(FXCollections.observableList(symbolTableList));
    }

    //TODO TODO TODO TODO
    private void updateLockTable() {
        List<Pair<String, String>> lockTableList = controller.getLockTable().getContent().entrySet().stream().map(p -> new Pair<String, String>(Integer.toString(p.getKey()), p.getValue().toString())).collect(Collectors.toList());
        lockTableView.setItems(FXCollections.observableList(lockTableList));
    }

    private ProgramState getSelectedProgram() {
        int currentIndex = programStateIDListView.getSelectionModel().getSelectedIndex();
        return controller.getProgramByIndex(currentIndex);
    }


    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        heapAddressColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getKey()));
        heapValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue()));

        lockAddressColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getKey()));
        lockValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue()));

        symbolTableVariableColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getKey()));
        symbolTableValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue()));

        executeOneStepButton.setOnAction(actionEvent -> {
            if (controller == null) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("ERROR");
                alert.setHeaderText("No program was selected");

                alert.showAndWait();
            }
            else {
                executeOneStep();
                updateProgramStateNumber();
                updateProgramStateID();
                updateFileTable();
                updateOutput();
                updateHeap();
                updateLockTable();
                executionStackListView.getItems().clear();
                symbolTableView.getItems().clear();

                if (controller.getProgramStateIDs().size() == 1){
                    updateExecutionStack(controller.getProgramByIndex(0));
                    updateSymbolTable(controller.getProgramByIndex(0));
                }
            }
        });

        programStateIDListView.setOnMouseClicked(actionEvent -> {
            ProgramState selectedProgram = getSelectedProgram();
            if (selectedProgram != null) {
                updateExecutionStack(selectedProgram);
                updateSymbolTable(selectedProgram);
            }

            else
            {
                executionStackListView.getItems().clear();
                symbolTableView.getItems().clear();
            }
        });
    }
}
