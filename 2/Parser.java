
public class Parser {


    // tok is global to all these parsing methods;
    // scan just calls the scanner's scan method and saves the result in tok.
    private Token tok; // the current token
    public int cblock; // the current block
    //private Stack<Integer> block_number = new Stack<Integer> ();
    public int SAsize = 5;
    public String Array[][] = new String[SAsize][SAsize];
    
    private void initial_Array() {; //Initial the 2d string-type array
        for(int i = 0; i < SAsize; i++){
            for(int j = 0; j < SAsize; j++){
                Array[i][j] = "\0";
           }
        }
    }
    

    private void increase_array() { //Double the array size
        SAsize = SAsize*2;
        String temp[][] = new String[SAsize][SAsize];
        for(int i = 0; i < SAsize; i++){ //First initial the temp array
            for(int j = 0; j < SAsize; j++){
                temp[i][j] = "\0";
            }
        }
        for(int i = (0); i < (SAsize/2); i++){ //Copy the Temp to Array
            for(int j = 0; j < (SAsize/2); j++){
                temp[i][j] = Array[i][j] ;
            }
        }
        Array = temp; //Reference Array to temp
    }
    

    private void clearblock() { //reset the list of declarations to empty before leave a particular block
        int b = cblock;
        for(int i = 0; i < SAsize; i++){
            Array[b][i] = "\0";
        }
    }

    
    private void scan() {
        tok = scanner.scan();
    }


    private Scan scanner;
        Parser(Scan scanner) {
        this.scanner = scanner;
        scan();
        program();
        if( tok.kind != TK.EOF )
            parse_error("junk after logical end of program");
    }


    private void ccode(String s) {
        System.out.print(s);
    }


    private void program() {
        ccode("#include <stdio.h>\n");
        ccode("int main() {\n");
        cblock = -1;
        initial_Array();
        block();
        ccode("return 0; }\n");
    }


    private void block(){
        cblock++; //First time enter block, cblock will be 0
        declaration_list();
        statement_list();
        clearblock();
        cblock--; //before exit each block
    }


    private void declaration_list() {
    // below checks whether tok is in first set of declaration.
    // here, that's easy since there's only one token kind in the set.
    // in other places, though, there might be more.
    // so, you might want to write a general function to handle that.
        while( is(TK.DECLARE) ) {  //@, DECLARE
            declaration();
        }
    }


    private void declaration() {
        int b = cblock;
        int flag = -1;
        mustbe(TK.DECLARE);

        
        if( is(TK.ID)) { //if is ID, start check ID
            ccode("int ");
            if(Array[b][0] != "\0"){ 
                for (int i = 0; i < SAsize; i++){
                    if(Array[b][i] == "\0"){ //Store
                        ccode("x_");
                        ccode(tok.string);
                        ccode(Integer.toString(cblock));
                        Array[b][i] = tok.string;
                        break;
                    }else if((Array[b][i]).equals(tok.string)){ //redeclarationed
                        
                        System.err.println("redeclaration of variable "+tok.string);
                        
                        flag = 0;
                        break;
                    }else if((i+1)==SAsize && !(Array[b][i]).equals(tok.string)) {
                        increase_array();
                        ccode("x_");
                        ccode(tok.string);
                        ccode(Integer.toString(cblock));
                        Array[b][i+1] = tok.string;
                        break;
                    }
                }    
            }else { //Store
                ccode("x_");
                ccode(tok.string);
                ccode(Integer.toString(cblock));
                Array[b][0] = tok.string;  
            }
        }
        mustbe(TK.ID);
        while( is(TK.COMMA) ) { //next declaration(s)
            scan();
            if( is(TK.ID)) { //if is ID, start check ID
                for (int i = 0; i < SAsize; i++){
                    if(Array[b][i] == "\0"){ //Store
                        if(flag != 0 ){
                            ccode(",");
                        }
                        ccode("x_");
                        ccode(tok.string);
                        ccode(Integer.toString(cblock));
                        Array[b][i] = tok.string;
                        break;
                    }else if((Array[b][i]).equals(tok.string)){ //redeclarationed
                        
                        System.err.println("redeclaration of variable "+tok.string);
                        
                        break;
                    }else if((i+1)==SAsize && !(Array[b][i]).equals(tok.string)) {
                        increase_array();
                        if(flag != 0 ){
                            ccode(",");
                        }
                        ccode("x_");
                        ccode(tok.string);
                        ccode(Integer.toString(cblock));
                        Array[b][i+1] = tok.string;
                        break;
                    }
                }    
            }

            mustbe(TK.ID);
        }
        ccode(";\n");
    }


