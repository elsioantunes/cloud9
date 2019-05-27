// $ANTLR 2.7.6 (2005-12-22): "gramatica.g" -> "MeuParser.java"$
import antlr.TokenBuffer;
import antlr.TokenStreamException;
import antlr.TokenStreamIOException;
import antlr.ANTLRException;
import antlr.LLkParser;
import antlr.Token;
import antlr.TokenStream;
import antlr.RecognitionException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.ParserSharedInputState;
import antlr.collections.impl.BitSet;

public class MeuParser extends antlr.LLkParser implements MeuParserTokenTypes {

    private String operador;
    private int resultado;
    private java.util.ArrayList < String > novaNotacao;
    private java.util.HashMap < String, Integer > mapaValores;
    private String idVar;
    private int valVar;

    public void init() {
        resultado = 0;
        novaNotacao = new java.util.ArrayList < String > ();
        mapaValores = new java.util.HashMap < String, Integer > ();
    }

    protected MeuParser(TokenBuffer tokenBuf, int k) {
        super(tokenBuf, k);
        tokenNames = _tokenNames;
    }

    public MeuParser(TokenBuffer tokenBuf) {
        this(tokenBuf, 1);
    }

    protected MeuParser(TokenStream lexer, int k) {
        super(lexer, k);
        tokenNames = _tokenNames;
    }

    public MeuParser(TokenStream lexer) {
        this(lexer, 1);
    }

    public MeuParser(ParserSharedInputState state) {
        super(state, 1);
        tokenNames = _tokenNames;
    }

    public final void prog() throws RecognitionException, TokenStreamException {


        try { // for error handling
            declara();
            atribui();
            expr();

            Object[] valores = mapaValores.values().toArray();
            for (Object o: valores) {
                System.out.println(o);
            }

        } catch (RecognitionException ex) {
            reportError(ex);
            recover(ex, _tokenSet_0);
        }
    }

    public final void declara() throws RecognitionException, TokenStreamException {


        try { // for error handling
            match(LITERAL_declare);
            match(ID);
            mapaValores.put(LT(0).getText(), 0); {
                _loop4: do {
                    if ((LA(1) == VIRG)) {
                        match(VIRG);
                        match(ID);
                        mapaValores.put(LT(0).getText(), 0);
                    } else {
                        break _loop4;
                    }

                } while (true);
            }
            match(PF);
        } catch (RecognitionException ex) {
            reportError(ex);
            recover(ex, _tokenSet_1);
        }
    }

    public final void atribui() throws RecognitionException, TokenStreamException {


        try { // for error handling
            {
                int _cnt7 = 0;
                _loop7:
                    do {
                        if ((LA(1) == ID)) {
                            match(ID);
                            idVar = LT(0).getText();
                            match(EQ);
                            match(NUM);
                            mapaValores.put(idVar, Integer.parseInt(LT(0).getText()));
                            match(PF);
                        } else {
                            if (_cnt7 >= 1) {
                                break _loop7;
                            } else {
                                throw new NoViableAltException(LT(1), getFilename());
                            }
                        }

                        _cnt7++;
                    } while (true);
            }
        } catch (RecognitionException ex) {
            reportError(ex);
            recover(ex, _tokenSet_2);
        }
    }

    public final void expr() throws RecognitionException, TokenStreamException {


        try { // for error handling
            match(LITERAL_res);
            System.out.println("Initializing...");
            termo();
            resultado = valVar;
            novaNotacao.add(LT(0).getText());
            exprl();

            System.out.println("Agora a notacao posfixa...");
            for (String s: novaNotacao) {
                System.out.print(s + "  ");
            }
            System.out.println();
            System.out.println("A conta vai dar " + resultado);

        } catch (RecognitionException ex) {
            reportError(ex);
            recover(ex, _tokenSet_0);
        }
    }

    public final void termo() throws RecognitionException, TokenStreamException {


        try { // for error handling
            switch (LA(1)) {
                case ID:
                    {
                        match(ID);
                        valVar = mapaValores.get(LT(0).getText()).intValue();
                        break;
                    }
                case NUM:
                    {
                        match(NUM);
                        valVar = Integer.parseInt(LT(0).getText());
                        break;
                    }
                default:
                    {
                        throw new NoViableAltException(LT(1), getFilename());
                    }
            }
        } catch (RecognitionException ex) {
            reportError(ex);
            recover(ex, _tokenSet_3);
        }
    }

    public final void exprl() throws RecognitionException, TokenStreamException {


        try { // for error handling
            {
                _loop11: do {
                    if ((LA(1) == OP)) {
                        match(OP);
                        operador = LT(0).getText();
                        termo();

                        if (operador.equals("+")) {
                            resultado += valVar;
                        } else {
                            resultado -= valVar;
                        }
                        novaNotacao.add(LT(0).getText());
                        novaNotacao.add(operador);

                    } else {
                        break _loop11;
                    }

                } while (true);
            }
        } catch (RecognitionException ex) {
            reportError(ex);
            recover(ex, _tokenSet_0);
        }
    }


    public static final String[] _tokenNames = {
        "<0>",
        "EOF",
        "<2>",
        "NULL_TREE_LOOKAHEAD",
        "\"declare\"",
        "ID",
        "VIRG",
        "PF",
        "EQ",
        "NUM",
        "\"res\"",
        "OP",
        "BLANK"
    };

    private static final long[] mk_tokenSet_0() {
        long[] data = {
            2 L,
            0 L
        };
        return data;
    }
    public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
    private static final long[] mk_tokenSet_1() {
        long[] data = {
            32 L,
            0 L
        };
        return data;
    }
    public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
    private static final long[] mk_tokenSet_2() {
        long[] data = {
            1024 L,
            0 L
        };
        return data;
    }
    public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
    private static final long[] mk_tokenSet_3() {
        long[] data = {
            2050 L,
            0 L
        };
        return data;
    }
    public static final BitSet _tokenSet_3 = new BitSet(mk_tokenSet_3());

}