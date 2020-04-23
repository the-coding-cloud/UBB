package View;

import Controlller.Controller;

public class RunExample extends Command {
    private Controller ctr;

    RunExample(String key, String desc, Controller ctr){
        super(key, desc);
        this.ctr=ctr;
    }

    @Override
    public void execute() {
        try{
            ctr.allStepExecution();
        }
        catch (Exception e) {
            System.out.println();
        } //TODO here you must treat the exceptions that can not be solved in the controller
    }
}

