package Repository;

import Model.ProgramState.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class Repository implements IRepository {
    private String logFilePath;
    private List<ProgramState> programStateList;

    public Repository(String filePath) {
            programStateList = new LinkedList<>();
            logFilePath = filePath;
        }

    @Override
    public List<ProgramState> getProgramList() {
        return programStateList;
    }

    @Override
    public void setProgramList(List<ProgramState> programList) {
        programStateList = programList;
    }

    @Override
    public void addProgramState(ProgramState program) {
        programStateList.add(program);
    }

    @Override
    public void logProgramStateExecution(ProgramState state) {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.print(state.toString());
            logFile.close();
        }
        catch (IOException io){
            System.out.println(io.getMessage());
        }
    }

}
