package antlr_test;


import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

/**
 * Created by json-lee on 17-6-2.
 */
public class Test {
    public static void run(String expr) throws Exception{
        ANTLRInputStream inputStream=new ANTLRInputStream(expr);
        ArrayInitLexer lexer=new ArrayInitLexer(inputStream);
        CommonTokenStream tokens=new CommonTokenStream(lexer);
        ArrayInitParser parser=new ArrayInitParser(tokens);
        ParseTree tree=parser.init();
        System.out.println(tree.toStringTree(parser));
    }
    public static void main(String[] args) throws Exception{
//        ANTLRInputStream inputStream=new ANTLRInputStream(System.in);
//        ArrayInitLexer lexer=new ArrayInitLexer(inputStream);
//        CommonTokenStream tokens=new CommonTokenStream(lexer);
//        ArrayInitParser parser=new ArrayInitParser(tokens);
//        ParseTree tree=parser.init();
//        System.out.println(tree.toStringTree(parser));
        String []testStr={
                "{99,3,123}",
                "{1,{2,3},4}"};
        for(String str:testStr){
            System.out.println("expr: "+str);
            run(str);
        }

    }
}
