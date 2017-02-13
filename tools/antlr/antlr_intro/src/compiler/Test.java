package compiler;

import org.antlr.runtime.ANTLRStringStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.CommonTreeNodeStream;



public class Test {
	public static void main(String[] args) throws Exception {

		String[] testStr = { 
				"2",
				"a + b + 3",
				"(a - b) + 3",
				"(a - (b * 2)) + 3",			
				"(a - 1) * a"			
		};

		for (String s : testStr) {
			System.out.println("Input expr: " + s);
			run(s);
			System.out.println();
		}

	}
	
	public static void run(String expr) throws Exception {
		ANTLRStringStream in = new ANTLRStringStream(expr);
        //´Ê·¨·ÖÎöÆ÷
		ExprLexer lexer = new ExprLexer(in);

		CommonTokenStream tokens = new CommonTokenStream(lexer);
        //Óï·¨·ÖÎöÆ÷ 
		ExprParser parser = new ExprParser(tokens);


		ExprParser.prog_return ret = parser.prog();
		CommonTree t = (CommonTree)ret.getTree();
		
		CommonTreeNodeStream nodes = new CommonTreeNodeStream(t);
		nodes.setTokenStream(tokens);		
        //±àÒëÆ÷
		Compiler c_walker = new Compiler(nodes);
		c_walker.prog();
	}
}
