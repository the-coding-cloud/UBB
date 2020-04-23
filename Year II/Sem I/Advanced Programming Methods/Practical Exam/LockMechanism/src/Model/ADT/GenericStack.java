package Model.ADT;

import java.util.*;

public class GenericStack <T> implements IStack <T> {
    private Stack<T> stack;

    public GenericStack(){
        stack = new Stack<T>();
    }

    public T pop(){
        return stack.pop();
    }

    public void push(T elem){
        stack.push(elem);
    }

    @Override
    public Boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public List<T> getStackContents() {
        List<T> stackContents = new ArrayList<T>(stack);
        Collections.reverse(stackContents);
        return stackContents;
    }

    @Override
    public String toString() {
        return stack.toString();
    }
}
