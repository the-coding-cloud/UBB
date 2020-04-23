package Model.ADT;

import java.util.LinkedList;

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
    public String toString() {
        StringBuilder info = new StringBuilder();

        for (T elem : list) {
            info.append(elem.toString()).append("\n");
        }
        return info.toString();
    }
}
