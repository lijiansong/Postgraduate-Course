// $ANTLR 3.2 Sep 23, 2009 12:02:23 E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g 2010-12-23 11:02:43

	package interpreter;
	import java.util.Random;
	import java.util.Map;
	import java.util.HashMap;	


import org.antlr.runtime.*;
import org.antlr.runtime.tree.*;import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

import org.antlr.stringtemplate.*;
import org.antlr.stringtemplate.language.*;
import java.util.HashMap;
public class Eval extends TreeParser {
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
    public static final int T__16=16;
    public static final int NUM=6;
    public static final int T__14=14;
    public static final int PROG=4;
    public static final int T__15=15;
    public static final int ID=9;
    public static final int NEWLINE=10;

    // delegates
    // delegators


        public Eval(TreeNodeStream input) {
            this(input, new RecognizerSharedState());
        }
        public Eval(TreeNodeStream input, RecognizerSharedState state) {
            super(input, state);
             
        }
        
    protected StringTemplateGroup templateLib =
      new StringTemplateGroup("EvalTemplates", AngleBracketTemplateLexer.class);

    public void setTemplateLib(StringTemplateGroup templateLib) {
      this.templateLib = templateLib;
    }
    public StringTemplateGroup getTemplateLib() {
      return templateLib;
    }
    /** allows convenient multi-value initialization:
     *  "new STAttrMap().put(...).put(...)"
     */
    public static class STAttrMap extends HashMap {
      public STAttrMap put(String attrName, Object value) {
        super.put(attrName, value);
        return this;
      }
      public STAttrMap put(String attrName, int value) {
        super.put(attrName, new Integer(value));
        return this;
      }
    }

    public String[] getTokenNames() { return Eval.tokenNames; }
    public String getGrammarFileName() { return "E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g"; }


    	Random rand = new Random() ; 
    	Map<String, Integer> valueMap = new HashMap<String, Integer>();


