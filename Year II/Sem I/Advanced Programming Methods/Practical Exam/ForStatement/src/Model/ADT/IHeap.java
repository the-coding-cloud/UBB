package Model.ADT;

import Model.Value.Value;

import java.util.Map;

public interface IHeap {
    Boolean containsKey(Integer key);
    Value getValue(Integer key);
    Integer insert(Value value);
    void update(Integer key, Value value);
    void remove(Integer key);
    void setContent(Map<Integer, Value> newHeap);
    Map<Integer, Value> getContent();
}
