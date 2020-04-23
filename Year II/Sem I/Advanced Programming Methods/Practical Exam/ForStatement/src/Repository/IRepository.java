package Repository;

import Model.ProgramState.ProgramState;

import java.util.List;

public interface IRepository {
    List<ProgramState> getProgramList();
    void setProgramList(List<ProgramState> programList);
    void addProgramState(ProgramState program);
    void logProgramStateExecution(ProgramState state);
}
// TODO: logProgramStateExecution ---THROWS TOYEXCEPTION ---