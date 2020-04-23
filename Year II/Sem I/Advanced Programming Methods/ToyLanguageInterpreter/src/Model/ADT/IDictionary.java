package Model.ADT;

import java.util.Map;

public interface IDictionary <T, V> {
    Boolean containsKey(T key);
    V getValue(T key);
    void insert(T key, V value);
    void update(T key, V value);
    void remove(T key);
    Map<T,V> getContent();
    IDictionary<T,V> deepCopy();
}
