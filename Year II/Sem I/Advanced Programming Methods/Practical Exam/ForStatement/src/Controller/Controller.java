package Controller;

import Model.ADT.IHeap;
import Model.Exception.ToyException;
import Model.ProgramState.ProgramState;
import Model.Value.RefValue;
import Model.Value.Value;
import Repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private IRepository programStateRepo;
    private ExecutorService executor;

    public Controller(IRepository repo){
        programStateRepo = repo;
    }

    private Map<Integer, Value> safeGarbageCollector(List<Integer> symbolTableAddresses, Map<Integer, Value> heap)
    {
        return heap.entrySet()
                .stream()
                .filter(e->symbolTableAddresses.contains(e.getKey()))
                .collect(Collectors.toConcurrentMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private List<Integer> getSymbolTableAddresses(Collection<Value> symTableValues, Collection<Value> heap)
    {
        return  Stream.concat(
                heap.stream()
                        .filter(v -> v instanceof RefValue)
                        .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddress();}),
                symTableValues.stream()
                        .filter(v-> v instanceof RefValue)
                        .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddress();})
        )
                .collect(Collectors.toList());
    }

    private List<ProgramState> removeCompletedPrg(List<ProgramState> prgList) {
        return prgList.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public List<Integer> getProgramStateIDs(){
        return programStateRepo.getProgramList().stream().map(ProgramState::getProcessID).collect(Collectors.toList());
    }

    public List<String> getStringOutput(){
        return programStateRepo.getProgramList().get(0).getOutput().getList().stream().map(Object::toString).collect(Collectors.toList());
    }

    public List<String> getStringFileTable(){
        return programStateRepo.getProgramList().get(0).getFileTable().getContent().keySet().stream().map(Object::toString).collect(Collectors.toList());
    }

    public IHeap getHeap() {
        return programStateRepo.getProgramList().get(0).getHeap();
    }

    public ProgramState getProgramByIndex(int index){
        return programStateRepo.getProgramList().get(index);
    }

    public boolean finishedExecution(){
        return removeCompletedPrg(programStateRepo.getProgramList()).size() == 0;
    }

    private void oneStepForAllPrograms(List<ProgramState> programStateList) {
        //before the execution, print the PrgState List into the log file

        //RUN concurrently one step for each of the existing PrgStates
        //-----------------------------------------------------------------------
        //prepare the list of callables

        List<Callable<ProgramState>> callList = programStateList.stream()
                .map((ProgramState p) -> (Callable<ProgramState>)(p::oneStepExecution))
                .collect(Collectors.toList());

        //start the execution of the callables
        //it returns the list of new created PrgStates (namely threads)

        try {
            List<ProgramState> newPrgList = executor.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        }
                        catch (ToyException | InterruptedException | ExecutionException sce) {
                            System.out.println(sce.getMessage());
                            throw new ToyException("Something went wrong during future.get..");
                        }
                    }).filter(Objects::nonNull).collect(Collectors.toList());

            programStateList.addAll(newPrgList);

            programStateRepo.setProgramList(programStateList);

            programStateList.forEach(prg ->programStateRepo.logProgramStateExecution(prg));
        }
        catch(InterruptedException ie){
            throw new ToyException(ie.getMessage());
        }
    }

    public void oneStepExecution(){
        executor = Executors.newFixedThreadPool(2);

        List<ProgramState> prgList = removeCompletedPrg(programStateRepo.getProgramList());

        oneStepForAllPrograms(prgList);

        Collection<Value> allSymTbl = new ArrayList<>();
        prgList.forEach(v-> allSymTbl.addAll(v.getSymbolTable().getContent().values()));
        List<Integer> symTableAddresses = getSymbolTableAddresses(allSymTbl, prgList.get(0).getHeap().getContent().values());
        Map<Integer, Value> newHeap = safeGarbageCollector(symTableAddresses, prgList.get(0).getHeap().getContent());
        prgList.get(0).getHeap().setContent(newHeap);

        //HERE you can call conservativeGarbageCollector

        //prgList.forEach(prg -> programStateRepo.logProgramStateExecution(prg));
        //prgList.forEach(System.out::println);

        executor.shutdownNow();
        //HERE the repository still contains at least one Completed Prg
        // and its List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        //setPrgList of repository in order to change the repository

        // update the repository state
        programStateRepo.setProgramList(prgList);
    }

}

