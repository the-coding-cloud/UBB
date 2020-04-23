package Model.ADT;

import Model.Value.Value;

import java.util.LinkedList;
import java.util.List;

public class GenericList <T> implements IList <T> {
    private LinkedList<T> list;

    public GenericList(){
        list = new LinkedList<T>();
    }

    @Override
    public void add(T elem){
        list.add(elem);
    }

    @Override
    public List<T> getList() {
        return list;
    }

    @Override
    public String toString() {
        StringBuilder info = new StringBuilder();

        for (T elem : list) {
            info.append(elem.toString()).append("\n");
        }
        return info.toString();
    }
}
