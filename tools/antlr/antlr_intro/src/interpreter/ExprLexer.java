// $ANTLR 3.2 Sep 23, 2009 12:02:23 E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g 2010-12-23 10:51:24
package interpreter;

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

public class ExprLexer extends Lexer {
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

    public ExprLexer() {;} 
    public ExprLexer(CharStream input) {
        this(input, new RecognizerSharedState());
    }
    public ExprLexer(CharStream input, RecognizerSharedState state) {
        super(input,state);

    }
    public String getGrammarFileName() { return "E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g"; }

    // $ANTLR start "T__12"
    public final void mT__12() throws RecognitionException {
        try {
            int _type = T__12;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:5:7: ( '+' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:5:9: '+'
            {
            match('+'); 

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
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:6:7: ( '-' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:6:9: '-'
            {
            match('-'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__13"

    // $ANTLR start "T__14"
    public final void mT__14() throws RecognitionException {
        try {
            int _type = T__14;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:7:7: ( '*' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:7:9: '*'
            {
            match('*'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__14"

    // $ANTLR start "T__15"
    public final void mT__15() throws RecognitionException {
        try {
            int _type = T__15;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:8:7: ( '/' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:8:9: '/'
            {
            match('/'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__15"

    // $ANTLR start "T__16"
    public final void mT__16() throws RecognitionException {
        try {
            int _type = T__16;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:9:7: ( '(' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:9:9: '('
            {
            match('('); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__16"

    // $ANTLR start "T__17"
    public final void mT__17() throws RecognitionException {
        try {
            int _type = T__17;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:10:7: ( ')' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:10:9: ')'
            {
            match(')'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__17"

    // $ANTLR start "ID"
    public final void mID() throws RecognitionException {
        try {
            int _type = ID;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:32:4: ( ( 'a' .. 'z' | 'A' .. 'Z' )+ )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:32:6: ( 'a' .. 'z' | 'A' .. 'Z' )+
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:32:6: ( 'a' .. 'z' | 'A' .. 'Z' )+
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
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:
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
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:33:5: ( ( '0' .. '9' )+ )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:33:7: ( '0' .. '9' )+
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:33:7: ( '0' .. '9' )+
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
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:33:7: '0' .. '9'
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
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:34:8: ( ( '\\r' )? '\\n' )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:34:9: ( '\\r' )? '\\n'
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:34:9: ( '\\r' )?
            int alt3=2;
            int LA3_0 = input.LA(1);

            if ( (LA3_0=='\r') ) {
                alt3=1;
            }
            switch (alt3) {
                case 1 :
                    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:34:9: '\\r'
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
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:35:4: ( ( ' ' | '\\t' | '\\n' | '\\r' )+ )
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:35:6: ( ' ' | '\\t' | '\\n' | '\\r' )+
            {
            // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:35:6: ( ' ' | '\\t' | '\\n' | '\\r' )+
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
            	    // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:
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
        // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:8: ( T__12 | T__13 | T__14 | T__15 | T__16 | T__17 | ID | INT | NEWLINE | WS )
        int alt5=10;
        alt5 = dfa5.predict(input);
        switch (alt5) {
            case 1 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:10: T__12
                {
                mT__12(); 

                }
                break;
            case 2 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:16: T__13
                {
                mT__13(); 

                }
                break;
            case 3 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:22: T__14
                {
                mT__14(); 

                }
                break;
            case 4 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:28: T__15
                {
                mT__15(); 

                }
                break;
            case 5 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:34: T__16
                {
                mT__16(); 

                }
                break;
            case 6 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:40: T__17
                {
                mT__17(); 

                }
                break;
            case 7 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:46: ID
                {
                mID(); 

                }
                break;
            case 8 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:49: INT
                {
                mINT(); 

                }
                break;
            case 9 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:53: NEWLINE
                {
                mNEWLINE(); 

                }
                break;
            case 10 :
                // E:\\MyEclipse\\workspace\\antlr_intro\\src\\interpreter\\Expr.g:1:61: WS
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
            return "1:1: Tokens : ( T__12 | T__13 | T__14 | T__15 | T__16 | T__17 | ID | INT | NEWLINE | WS );";
        }
    }
 

}