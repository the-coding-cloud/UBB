package Model.ADT;

import Model.Value.Value;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class LockTable implements ILockTable{
    private ConcurrentHashMap<Integer, Integer> lockTable;
    private AtomicInteger key;

    public LockTable() {
        lockTable = new ConcurrentHashMap<Integer, Integer>();
        // TODO: take care of the synchronization
        key = new AtomicInteger(0);
    }

    @Override
    public Boolean containsKey(Integer key) {
        return lockTable.containsKey(key);
    }

    @Override
    public Integer getValue(Integer key) {
        return lockTable.get(key);
    }

    @Override
    public Integer insert(Integer i) {
        int address = key.incrementAndGet();
        lockTable.put(address, i);
        return address;
    }

    @Override
    public void update(Integer key, Integer value) {
        lockTable.put(key, value);
    }

    @Override
    public Map<Integer, Integer> getContent() {
        return lockTable;
    }

    @Override
    public String toString() {
        StringBuilder info = new StringBuilder();
        for (Integer key : lockTable.keySet()){
            info.append(key.toString()).append(" --> ").append(lockTable.get(key).toString()).append("\n");
        }
        return info.toString();
    }

}
