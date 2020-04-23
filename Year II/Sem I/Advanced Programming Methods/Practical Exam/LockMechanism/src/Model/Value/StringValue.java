package Model.Value;

import Model.Type.StringType;
import Model.Type.Type;

public class StringValue implements Value {
    private String value;

    public StringValue(String val){
        value = val;
    }

    @Override
    public String toString() {
        return value;
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    public String getValue() {
        return value;
    }

    @Override
    public Value deepCopy() {
        return new StringValue(value);
    }


}
