public class Pair extends Element {
    private MyChar key;
    private Element element;
    
    public Pair (MyChar k, Element elm) {
        key = k;
        element = elm;
    }
    
    public MyChar Getkey() {
        return key;
    }
    
    public Element Getelm() {
        return element;
    }
    
    public void Print() {
        System.out.print("(");
        key.Print();
        System.out.print(" ");
        element.Print();
        System.out.print(")");
    }
}