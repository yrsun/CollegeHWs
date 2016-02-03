public class Sequence extends Element {
    private Element element;
    private Sequence node;
    
//First set elm and node as null, which will also be the end of sequence
    public Sequence() {
        element = null;
        node = null;
    }
    
    
    
//Define method first to return the first element of the sequence:
    public Element first() {
        return element;
    }

//Define a method rest that returns the rest of the elements of the seqence:
    public Sequence rest() {
        return node;
    }
//Note that rest does not create a new sequence. It merely points to the rest of the elements of the
//original sequence.

//Define a method length to return the number of elements in a Sequence object:
    public int length() {
        int l = 0;
        Sequence tempnode = this;
        while (tempnode != null) {
            tempnode = tempnode.node;
            l++;
        }
        return l;
    }

//Define a method add to add an element at a specified position:
    public void add(Element elm, int pos) {
        int len = length();
        
        if ( (pos < 0) || (pos > len) ) {
            System.err.println("pos should between 0 and the length of the Sequence.");
            System.exit(1);
        }
        
        Sequence temp = this;
        Sequence temptwo = new Sequence();
        
        if (temp.element == null) {
            temp.element = elm;
        }else if ( pos == len ) {
            for (int i = 1; i < pos; i++) {
                temp = temp.node;
            }
            temp.node = temptwo;
            temptwo.element = elm;
        }else {
            if (pos == 0){
                temptwo.element = temp.element;
                temp.element = elm;
                temptwo.node = temp.node;
                temp.node = temptwo;
            }else {
                for (int i = 1; i < pos; i++) {
                    temp = temp.node;
                }
                temptwo.node = temp.node;
                temptwo.element = elm;
                temp.node = temptwo;
            }
        }
    }
//If an element already exists at pos, elm is inserted at pos. All elements starting at location pos are
//pushed to the right. If pos is not between 0 and the length of the Sequence object, flag an error
//and exit.

//Define a delete method to remove an element at a specified position:
    public void delete(int pos) {
        Sequence temp = this;
        Sequence temptwo = new Sequence();

        if (pos == 0){
            temptwo = temp.node;
            temp.node = temptwo.node;
            temp.element = temptwo.element;
        }else {
            for (int i = 1; i < pos; i++) {
                temp = temp.node;
            }
            temptwo = temp.node;
            temptwo = temptwo.node;
            temp.node = temptwo;
        }
    }
//After deleting the element at pos, all elements to the right of pos are pushed to the left. If there are
//no elements at pos, the Sequence object remains unchanged.

    public void Print() {
        System.out.print("[ ");
        Sequence temp = this;
        while (temp != null) {
            temp.element.Print();
            System.out.print(" ");
            temp = temp.node;
        }
        System.out.print("]");
    }
    
//1. index to access the element at a particular position:
    public Element index(int pos) {
        int len = length();
        if ( (pos < 0) || (pos >= len) ) {
            System.err.println("pos should between 0 and the length of the Sequence.");
            System.exit(1);
        }
        
        Sequence temp = this;
        for (int i = 0; i < pos; i++) {
            temp = temp.node;
        }
        
        return temp.element;
    }
//The method index is used to access a particular element of a Sequence object. For instance,
//S.index(0) returns the first element of S. If pos is not between 0 and the length of the Sequence
//object, flag an error and exit.

//2. flatten to flatten a sequence:
    public Sequence flatten() {
        Sequence temp = this;
        Sequence temptwo = new Sequence();
        int pos = 0;
        while (temp != null) {
            if (temp.element instanceof Sequence) {
                Sequence inside = ((Sequence)temp.element).flatten();
                while (inside != null) {
                    temptwo.add(inside.element, pos);
                    inside = inside.node;
                    pos++;
                }
                temp = temp.node;
            }else {
                temptwo.add(temp.element, pos);
                temp = temp.node;
                pos++;
            }
        }
        return temptwo;
    }
//An example usage of flatten is shown below:

//Note that flatten returns a new Sequence object.

//3. copy to perform a deep copy of a Sequence object:
    public Sequence copy() {
        Sequence temp = this;
        Sequence temptwo = new Sequence();
        int pos = 0;
        
        while (temp != null) {
            if (temp.element instanceof Sequence) {
                Element inside = ((Sequence)temp.element).copy();
                temptwo.add(inside, pos);
                temp = temp.node;
                pos++;

            }else {
                if (temp.element instanceof MyChar) {
                    MyChar c = new MyChar();
                    c.Set(((MyChar)temp.element).Get());
                    temptwo.add(c, pos);
                }else {
                    MyInteger i = new MyInteger();
                    i.Set(((MyInteger)temp.element).Get());
                    temptwo.add(i, pos);
                }
                temp = temp.node;
                pos++;
            }
        }
        return temptwo;
    }
    
//Method begin returns a SequenceIterator object that points to the first element of the sequence.
	public SequenceIterator begin(){
        SequenceIterator si = new SequenceIterator();
        si.Set(this);
        return si;
	}
	
//Method end, on the other hand, returns a SequenceIterator object that points to a special value after the
//last element of a Sequence object.
	public SequenceIterator end(){
        SequenceIterator si = new SequenceIterator();
        Sequence temp = this;
        while(temp.node != null) {
            temp = temp.node;
        }
        si.Set(temp.node);
        return si;
	}
}