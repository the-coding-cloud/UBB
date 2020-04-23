package Model.Value;

import Model.Type.RefType;
import Model.Type.Type;

public class RefValue implements Value{
    Integer address;
    Type locationType;

    public RefValue(Type locType, int addr){
        address = addr;
        locationType = locType;
    }

    public void setAddress(Integer address) {
        this.address = address;
    }

    @Override
    public String toString() {
        return "(" + Integer.toString(address) + ", " + locationType.toString() + ")";
    }

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    public Integer getAddress() {
        return address;
    }

    @Override
    public Value deepCopy() {
        return new RefValue(locationType.deepCopy(), address);
    }
}
