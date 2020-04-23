package Model.ADT;

import javax.annotation.processing.Generated;
import java.util.HashMap;
import java.util.Map;

public class GenericDictionary<T, V> implements IDictionary <T, V> {
    private HashMap<T,V> dictionary;

    public GenericDictionary() {
        dictionary = new HashMap<T,V>();
    }

    public GenericDictionary(HashMap<T,V> map) {
        dictionary = map;
    }

    @Override
    public Boolean containsKey(T key) {
        return dictionary.containsKey(key);
    }

    // TODO: take care of exceptions (getValue returns NULL bla bla)
    @Override
    public V getValue(T key) {
        return dictionary.get(key);
    }

    @Override
    public void insert(T key, V value) {
        dictionary.put(key, value);
    }

    @Override
    public void update(T key, V value) {
        dictionary.put(key, value);
    }

    @Override
    public void remove(T key) {
        dictionary.remove(key);
    }

    @Override
    public Map<T, V> getContent() {
        return dictionary;
    }

    @Override
    public IDictionary<T, V> deepCopy() {
        return new GenericDictionary((HashMap<T,V>) this.dictionary.clone());
    }

    @Override
    public String toString() {
        StringBuilder info = new StringBuilder();
        for (T key : dictionary.keySet()){
            info.append(key.toString()).append(" --> ").append(dictionary.get(key).toString()).append("\n");
        }
        return info.toString();
    }
}
