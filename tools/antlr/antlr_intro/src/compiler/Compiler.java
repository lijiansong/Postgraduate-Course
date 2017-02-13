// $ANTLR 3.2 Sep 23, 2009 12:02:23 E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g 2010-12-23 15:06:02

	package compiler; 


import org.antlr.runtime.*;
import org.antlr.runtime.tree.*;import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

import org.antlr.stringtemplate.*;
import org.antlr.stringtemplate.language.*;
import java.util.HashMap;
public class Compiler extends TreeParser {
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


        public Compiler(TreeNodeStream input) {
            this(input, new RecognizerSharedState());
        }
        public Compiler(TreeNodeStream input, RecognizerSharedState state) {
            super(input, state);
             
        }
        
    protected StringTemplateGroup templateLib =
      new StringTemplateGroup("CompilerTemplates", AngleBracketTemplateLexer.class);

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

    public String[] getTokenNames() { return Compiler.tokenNames; }
    public String getGrammarFileName() { return "E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g"; }


    public static class prog_return extends TreeRuleReturnScope {
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "prog"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:14:1: prog : ^( PROG s= stat ) ;
    public final Compiler.prog_return prog() throws RecognitionException {
        Compiler.prog_return retval = new Compiler.prog_return();
        retval.start = input.LT(1);

        Compiler.stat_return s = null;


        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:14:6: ( ^( PROG s= stat ) )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:14:8: ^( PROG s= stat )
            {
            match(input,PROG,FOLLOW_PROG_in_prog49); 

            match(input, Token.DOWN, null); 
            pushFollow(FOLLOW_stat_in_prog53);
            s=stat();

            state._fsp--;


            match(input, Token.UP, null); 
            System.out.println("RET");

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
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "stat"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:16:1: stat : ^( STAT e= expr ) ;
    public final Compiler.stat_return stat() throws RecognitionException {
        Compiler.stat_return retval = new Compiler.stat_return();
        retval.start = input.LT(1);

        Compiler.expr_return e = null;


        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:17:1: ( ^( STAT e= expr ) )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:17:3: ^( STAT e= expr )
            {
            match(input,STAT,FOLLOW_STAT_in_stat66); 

            match(input, Token.DOWN, null); 
            pushFollow(FOLLOW_expr_in_stat70);
            e=expr();

            state._fsp--;


            match(input, Token.UP, null); 

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
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "expr"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:20:1: expr : ( ^( '+' e1= expr e2= expr ) | ^( '-' e1= expr e2= expr ) | ^( '*' e1= expr e2= expr ) | ^( '/' e1= expr e2= expr ) | a= atom );
    public final Compiler.expr_return expr() throws RecognitionException {
        Compiler.expr_return retval = new Compiler.expr_return();
        retval.start = input.LT(1);

        Compiler.expr_return e1 = null;

        Compiler.expr_return e2 = null;

        Compiler.atom_return a = null;


        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:21:1: ( ^( '+' e1= expr e2= expr ) | ^( '-' e1= expr e2= expr ) | ^( '*' e1= expr e2= expr ) | ^( '/' e1= expr e2= expr ) | a= atom )
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
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:21:7: ^( '+' e1= expr e2= expr )
                    {
                    match(input,12,FOLLOW_12_in_expr88); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr92);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr96);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    System.out.println("ADD");

                    }
                    break;
                case 2 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:22:4: ^( '-' e1= expr e2= expr )
                    {
                    match(input,13,FOLLOW_13_in_expr105); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr109);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr113);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    System.out.println("SUB");

                    }
                    break;
                case 3 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:23:7: ^( '*' e1= expr e2= expr )
                    {
                    match(input,14,FOLLOW_14_in_expr125); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr129);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr133);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    System.out.println("MUL");

                    }
                    break;
                case 4 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:24:4: ^( '/' e1= expr e2= expr )
                    {
                    match(input,15,FOLLOW_15_in_expr142); 

                    match(input, Token.DOWN, null); 
                    pushFollow(FOLLOW_expr_in_expr146);
                    e1=expr();

                    state._fsp--;

                    pushFollow(FOLLOW_expr_in_expr150);
                    e2=expr();

                    state._fsp--;


                    match(input, Token.UP, null); 
                    System.out.println("DIV");

                    }
                    break;
                case 5 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:25:4: a= atom
                    {
                    pushFollow(FOLLOW_atom_in_expr160);
                    a=atom();

                    state._fsp--;


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
        public StringTemplate st;
        public Object getTemplate() { return st; }
        public String toString() { return st==null?null:st.toString(); }
    };

    // $ANTLR start "atom"
    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:28:1: atom : ( ^( NUM i= INT ) | ^( VAR v= ID ) );
    public final Compiler.atom_return atom() throws RecognitionException {
        Compiler.atom_return retval = new Compiler.atom_return();
        retval.start = input.LT(1);

        CommonTree i=null;
        CommonTree v=null;

        try {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:29:1: ( ^( NUM i= INT ) | ^( VAR v= ID ) )
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
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:29:8: ^( NUM i= INT )
                    {
                    match(input,NUM,FOLLOW_NUM_in_atom179); 

                    match(input, Token.DOWN, null); 
                    i=(CommonTree)match(input,INT,FOLLOW_INT_in_atom183); 

                    match(input, Token.UP, null); 
                    System.out.println("LDC "+i.getText());

                    }
                    break;
                case 2 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\compiler\\Compiler.g:30:6: ^( VAR v= ID )
                    {
                    match(input,VAR,FOLLOW_VAR_in_atom194); 

                    match(input, Token.DOWN, null); 
                    v=(CommonTree)match(input,ID,FOLLOW_ID_in_atom198); 

                    match(input, Token.UP, null); 
                    System.out.println("LDV "+v.getText());

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


 

    public static final BitSet FOLLOW_PROG_in_prog49 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_stat_in_prog53 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_STAT_in_stat66 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_stat70 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_12_in_expr88 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr92 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr96 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_13_in_expr105 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr109 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr113 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_14_in_expr125 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr129 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr133 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_15_in_expr142 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_expr_in_expr146 = new BitSet(new long[]{0x000000000000F0C0L});
    public static final BitSet FOLLOW_expr_in_expr150 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_atom_in_expr160 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_NUM_in_atom179 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_INT_in_atom183 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_VAR_in_atom194 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_in_atom198 = new BitSet(new long[]{0x0000000000000008L});

}