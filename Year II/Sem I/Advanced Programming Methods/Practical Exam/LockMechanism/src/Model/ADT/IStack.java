package Model.ADT;

import java.util.List;

public interface IStack <T> {
    T pop();
    void push(T value);
    Boolean isEmpty();
    List<T> getStackContents();
}
