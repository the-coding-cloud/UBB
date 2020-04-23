package Model.Value;

import Model.Type.BoolType;
import Model.Type.Type;

public class BoolValue implements Value {
    private Boolean value;

    public BoolValue(Boolean val){
        value = val;
    }

    @Override
    public String toString() {
        if (value)
            return "TRUE";
        else
            return "FALSE";
    }

    @Override
    public Type getType() {
        return (Type) new BoolType();
    }

    public Boolean getValue(){
        return value;
    }

    public Value deepCopy(){
        return new BoolValue(value);
    }
}
