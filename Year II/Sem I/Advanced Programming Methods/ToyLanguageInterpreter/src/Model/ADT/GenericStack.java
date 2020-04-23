package Model.ADT;

import java.util.Stack;

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
    public String toString() {
        return stack.toString();
    }
}
