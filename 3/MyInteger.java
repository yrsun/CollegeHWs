public class MyInteger extends Element {
    private int i;
    public MyInteger() { i = 0; }
    public int Get() { return i; }
    public void Set(int val) { i = val; }
    public void Print() { System.out.print(i); }
}