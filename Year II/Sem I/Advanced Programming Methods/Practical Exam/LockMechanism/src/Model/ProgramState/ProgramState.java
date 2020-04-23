package Model.ProgramState;

import Model.ADT.*;
import Model.Exception.ToyException;
import Model.Statement.IStatement;
import Model.Value.StringValue;
import Model.Value.Value;
import java.io.BufferedReader;

public class ProgramState {
    private IStack<IStatement> exeStack;
    private IDictionary<String, Value> symbolTable;
    private IList<Value> output;
    private IDictionary<StringValue, BufferedReader> fileTable;
    private IHeap heap;
    private ILockTable lockTable;
    private IStatement originalProgram;
    private int processID;
    private static int currentID = 0;

    public ProgramState(IStack<IStatement> stack, IDictionary<String, Value> symTable, IList<Value> out, IDictionary<StringValue, BufferedReader> fileT, IHeap h, ILockTable locktbl, IStatement program){
        exeStack = stack;
        symbolTable = symTable;
        output = out;
        fileTable = fileT;
        heap = h;
        lockTable = locktbl;
        originalProgram = program.deepCopy();
        processID = setCurrentID();
        stack.push(program);
    }

    public ProgramState(IStatement statement) {
        exeStack = new GenericStack<IStatement>();
        symbolTable = new GenericDictionary<String, Value>();
        output = new GenericList<Value>();
        fileTable = new GenericDictionary<StringValue, BufferedReader>();
        heap = new Heap();
        lockTable = new LockTable();
        originalProgram = statement.deepCopy();
        processID = setCurrentID();
        exeStack.push(statement);
    }

    synchronized private static int setCurrentID(){
        currentID = currentID+1;
        return currentID;
    }

    public ProgramState oneStepExecution() throws ToyException{
        if(exeStack.isEmpty())
            throw new ToyException("Program state stack is empty");

        IStatement currentStatement = exeStack.pop();
        return currentStatement.execute(this);
    }

    public boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }

    public void setOriginalProgram(IStatement originalProgram) {
        this.originalProgram = originalProgram;
    }

    public void setExeStack(IStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }

    public void setSymbolTable(IDictionary<String, Value> symbolTable) {
        this.symbolTable = symbolTable;
    }

    public void setOutput(IList<Value> output) {
        this.output = output;
    }

    public void setFileTable(IDictionary<StringValue, BufferedReader> fileTable) {
        this.fileTable = fileTable;
    }

    public void setHeap(IHeap heap) {
        this.heap = heap;
    }

    public IStatement getOriginalProgram() {
        return originalProgram;
    }

    public IStack<IStatement> getExeStack() {
        return exeStack;
    }

    public IDictionary<String, Value> getSymbolTable() {
        return symbolTable;
    }

    public IList<Value> getOutput() {
        return output;
    }

    public IDictionary<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public IHeap getHeap() {
        return heap;
    }

    public ILockTable getLockTable() {
        return lockTable;
    }

    public int getProcessID() {
        return processID;
    }

    @Override
    public String toString() {
         return  "------------------------------------------------------\n" +
                 "--- Thread ID: " + this.processID + " ---\n" +
                 "--- Execution Stack ---\n" +
                 exeStack.toString() + "\n" +
                 "--- Symbol Table ---\n" +
                 symbolTable.toString() + "\n" +
                 "--- Output List ---\n" +
                 output.toString() + "\n" +
                 "--- File Table ---\n" +
                 fileTable.toString() + "\n" +
                 "--- Heap ---\n" +
                 heap.toString() + "\n" +
                "------------------------------------------------------\n\n";
    }

}

