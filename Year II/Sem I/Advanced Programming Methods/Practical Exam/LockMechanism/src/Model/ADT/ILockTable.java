package Model.ADT;

import java.util.Map;

public interface ILockTable {
    Boolean containsKey(Integer key);
    Integer getValue(Integer key);
    Integer insert(Integer i);
    void update(Integer key, Integer value);
    Map<Integer, Integer> getContent();
}