    public static class prog_return extends TreeRuleReturnScope {
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "prog"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:20:1: prog : ^( PROG s= stat ) ;
    public final Eval.prog_return prog() throws RecognitionException {
        Eval.prog_return retval = new Eval.prog_return();
        retval.start = input.LT(1);

        Eval.stat_return s = null;


        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:20:6: ( ^( PROG s= stat ) )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:20:8: ^( PROG s= stat )
            {
            match(input,PROG,FOLLOW_PROG_in_prog51); 

            match(input, Token.DOWN, null); 
            pushFollow(FOLLOW_stat_in_prog55);
            s=stat();

            state._fsp--;


            match(input, Token.UP, null); 
            System.out.println("Compute result : " + s.value);

            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return retval;
    }
    // $ANTLR end "prog"

    public static class stat_return extends TreeRuleReturnScope {
        public Integer value;
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "stat"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:22:1: stat returns [Integer value] : ^( STAT e= expr ) ;
    public final Eval.stat_return stat() throws RecognitionException {
        Eval.stat_return retval = new Eval.stat_return();
        retval.start = input.LT(1);

        Eval.expr_return e = null;


        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:23:1: ( ^( STAT e= expr ) )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:23:3: ^( STAT e= expr )
            {
            match(input,STAT,FOLLOW_STAT_in_stat70); 

            match(input, Token.DOWN, null); 
            pushFollow(FOLLOW_expr_in_stat74);
            e=expr();

            state._fsp--;


            match(input, Token.UP, null); 
            retval.value = e.value;

            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
        }
        return retval;
    }
    // $ANTLR end "stat"

    public static class expr_return extends TreeRuleReturnScope {
        public Integer value;
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "expr"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:26:1: expr returns [Integer value] : ( ^( '+' e1= expr e2= expr ) | ^( '-' e1= expr e2= expr ) | ^( '*' e1= expr e2= expr ) | ^( '/' e1= expr e2= expr ) | a= atom );
    public final Eval.expr_return expr() throws RecognitionException {
        Eval.expr_return retval = new Eval.expr_return();
        retval.start = input.LT(1);

        Eval.expr_return e1 = null;

        Eval.expr_return e2 = null;

        Eval.atom_return a = null;


        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:27:1: ( ^( '+' e1= expr e2= expr ) | ^( '-' e1= expr e2= expr ) | ^( '*' e1= expr e2= expr ) | ^( '/' e1= expr e2= expr ) | a= atom )
            int alt1=5;
            switch ( input.LA(1) ) {
            case 12:
                {
                alt1=1;
                }
                break;
            case 13:
                {
                alt1=2;
                }
                break;
            case 14:
                {
                alt1=3;
                }
                break;
            case 15:
                {
                alt1=4;
                }
                break;
            case NUM:
            case VAR:
                {
                alt1=5;
                }
                break;
            default:
                NoViableAltException nvae =
                    new NoViableAltException("", 1, 0, input);

                throw nvae;
            }

            switch (alt1) {
                case 1 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:27:7: ^( '+' e1= expr e2= expr )
                    {
                    match(input,12,FOLLOW_12_in_expr94); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr98);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr102);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    retval.value = e1.value + e2.value;

                    }
                    break;
                case 2 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:28:4: ^( '-' e1= expr e2= expr )
                    {
                    match(input,13,FOLLOW_13_in_expr111); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr115);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr119);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    retval.value = e1.value - e2.value;

                    }
                    break;
                case 3 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:29:7: ^( '*' e1= expr e2= expr )
                    {
                    match(input,14,FOLLOW_14_in_expr131); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr135);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr139);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    retval.value = e1.value * e2.value;

                    }
                    break;
                case 4 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:30:4: ^( '/' e1= expr e2= expr )
                    {
                    match(input,15,FOLLOW_15_in_expr148); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr152);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr156);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    retval.value = e1.value / e2.value;

                    }
                    break;
                case 5 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:31:4: a= atom
                    {
                    pushFollow(FOLLOW_atom_in_expr166);
                    a=atom();

                    state._fsp--;

                    retval.value = a.value;

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
        return retval;
    }
    // $ANTLR end "expr"

    public static class atom_return extends TreeRuleReturnScope {
        public Integer value;
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "atom"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:34:1: atom returns [Integer value] : ( ^( NUM i= INT ) | ^( VAR v= ID ) );
    public final Eval.atom_return atom() throws RecognitionException {
        Eval.atom_return retval = new Eval.atom_return();
        retval.start = input.LT(1);

        CommonTree i=null;
        CommonTree v=null;

        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:35:1: ( ^( NUM i= INT ) | ^( VAR v= ID ) )
            int alt2=2;
            int LA2_0 = input.LA(1);

            if ( (LA2_0==NUM) ) {
                alt2=1;
            }
            else if ( (LA2_0==VAR) ) {
                alt2=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 2, 0, input);

                throw nvae;
            }
            switch (alt2) {
                case 1 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:35:8: ^( NUM i= INT )
                    {
                    match(input,NUM,FOLLOW_NUM_in_atom186); 

                    match(input, Token.DOWN, null); 
                    i=(CommonTree)match(input,INT,FOLLOW_INT_in_atom190); 

                    match(input, Token.UP, null); 
                    retval.value = Integer.parseInt(i.getText());

                    }
                    break;
                case 2 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Eval.g:36:6: ^( VAR v= ID )
                    {
                    match(input,VAR,FOLLOW_VAR_in_atom201); 

                    match(input, Token.DOWN, null); 
                    v=(CommonTree)match(input,ID,FOLLOW_ID_in_atom205); 

                    match(input, Token.UP, null); 
                    String name=v.getText(); if(valueMap.get(name)==null){int t = rand.nextInt(10);valueMap.put(name,t); System.out.println(name + ":" + t); retval.value = t;}else{retval.value = valueMap.get(name);}

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
        return retval;
    }
    // $ANTLR end "atom"

    // Delegated rules


 

    public static final BitSet FOLLOW_PROG_in_prog51 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_stat_in_prog55 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_STAT_in_stat70 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_stat74 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_12_in_expr94 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr98 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr102 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_13_in_expr111 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr115 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr119 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_14_in_expr131 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr135 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr139 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_15_in_expr148 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr152 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr156 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_atom_in_expr166 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NUM_in_atom186 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_INT_in_atom190 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_VAR_in_atom201 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_in_atom205 = new BitSet(new long[]{0x0000000000000008L});

}