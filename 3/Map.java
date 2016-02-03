public class Map extends Sequence {
    private Pair pair;
    private Map node;
    
//First set elm and node as null, which will also be the end of sequence
    public Map() {
        pair = null;
        node = null;
    }
    
//Define method first to return the first element of the sequence:
    public Pair first() {
        return pair;
    }

//Define a method rest that returns the rest of the elements of the seqence:
    public Map rest() {
        return node;
    }
//Note that rest does not create a new sequence. It merely points to the rest of the elements of the
//original sequence.

//Define a method add to add an element at a specified position:
    public void add(Pair inval) {
        Map temp = this;
        Map temptwo = new Map();
        
        if (temp.pair == null) {
            temp.pair = inval;
        }else {
            while(temp.node !=null && temp.first().Getkey().Get()<=inval.Getkey().Get()) {
                temp = temp.node;
            }

            if(temp.node == null && temp.first().Getkey().Get()<=inval.Getkey().Get()){
                temptwo.pair = inval;
                temp.node = temptwo;
            }else {
                temptwo.pair = temp.pair;
                temp.pair = inval;
                temptwo.node = temp.node;
                temp.node = temptwo;
            }
        }
    }
//If an element already exists at pos, elm is inserted at pos. All elements starting at location pos are
//pushed to the right. If pos is not between 0 and the length of the Sequence object, flag an error
//and exit.

    public MapIterator find(MyChar key){
        MapIterator temp = begin();
		while (temp.getp() != null && temp.get().Getkey().Get() != key.Get()){
			temp.advance();
		}
		return temp;
    }

    public void Print() {
        System.out.print("[ ");
        Map temp = this;
        while (temp != null) {
            System.out.print("('"+(temp.pair).Getkey().Get()+"' ");
            (temp.pair).Getelm().Print();
            System.out.print(") ");
            temp = temp.node;
        }
        System.out.print("]");
    }
    
//Method begin returns a SequenceIterator object that points to the first element of the sequence.
	public MapIterator begin(){
        MapIterator si = new MapIterator();
        si.Set(this);
        return si;
	}
	
//Method end, on the other hand, returns a SequenceIterator object that points to a special value after the
//last element of a Sequence object.
	public MapIterator end(){
        MapIterator si = new MapIterator();
        Map temp = this;
        while(temp.node != null) {
            temp = temp.node;
        }
        si.Set(temp.node);
        return si;
	}
}