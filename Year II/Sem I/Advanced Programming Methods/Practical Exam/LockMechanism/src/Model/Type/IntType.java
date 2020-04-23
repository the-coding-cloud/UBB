package Model.Type;

import Model.Value.IntValue;
import Model.Value.Value;

public class IntType implements Type{

    @Override
    public Value getDefaultValue() {
        return new IntValue(0);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof IntType;
    }

    @Override
    public String toString() {
        return "int";
    }

    @Override
    public Type deepCopy() {
        return new IntType();
    }
}
