package Model.Value;

import Model.Type.IntType;
import Model.Type.Type;

public class IntValue implements Value {
    private int value;

    public IntValue(int val){
        value = val;
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }

    @Override
    public Type getType() {
        return (Type) new IntType();
    }

    public int getValue() {
        return value;
    }

    public Value deepCopy(){
        return new IntValue(value);
    }
}