    private void statement_list() {
        while( is(TK.PRINT) || is(TK.DO) || is(TK.IF) || is(TK.ID) || is(TK.TILDE) || is(TK.LFOR)){  
            statement();
        }
    }

    
    private void statement() {
        if( is(TK.PRINT) ) {  //!, PRINT    
            s_print();
        }else if( is(TK.DO) ) {  //<, DO
            s_do();
        }else if( is(TK.IF) ) {  //[, IF
            s_if();
        }else if( is(TK.ID) || is(TK.TILDE) ) {
            s_assignment();
        }else if( is(TK.LFOR) ) {
            s_for();
        }
    }

    
    private void s_assignment() {
        ref_id();
        mustbe(TK.ASSIGN); //=
        ccode(" = ");
        expr();
        ccode(";\n");
    }

    
    private void ref_id() { //reference
        int b = cblock;
        int n = -1;
        int flag = -1;
        int tflag = -1;
        int rC = 0;
        if( is(TK.TILDE)){ //have ~

            n = 0;
            scan();
            if( is(TK.NUM)){
                tflag=0;
                n = Integer.parseInt(tok.string);
                if(n > b){
                    scan();
                    System.err.println("no such variable ~"+n+tok.string+" on line "+tok.lineNumber);
                    System.exit(1);
                }
                scan();
            }else { //exists the global declaration rC=0
                for(int i = 0; i <SAsize; i++){ 
                    if((Array[0][i]).equals(tok.string)){
                       flag = 0; 
                    }else if(Array[0][i] == "\0"){
                        break;
                    }
                }
                if(flag != 0){
                    System.err.println("no such variable ~"+tok.string+" on line "+tok.lineNumber);
                    System.exit(1);
                }
            }
        }
        if( is(TK.ID)) { //check ID
            if(n >= 0) { //check ~ references
                if(tflag == 0){
                    rC = cblock - n;
                }else{
                    rC = 0;
                }
                for(int i = 0; i <SAsize; i++){
                    if((Array[b-n][i]).equals(tok.string)){
                       flag = 0; 
                    }else if(Array[b-n][i] == "\0"){
                        break;
                    }
                }
                if(flag != 0){
                    System.err.println("no such variable ~"+n+tok.string+" on line "+tok.lineNumber);
                    System.exit(1);
                }
            }else {
                for(int c = b; c >= 0; c--){
                    for(int i = 0; i <SAsize; i++){
                        if((Array[c][i]).equals(tok.string)){
                            if((c)>(rC)){
                                rC = c;
                            }
                            flag = 0; 
                            break;
                        }else if(Array[c][i] == "\0"){
                            break;
                        }
                    }
                }
                if(flag != 0){
                    System.err.println(tok.string+" is an undeclared variable on line "+tok.lineNumber);
                    System.exit(1);
                }
            }
        }
        ccode(" x_");
        ccode(tok.string);
        ccode(Integer.toString(rC));
        ccode(" ");
        mustbe(TK.ID);
    }

    
    private void expr() {
        term();
        while( is(TK.PLUS) || is(TK.MINUS) ) {
            ccode(tok.string);
            scan();
            term();
        }
    }

    
    private void term() {
        factor();
        while( is(TK.TIMES) || is(TK.DIVIDE) ) {
            ccode(tok.string);
            scan();
            factor();
        }
    }

    
    private void factor() {
        if( is(TK.LPAREN)) {
            ccode(" ( ");
            scan();
            expr();
            mustbe(TK.RPAREN);
            ccode(" ) ");
        }else if( is(TK.NUM)){
            ccode(tok.string);
            scan();
        }else {
            ref_id();
        }
    }

    
    private void guarded_command() {
        ccode("( 0 >= (");
        expr();
        ccode(")){\n");
        mustbe(TK.THEN);
        block();
        ccode("\n}\n");
    }

    
    private void s_print() {
        mustbe(TK.PRINT);
        ccode("printf(\"%d\\n\",");
        expr();
        ccode(");\n");
    }

    
    private void s_do() {
        mustbe(TK.DO);
        ccode("while");
        guarded_command();
        mustbe(TK.ENDDO);
    }

//for::= '{' number ',' number ',' block '}' // 
    private void s_for() {
        mustbe(TK.LFOR);
        int start=0, end=0;
        ccode("int index; for(");
        if(is(TK.NUM)){
            ccode("index = ");
            ccode(tok.string);
            ccode(";");
            start = Integer.parseInt(tok.string);
            scan();
        }
        mustbe(TK.COMMA);
        if(is(TK.NUM)){
            end = Integer.parseInt(tok.string);
            if(start < end){
                ccode("index <= ");
                ccode(tok.string);
                ccode("; index++) {\n");
            }else {
                ccode("index >= ");
                ccode(tok.string);
                ccode("; index--) {\n");
            }
            scan();
        }
        mustbe(TK.COMMA);
        block();
        ccode("\n}\n");
        mustbe(TK.RFOR);
    }
    
    
    private void s_if() {
        mustbe(TK.IF);
        ccode("if");
        guarded_command();
        while( is(TK.ELSEIF) ) {
            ccode("else if");
            scan();
            guarded_command();
        }
        if( is(TK.ELSE)) {
            ccode("else");
            scan();
            ccode(" { ");
            block();
            ccode("\n}\n");
        }
        mustbe(TK.ENDIF);
    }
    
    

    // is current token what we want?
    private boolean is(TK tk) {
        return tk == tok.kind;
    }

    // ensure current token is tk and skip over it.
    private void mustbe(TK tk) {
    if( tok.kind != tk ) {
        System.err.println( "mustbe: want " + tk + ", got " +
                    tok);
        parse_error( "missing token (mustbe)" );
    }
    scan();
    }

    private void parse_error(String msg) {
    System.err.println( "can't parse: line "
                + tok.lineNumber + " " + msg );
    System.exit(1);
    }
}