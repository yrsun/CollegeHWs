public class Matrix extends Sequence {
    private int row;
    private int col;
    
// constructor for creating a matrix of specific number of rows and columns
    public Matrix(int rowsize, int colsize) {
        row = rowsize;
        col = colsize;
        for (int i=0; i<(row*col); i++) {
            MyInteger newint = new MyInteger();
            this.add(newint, i);
        }
    }

    public void Set(int rowsize, int colsize, int value) {
        int pos = rowsize*col + colsize;
        ((MyInteger)this.index(pos)).Set(value);
    } // set the value of an element
    
    public int Get(int rowsize, int colsize) {
        int value;
        int pos = rowsize*col + colsize;
        value = ((MyInteger)this.index(pos)).Get();
        return value;
    } // get the value of an element
    
    public Matrix Sum(Matrix mat) {
        Matrix temp = new Matrix(row, col);
        int a, b;
        for(int i=0; i<row; i++) {
            for(int j=0; j<col; j++) {
                a = this.Get(i,j);
                b = mat.Get(i,j);
                temp.Set(i,j,a+b);
            }
        }
        return temp;
    } // return the sum of two matrices: mat & this
    
    public Matrix Product(Matrix mat) {
        if(this.col != mat.row) {
            System.out.println("Matrix dimensions incompatible for Product");
            System.exit(1);
        }
        
        Matrix temp = new Matrix(this.row, mat.col);
         
        for(int i=0; i<this.row; i++) {
            for(int j=0; j<mat.col; j++) {
                int a=0;
                for(int k=0; k<this.col; k++) {
                    a = a+(this.Get(i,k))*(mat.Get(k,j));
                }
                temp.Set(i,j,a);
            }
        }
        return temp;
    } // return the product of two matrices: mat & this
    
    public void Print() {
        for (int i=0; i<row; i++) {
            System.out.print("[ ");
            for(int j=0; j<col; j++) {
                System.out.print(this.Get(i,j)+" ");
            }
            System.out.println("]");
        }
    } // print the elements of matrix
}








