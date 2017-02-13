// $ANTLR 3.2 Sep 23, 2009 12:02:23 E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g 2010-12-23 10:48:47
package expr;

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

public class ExprParser extends Parser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "NEWLINE", "INT", "ID", "WS", "'+'", "'-'", "'*'", "'/'", "'('", "')'"
    };
    public static final int T__12=12;
    public static final int INT=5;
    public static final int T__8=8;
    public static final int WS=7;
    public static final int EOF=-1;
    public static final int T__13=13;
    public static final int T__10=10;
    public static final int T__9=9;
    public static final int T__11=11;
    public static final int ID=6;
    public static final int NEWLINE=4;

    // delegates
    // delegators


        public ExprParser(TokenStream input) {
            this(input, new RecognizerSharedState());
        }
        public ExprParser(TokenStream input, RecognizerSharedState state) {
            super(input, state);
             
        }
        

    public String[] getTokenNames() { return ExprParser.tokenNames; }
    public String getGrammarFileName() { return "E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g"; }



    // $ANTLR start "prog"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:6:1: prog : stat ;
    public final void prog() throws RecognitionException {
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:6:5: ( stat )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:6:7: stat
            {
            pushFollow(FOLLOW_stat_in_prog22);
            stat();

            state._fsp--;


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return ;
    }
    // $ANTLR end "prog"


    // $ANTLR start "stat"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:9:1: stat : ( expr | NEWLINE );
    public final void stat() throws RecognitionException {
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:9:6: ( expr | NEWLINE )
            int alt1=2;
            int LA1_0 = input.LA(1);

            if ( ((LA1_0>=INT && LA1_0<=ID)||LA1_0==12) ) {
                alt1=1;
            }
            else if ( (LA1_0==NEWLINE) ) {
                alt1=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 1, 0, input);

                throw nvae;
            }
            switch (alt1) {
                case 1 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:9:8: expr
                    {
                    pushFollow(FOLLOW_expr_in_stat33);
                    expr();

                    state._fsp--;


                    }
                    break;
                case 2 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:10:5: NEWLINE
                    {
                    match(input,NEWLINE,FOLLOW_NEWLINE_in_stat40); 

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return ;
    }
    // $ANTLR end "stat"


    // $ANTLR start "expr"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:13:1: expr : multExpr ( ( '+' | '-' ) multExpr )* ;
    public final void expr() throws RecognitionException {
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:13:6: ( multExpr ( ( '+' | '-' ) multExpr )* )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:13:8: multExpr ( ( '+' | '-' ) multExpr )*
            {
            pushFollow(FOLLOW_multExpr_in_expr49);
            multExpr();

            state._fsp--;

            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:13:17: ( ( '+' | '-' ) multExpr )*
            loop2:
            do {
                int alt2=2;
                int LA2_0 = input.LA(1);

                if ( ((LA2_0>=8 && LA2_0<=9)) ) {
                    alt2=1;
                }


                switch (alt2) {
            	case 1 :
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:13:18: ( '+' | '-' ) multExpr
            	    {
            	    if ( (input.LA(1)>=8 && input.LA(1)<=9) ) {
            	        input.consume();
            	        state.errorRecovery=false;
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }

            	    pushFollow(FOLLOW_multExpr_in_expr58);
            	    multExpr();

            	    state._fsp--;


            	    }
            	    break;

            	default :
            	    break loop2;
                }
            } while (true);


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return ;
    }
    // $ANTLR end "expr"


    // $ANTLR start "multExpr"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:16:1: multExpr : atom ( ( '*' | '/' ) atom )* ;
    public final void multExpr() throws RecognitionException {
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:16:10: ( atom ( ( '*' | '/' ) atom )* )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:16:12: atom ( ( '*' | '/' ) atom )*
            {
            pushFollow(FOLLOW_atom_in_multExpr69);
            atom();

            state._fsp--;

            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:16:17: ( ( '*' | '/' ) atom )*
            loop3:
            do {
                int alt3=2;
                int LA3_0 = input.LA(1);

                if ( ((LA3_0>=10 && LA3_0<=11)) ) {
                    alt3=1;
                }


                switch (alt3) {
            	case 1 :
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:16:18: ( '*' | '/' ) atom
            	    {
            	    if ( (input.LA(1)>=10 && input.LA(1)<=11) ) {
            	        input.consume();
            	        state.errorRecovery=false;
            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }

            	    pushFollow(FOLLOW_atom_in_multExpr78);
            	    atom();

            	    state._fsp--;


            	    }
            	    break;

            	default :
            	    break loop3;
                }
            } while (true);


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return ;
    }
    // $ANTLR end "multExpr"


    // $ANTLR start "atom"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:19:1: atom : ( '(' expr ')' | INT | ID );
    public final void atom() throws RecognitionException {
        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:19:6: ( '(' expr ')' | INT | ID )
            int alt4=3;
            switch ( input.LA(1) ) {
            case 12:
                {
                alt4=1;
                }
                break;
            case INT:
                {
                alt4=2;
                }
                break;
            case ID:
                {
                alt4=3;
                }
                break;
            default:
                NoViableAltException nvae =
                    new NoViableAltException("", 4, 0, input);

                throw nvae;
            }

            switch (alt4) {
                case 1 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:19:10: '(' expr ')'
                    {
                    match(input,12,FOLLOW_12_in_atom91); 
                    pushFollow(FOLLOW_expr_in_atom93);
                    expr();

                    state._fsp--;

                    match(input,13,FOLLOW_13_in_atom95); 

                    }
                    break;
                case 2 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:20:7: INT
                    {
                    match(input,INT,FOLLOW_INT_in_atom104); 

                    }
                    break;
                case 3 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:21:7: ID
                    {
                    match(input,ID,FOLLOW_ID_in_atom114); 

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return ;
    }
    // $ANTLR end "atom"

    // Delegated rules


 

    public static final BitSet FOLLOW_stat_in_prog22 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_expr_in_stat33 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NEWLINE_in_stat40 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_multExpr_in_expr49 = new BitSet(new long[]{0x0000000000000302L});
    public static final BitSet FOLLOW_set_in_expr52 = new BitSet(new long[]{0x0000000000001060L});
    public static final BitSet FOLLOW_multExpr_in_expr58 = new BitSet(new long[]{0x0000000000000302L});
    public static final BitSet FOLLOW_atom_in_multExpr69 = new BitSet(new long[]{0x0000000000000C02L});
    public static final BitSet FOLLOW_set_in_multExpr72 = new BitSet(new long[]{0x0000000000001060L});
    public static final BitSet FOLLOW_atom_in_multExpr78 = new BitSet(new long[]{0x0000000000000C02L});
    public static final BitSet FOLLOW_12_in_atom91 = new BitSet(new long[]{0x0000000000001060L});
    public static final BitSet FOLLOW_expr_in_atom93 = new BitSet(new long[]{0x0000000000002000L});
    public static final BitSet FOLLOW_13_in_atom95 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_INT_in_atom104 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ID_in_atom114 = new BitSet(new long[]{0x0000000000000002L});

}