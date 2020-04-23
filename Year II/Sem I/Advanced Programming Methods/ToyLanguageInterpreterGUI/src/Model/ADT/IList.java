package Model.ADT;

import Model.Value.Value;

import java.util.List;

public interface IList <T> {
    void add(T elem);
    List<T> getList();
}
