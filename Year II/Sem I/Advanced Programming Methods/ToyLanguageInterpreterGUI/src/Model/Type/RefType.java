package Model.Type;

import Model.Value.RefValue;
import Model.Value.Value;

public class RefType implements Type {
    private Type innerType;

    public RefType(Type inner){ innerType = inner; }


    public Type getInnerType() {
        return innerType;
    }

    @Override
    public String toString() {
        return "Ref(" + innerType.toString() + ")";
    }

    @Override
    public boolean equals(Object another) {
        if (another instanceof RefType)
            return  innerType.equals(((RefType) another).getInnerType());
        else
            return false;
    }

    @Override
    public Value getDefaultValue() {
        return new RefValue(innerType, 0);
    }

    @Override
    public Type deepCopy() {
        return new RefType(innerType.deepCopy());
    }
}
