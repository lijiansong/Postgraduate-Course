package expr;

import org.antlr.runtime.ANTLRStringStream;
import org.antlr.runtime.CommonTokenStream;



public class Test {
	public static void main(String[] args) throws Exception {

		String[] testStr = { 
				"2",
				"a + b + 3",
				"(a - b) + 3",
				"a + (b * 3",							     	
		};

		for (String s : testStr) {
			System.out.println("Input expr: " + s);
			run(s);
		}

	}
	
	public static void run(String expr) throws Exception {
		ANTLRStringStream in = new ANTLRStringStream(expr);
        //词法分析器
		ExprLexer lexer = new ExprLexer(in);

		CommonTokenStream tokens = new CommonTokenStream(lexer);
        //语法分析器 
		ExprParser parser = new ExprParser(tokens);

		parser.prog();		
	}
}
