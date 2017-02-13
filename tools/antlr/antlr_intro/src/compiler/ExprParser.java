// $ANTLR 3.2 Sep 23, 2009 12:02:23 E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g 2010-12-23 10:51:24
package compiler;

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;


import org.antlr.runtime.tree.*;

public class ExprParser extends Parser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "PROG", "STAT", "NUM", "VAR", "INT", "ID", "NEWLINE", "WS", "'+'", "'-'", "'*'", "'/'", "'('", "')'"
    };
    public static final int VAR=7;
    public static final int T__12=12;
    public static final int STAT=5;
    public static final int T__17=17;
    public static final int INT=8;
    public static final int WS=11;
    public static final int EOF=-1;
    public static final int T__13=13;
    public static final int NUM=6;
    public static final int T__16=16;
    public static final int T__14=14;
    public static final int PROG=4;
    public static final int T__15=15;
    public static final int NEWLINE=10;
    public static final int ID=9;

    // delegates
    // delegators


        public ExprParser(TokenStream input) {
            this(input, new RecognizerSharedState());
        }
        public ExprParser(TokenStream input, RecognizerSharedState state) {
            super(input, state);
             
        }
        
    protected TreeAdaptor adaptor = new CommonTreeAdaptor();

    public void setTreeAdaptor(TreeAdaptor adaptor) {
        this.adaptor = adaptor;
    }
    public TreeAdaptor getTreeAdaptor() {
        return adaptor;
    }

    public String[] getTokenNames() { return ExprParser.tokenNames; }
    public String getGrammarFileName() { return "E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g"; }


    public static class prog_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "prog"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:15:1: prog : stat -> ^( PROG stat ) ;
    public final ExprParser.prog_return prog() throws RecognitionException {
        ExprParser.prog_return retval = new ExprParser.prog_return();
        retval.start = input.LT(1);

        CommonTree root_0 = null;

        ExprParser.stat_return stat1 = null;


        RewriteRuleSubtreeStream stream_stat=new RewriteRuleSubtreeStream(adaptor,"rule stat");
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:15:6: ( stat -> ^( PROG stat ) )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:15:8: stat
            {
            pushFollow(FOLLOW_stat_in_prog62);
            stat1=stat();

            state._fsp--;

            stream_stat.add(stat1.getTree());


            // AST REWRITE
            // elements: stat
            // token labels: 
            // rule labels: retval
            // token list labels: 
            // rule list labels: 
            // wildcard labels: 
            retval.tree = root_0;
            RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

            root_0 = (CommonTree)adaptor.nil();
            // 15:13: -> ^( PROG stat )
            {
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:15:16: ^( PROG stat )
                {
                CommonTree root_1 = (CommonTree)adaptor.nil();
                root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(PROG, "PROG"), root_1);

                adaptor.addChild(root_1, stream_stat.nextTree());

                adaptor.addChild(root_0, root_1);
                }

            }

            retval.tree = root_0;
            }

            retval.stop = input.LT(-1);

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (CommonTree)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }
        finally {
        }
        return retval;
    }
    // $ANTLR end "prog"

    public static class stat_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "stat"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:17:1: stat : expr EOF -> ^( STAT expr ) ;
    public final ExprParser.stat_return stat() throws RecognitionException {
        ExprParser.stat_return retval = new ExprParser.stat_return();
        retval.start = input.LT(1);

        CommonTree root_0 = null;

        Token EOF3=null;
        ExprParser.expr_return expr2 = null;


        CommonTree EOF3_tree=null;
        RewriteRuleTokenStream stream_EOF=new RewriteRuleTokenStream(adaptor,"token EOF");
        RewriteRuleSubtreeStream stream_expr=new RewriteRuleSubtreeStream(adaptor,"rule expr");
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:17:6: ( expr EOF -> ^( STAT expr ) )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:17:8: expr EOF
            {
            pushFollow(FOLLOW_expr_in_stat78);
            expr2=expr();

            state._fsp--;

            stream_expr.add(expr2.getTree());
            EOF3=(Token)match(input,EOF,FOLLOW_EOF_in_stat80);  
            stream_EOF.add(EOF3);



            // AST REWRITE
            // elements: expr
            // token labels: 
            // rule labels: retval
            // token list labels: 
            // rule list labels: 
            // wildcard labels: 
            retval.tree = root_0;
            RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

            root_0 = (CommonTree)adaptor.nil();
            // 17:18: -> ^( STAT expr )
            {
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:17:21: ^( STAT expr )
                {
                CommonTree root_1 = (CommonTree)adaptor.nil();
                root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(STAT, "STAT"), root_1);

                adaptor.addChild(root_1, stream_expr.nextTree());

                adaptor.addChild(root_0, root_1);
                }

            }

            retval.tree = root_0;
            }

            retval.stop = input.LT(-1);

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (CommonTree)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }
        finally {
        }
        return retval;
    }
    // $ANTLR end "stat"

    public static class expr_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "expr"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:20:1: expr : multExpr ( ( '+' | '-' ) multExpr )* ;
    public final ExprParser.expr_return expr() throws RecognitionException {
        ExprParser.expr_return retval = new ExprParser.expr_return();
        retval.start = input.LT(1);

        CommonTree root_0 = null;

        Token set5=null;
        ExprParser.multExpr_return multExpr4 = null;

        ExprParser.multExpr_return multExpr6 = null;


        CommonTree set5_tree=null;

        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:20:6: ( multExpr ( ( '+' | '-' ) multExpr )* )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:20:8: multExpr ( ( '+' | '-' ) multExpr )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_multExpr_in_expr98);
            multExpr4=multExpr();

            state._fsp--;

            adaptor.addChild(root_0, multExpr4.getTree());
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:20:17: ( ( '+' | '-' ) multExpr )*
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( ((LA1_0>=12 && LA1_0<=13)) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:20:18: ( '+' | '-' ) multExpr
            	    {
            	    set5=(Token)input.LT(1);
            	    set5=(Token)input.LT(1);
            	    if ( (input.LA(1)>=12 && input.LA(1)<=13) ) {
            	        input.consume();
            	        root_0 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(set5), root_0);
            	        state.errorRecovery=false;
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }

            	    pushFollow(FOLLOW_multExpr_in_expr108);
            	    multExpr6=multExpr();

            	    state._fsp--;

            	    adaptor.addChild(root_0, multExpr6.getTree());

            	    }
            	    break;

            	default :
            	    break loop1;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (CommonTree)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }
        finally {
        }
        return retval;
    }
    // $ANTLR end "expr"

    public static class multExpr_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "multExpr"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:23:1: multExpr : atom ( ( '*' | '/' ) atom )* ;
    public final ExprParser.multExpr_return multExpr() throws RecognitionException {
        ExprParser.multExpr_return retval = new ExprParser.multExpr_return();
        retval.start = input.LT(1);

        CommonTree root_0 = null;

        Token set8=null;
        ExprParser.atom_return atom7 = null;

        ExprParser.atom_return atom9 = null;


        CommonTree set8_tree=null;

        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:23:10: ( atom ( ( '*' | '/' ) atom )* )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:23:12: atom ( ( '*' | '/' ) atom )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_atom_in_multExpr119);
            atom7=atom();

            state._fsp--;

            adaptor.addChild(root_0, atom7.getTree());
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:23:17: ( ( '*' | '/' ) atom )*
            loop2:
            do {
                int alt2=2;
                int LA2_0 = input.LA(1);

                if ( ((LA2_0>=14 && LA2_0<=15)) ) {
                    alt2=1;
                }


                switch (alt2) {
            	case 1 :
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:23:18: ( '*' | '/' ) atom
            	    {
            	    set8=(Token)input.LT(1);
            	    set8=(Token)input.LT(1);
            	    if ( (input.LA(1)>=14 && input.LA(1)<=15) ) {
            	        input.consume();
            	        root_0 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(set8), root_0);
            	        state.errorRecovery=false;
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }

            	    pushFollow(FOLLOW_atom_in_multExpr129);
            	    atom9=atom();

            	    state._fsp--;

            	    adaptor.addChild(root_0, atom9.getTree());

            	    }
            	    break;

            	default :
            	    break loop2;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (CommonTree)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }
        finally {
        }
        return retval;
    }
    // $ANTLR end "multExpr"

    public static class atom_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "atom"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:26:1: atom : ( '(' expr ')' -> expr | INT -> ^( NUM INT ) | ID -> ^( VAR ID ) );
    public final ExprParser.atom_return atom() throws RecognitionException {
        ExprParser.atom_return retval = new ExprParser.atom_return();
        retval.start = input.LT(1);

        CommonTree root_0 = null;

        Token char_literal10=null;
        Token char_literal12=null;
        Token INT13=null;
        Token ID14=null;
        ExprParser.expr_return expr11 = null;


        CommonTree char_literal10_tree=null;
        CommonTree char_literal12_tree=null;
        CommonTree INT13_tree=null;
        CommonTree ID14_tree=null;
        RewriteRuleTokenStream stream_16=new RewriteRuleTokenStream(adaptor,"token 16");
        RewriteRuleTokenStream stream_INT=new RewriteRuleTokenStream(adaptor,"token INT");
        RewriteRuleTokenStream stream_17=new RewriteRuleTokenStream(adaptor,"token 17");
        RewriteRuleTokenStream stream_ID=new RewriteRuleTokenStream(adaptor,"token ID");
        RewriteRuleSubtreeStream stream_expr=new RewriteRuleSubtreeStream(adaptor,"rule expr");
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:26:6: ( '(' expr ')' -> expr | INT -> ^( NUM INT ) | ID -> ^( VAR ID ) )
            int alt3=3;
            switch ( input.LA(1) ) {
            case 16:
                {
                alt3=1;
                }
                break;
            case INT:
                {
                alt3=2;
                }
                break;
            case ID:
                {
                alt3=3;
                }
                break;
            default:
                NoViableAltException nvae =
                    new NoViableAltException("", 3, 0, input);

                throw nvae;
            }

            switch (alt3) {
                case 1 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:26:10: '(' expr ')'
                    {
                    char_literal10=(Token)match(input,16,FOLLOW_16_in_atom142);  
                    stream_16.add(char_literal10);

                    pushFollow(FOLLOW_expr_in_atom144);
                    expr11=expr();

                    state._fsp--;

                    stream_expr.add(expr11.getTree());
                    char_literal12=(Token)match(input,17,FOLLOW_17_in_atom146);  
                    stream_17.add(char_literal12);



                    // AST REWRITE
                    // elements: expr
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 26:23: -> expr
                    {
                        adaptor.addChild(root_0, stream_expr.nextTree());

                    }

                    retval.tree = root_0;
                    }
                    break;
                case 2 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:27:7: INT
                    {
                    INT13=(Token)match(input,INT,FOLLOW_INT_in_atom158);  
                    stream_INT.add(INT13);



                    // AST REWRITE
                    // elements: INT
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 27:11: -> ^( NUM INT )
                    {
                        // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:27:14: ^( NUM INT )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(NUM, "NUM"), root_1);

                        adaptor.addChild(root_1, stream_INT.nextNode());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;
                    }
                    break;
                case 3 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:28:7: ID
                    {
                    ID14=(Token)match(input,ID,FOLLOW_ID_in_atom174);  
                    stream_ID.add(ID14);



                    // AST REWRITE
                    // elements: ID
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 28:11: -> ^( VAR ID )
                    {
                        // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:28:14: ^( VAR ID )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(VAR, "VAR"), root_1);

                        adaptor.addChild(root_1, stream_ID.nextNode());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
    	retval.tree = (CommonTree)adaptor.errorNode(input, retval.start, input.LT(-1), re);

        }
        finally {
        }
        return retval;
    }
    // $ANTLR end "atom"

    // Delegated rules


 

    public static final BitSet FOLLOW_stat_in_prog62 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_expr_in_stat78 = new BitSet(new long[]{0x0000000000000000L});
    public static final BitSet FOLLOW_EOF_in_stat80 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_multExpr_in_expr98 = new BitSet(new long[]{0x0000000000003002L});
    public static final BitSet FOLLOW_set_in_expr101 = new BitSet(new long[]{0x0000000000010300L});
    public static final BitSet FOLLOW_multExpr_in_expr108 = new BitSet(new long[]{0x0000000000003002L});
    public static final BitSet FOLLOW_atom_in_multExpr119 = new BitSet(new long[]{0x000000000000C002L});
    public static final BitSet FOLLOW_set_in_multExpr122 = new BitSet(new long[]{0x0000000000010300L});
    public static final BitSet FOLLOW_atom_in_multExpr129 = new BitSet(new long[]{0x000000000000C002L});
    public static final BitSet FOLLOW_16_in_atom142 = new BitSet(new long[]{0x0000000000010300L});
    public static final BitSet FOLLOW_expr_in_atom144 = new BitSet(new long[]{0x0000000000020000L});
    public static final BitSet FOLLOW_17_in_atom146 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_INT_in_atom158 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ID_in_atom174 = new BitSet(new long[]{0x0000000000000002L});

}