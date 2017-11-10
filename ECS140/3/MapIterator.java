public class MapIterator extends SequenceIterator {
    private Map point;
    
    public MapIterator() {
        point = new Map();
    }
    
    public void Set( Map p ) {
        point = p;
    }

    public boolean equal (MapIterator other) {
        return (point == other.point);
    }
    
    public MapIterator advance() {
        this.Set(point.rest());
        return this;
    }
    
    public Pair get() {
        return point.first();
    }
    
    public Map getp() {
        return point;
    }
}