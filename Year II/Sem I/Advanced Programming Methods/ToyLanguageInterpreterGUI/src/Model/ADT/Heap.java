package Model.ADT;

import Model.Value.Value;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class Heap implements IHeap {
    private HashMap<Integer, Value> heap;
    private AtomicInteger key;

    public Heap() {
        heap = new HashMap<Integer, Value>();
        // TODO: take care of the synchronization
        key = new AtomicInteger(0);
    }

    @Override
    public Boolean containsKey(Integer key) {
        return heap.containsKey(key);
    }

    @Override
    public Value getValue(Integer key) {
        return heap.get(key);
    }

    @Override
    public Integer insert(Value value) {
        int address = key.incrementAndGet();
        heap.put(address, value);
        return address;
    }

    @Override
    public void update(Integer key, Value value) {
        heap.put(key, value);
    }

    @Override
    public void remove(Integer key) {
        heap.remove(key);
    }

    @Override
    public void setContent(Map<Integer, Value> newHeap) {
        heap.clear();
        for (Integer key: newHeap.keySet()) {
            heap.put(key, newHeap.get(key));
        }
    }

    @Override
    public Map<Integer, Value> getContent() {
        return heap;
    }

    @Override
    public String toString() {
        StringBuilder info = new StringBuilder();
        for (Integer key : heap.keySet()){
            info.append(key.toString()).append(" --> ").append(heap.get(key).toString()).append("\n");
        }
        return info.toString();
    }
}
