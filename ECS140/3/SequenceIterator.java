public class SequenceIterator {
//1. advance to advance a SequenceIterator to the next element in a Sequence object.
//2. get to return the object to which the SequenceIterator object points.
//3. equal to determine if two SequenceIterator objects point to the same element.
//The interface of the SequenceIterator class may look like the following:
    private Sequence point;
    
    public SequenceIterator() {
        point = new Sequence();
    }
    
    public void Set( Sequence p ) {
        point = p;
    }

    public boolean equal (SequenceIterator other) {
        return (point == other.point);
    }
    
    public SequenceIterator advance() {
        this.Set(point.rest());
        return this;
    }
    
    public Element get() {
        return point.first();
    }

//The following code fragment shows a possible usage of the iterator:
//Sequence seq;
//SequenceIterator it;
//for (it = seq.begin(); !it.equal(seq.end()); it.advance()) {
//(it.get()).f();
//}
//The above applies method f over all elements of seq.
}