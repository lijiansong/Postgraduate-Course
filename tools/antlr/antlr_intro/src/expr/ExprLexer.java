// $ANTLR 3.2 Sep 23, 2009 12:02:23 E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g 2010-12-23 10:48:47
package expr;

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

public class ExprLexer extends Lexer {
    public static final int T__12=12;
    public static final int INT=5;
    public static final int T__8=8;
    public static final int EOF=-1;
    public static final int WS=7;
    public static final int T__13=13;
    public static final int T__10=10;
    public static final int T__9=9;
    public static final int T__11=11;
    public static final int NEWLINE=4;
    public static final int ID=6;

    // delegates
    // delegators

    public ExprLexer() {;} 
    public ExprLexer(CharStream input) {
        this(input, new RecognizerSharedState());
    }
    public ExprLexer(CharStream input, RecognizerSharedState state) {
        super(input,state);

    }
    public String getGrammarFileName() { return "E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g"; }

    // $ANTLR start "T__8"
    public final void mT__8() throws RecognitionException {
        try {
            int _type = T__8;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:5:6: ( '+' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:5:8: '+'
            {
            match('+'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__8"

    // $ANTLR start "T__9"
    public final void mT__9() throws RecognitionException {
        try {
            int _type = T__9;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:6:6: ( '-' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:6:8: '-'
            {
            match('-'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__9"

    // $ANTLR start "T__10"
    public final void mT__10() throws RecognitionException {
        try {
            int _type = T__10;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:7:7: ( '*' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:7:9: '*'
            {
            match('*'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__10"

    // $ANTLR start "T__11"
    public final void mT__11() throws RecognitionException {
        try {
            int _type = T__11;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:8:7: ( '/' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:8:9: '/'
            {
            match('/'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__11"

    // $ANTLR start "T__12"
    public final void mT__12() throws RecognitionException {
        try {
            int _type = T__12;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:9:7: ( '(' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:9:9: '('
            {
            match('('); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__12"

    // $ANTLR start "T__13"
    public final void mT__13() throws RecognitionException {
        try {
            int _type = T__13;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:10:7: ( ')' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:10:9: ')'
            {
            match(')'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__13"

    // $ANTLR start "ID"
    public final void mID() throws RecognitionException {
        try {
            int _type = ID;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:25:4: ( ( 'a' .. 'z' | 'A' .. 'Z' )+ )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:25:6: ( 'a' .. 'z' | 'A' .. 'Z' )+
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:25:6: ( 'a' .. 'z' | 'A' .. 'Z' )+
            int cnt1=0;
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( ((LA1_0>='A' && LA1_0<='Z')||(LA1_0>='a' && LA1_0<='z')) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:
            	    {
            	    if ( (input.LA(1)>='A' && input.LA(1)<='Z')||(input.LA(1)>='a' && input.LA(1)<='z') ) {
            	        input.consume();

            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;}


            	    }
            	    break;

            	default :
            	    if ( cnt1 >= 1 ) break loop1;
                        EarlyExitException eee =
                            new EarlyExitException(1, input);
                        throw eee;
                }
                cnt1++;
            } while (true);


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "ID"

    // $ANTLR start "INT"
    public final void mINT() throws RecognitionException {
        try {
            int _type = INT;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:26:5: ( ( '0' .. '9' )+ )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:26:7: ( '0' .. '9' )+
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:26:7: ( '0' .. '9' )+
            int cnt2=0;
            loop2:
            do {
                int alt2=2;
                int LA2_0 = input.LA(1);

                if ( ((LA2_0>='0' && LA2_0<='9')) ) {
                    alt2=1;
                }


                switch (alt2) {
            	case 1 :
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:26:7: '0' .. '9'
            	    {
            	    matchRange('0','9'); 

            	    }
            	    break;

            	default :
            	    if ( cnt2 >= 1 ) break loop2;
                        EarlyExitException eee =
                            new EarlyExitException(2, input);
                        throw eee;
                }
                cnt2++;
            } while (true);


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "INT"

    // $ANTLR start "NEWLINE"
    public final void mNEWLINE() throws RecognitionException {
        try {
            int _type = NEWLINE;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:27:8: ( ( '\\r' )? '\\n' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:27:9: ( '\\r' )? '\\n'
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:27:9: ( '\\r' )?
            int alt3=2;
            int LA3_0 = input.LA(1);

            if ( (LA3_0=='\r') ) {
                alt3=1;
            }
            switch (alt3) {
                case 1 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:27:9: '\\r'
                    {
                    match('\r'); 

                    }
                    break;

            }

            match('\n'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "NEWLINE"

    // $ANTLR start "WS"
    public final void mWS() throws RecognitionException {
        try {
            int _type = WS;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:28:4: ( ( ' ' | '\\t' | '\\n' | '\\r' )+ )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:28:6: ( ' ' | '\\t' | '\\n' | '\\r' )+
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:28:6: ( ' ' | '\\t' | '\\n' | '\\r' )+
            int cnt4=0;
            loop4:
            do {
                int alt4=2;
                int LA4_0 = input.LA(1);

                if ( ((LA4_0>='\t' && LA4_0<='\n')||LA4_0=='\r'||LA4_0==' ') ) {
                    alt4=1;
                }


                switch (alt4) {
            	case 1 :
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:
            	    {
            	    if ( (input.LA(1)>='\t' && input.LA(1)<='\n')||input.LA(1)=='\r'||input.LA(1)==' ' ) {
            	        input.consume();

            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;}


            	    }
            	    break;

            	default :
            	    if ( cnt4 >= 1 ) break loop4;
                        EarlyExitException eee =
                            new EarlyExitException(4, input);
                        throw eee;
                }
                cnt4++;
            } while (true);

            skip();

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "WS"

    public void mTokens() throws RecognitionException {
        // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:8: ( T__8 | T__9 | T__10 | T__11 | T__12 | T__13 | ID | INT | NEWLINE | WS )
        int alt5=10;
        alt5 = dfa5.predict(input);
        switch (alt5) {
            case 1 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:10: T__8
                {
                mT__8(); 

                }
                break;
            case 2 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:15: T__9
                {
                mT__9(); 

                }
                break;
            case 3 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:20: T__10
                {
                mT__10(); 

                }
                break;
            case 4 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:26: T__11
                {
                mT__11(); 

                }
                break;
            case 5 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:32: T__12
                {
                mT__12(); 

                }
                break;
            case 6 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:38: T__13
                {
                mT__13(); 

                }
                break;
            case 7 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:44: ID
                {
                mID(); 

                }
                break;
            case 8 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:47: INT
                {
                mINT(); 

                }
                break;
            case 9 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:51: NEWLINE
                {
                mNEWLINE(); 

                }
                break;
            case 10 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\expr\\Expr.g:1:59: WS
                {
                mWS(); 

                }
                break;

        }

    }


    protected DFA5 dfa5 = new DFA5(this);
    static final String DFA5_eotS =
        "\11\uffff\1\13\1\14\2\uffff";
    static final String DFA5_eofS =
        "\15\uffff";
    static final String DFA5_minS =
        "\1\11\10\uffff\1\12\1\11\2\uffff";
    static final String DFA5_maxS =
        "\1\172\10\uffff\1\12\1\40\2\uffff";
    static final String DFA5_acceptS =
        "\1\uffff\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\2\uffff\1\12\1\11";
    static final String DFA5_specialS =
        "\15\uffff}>";
    static final String[] DFA5_transitionS = {
            "\1\13\1\12\2\uffff\1\11\22\uffff\1\13\7\uffff\1\5\1\6\1\3\1"+
            "\1\1\uffff\1\2\1\uffff\1\4\12\10\7\uffff\32\7\6\uffff\32\7",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\12",
            "\2\13\2\uffff\1\13\22\uffff\1\13",
            "",
            ""
    };

    static final short[] DFA5_eot = DFA.unpackEncodedString(DFA5_eotS);
    static final short[] DFA5_eof = DFA.unpackEncodedString(DFA5_eofS);
    static final char[] DFA5_min = DFA.unpackEncodedStringToUnsignedChars(DFA5_minS);
    static final char[] DFA5_max = DFA.unpackEncodedStringToUnsignedChars(DFA5_maxS);
    static final short[] DFA5_accept = DFA.unpackEncodedString(DFA5_acceptS);
    static final short[] DFA5_special = DFA.unpackEncodedString(DFA5_specialS);
    static final short[][] DFA5_transition;

    static {
        int numStates = DFA5_transitionS.length;
        DFA5_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA5_transition[i] = DFA.unpackEncodedString(DFA5_transitionS[i]);
        }
    }

    class DFA5 extends DFA {

        public DFA5(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 5;
            this.eot = DFA5_eot;
            this.eof = DFA5_eof;
            this.min = DFA5_min;
            this.max = DFA5_max;
            this.accept = DFA5_accept;
            this.special = DFA5_special;
            this.transition = DFA5_transition;
        }
        public String getDescription() {
            return "1:1: Tokens : ( T__8 | T__9 | T__10 | T__11 | T__12 | T__13 | ID | INT | NEWLINE | WS );";
        }
    }
 

}