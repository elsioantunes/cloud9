// $ANTLR 2.7.6 (2005-12-22): "gram.g" -> "MyParser.java"$

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

public class MyParser extends antlr.LLkParser       implements MyParserTokenTypes
 {

   private Programa     programa;
   private Comando      cmd;
   private int          writeType;
   private String       element;
   private StackCommand stack;
   public void init(){
       programa = new Programa();
       stack    = new StackCommand();
   }

protected MyParser(TokenBuffer tokenBuf, int k) {
  super(tokenBuf,k);
  tokenNames = _tokenNames;
}

public MyParser(TokenBuffer tokenBuf) {
  this(tokenBuf,1);
}

protected MyParser(TokenStream lexer, int k) {
  super(lexer,k);
  tokenNames = _tokenNames;
}

public MyParser(TokenStream lexer) {
  this(lexer,1);
}

public MyParser(ParserSharedInputState state) {
  super(state,1);
  tokenNames = _tokenNames;
}

	public final void prog() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_programa);
			declara();
			corpo();
			match(LITERAL_fimprog);
			
			System.out.println(programa.writeCode());
			
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		}
	}
	
	public final void declara() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_declare);
			match(ID);
			
			programa.addVariable(LT(0).getText());
			
			{
			_loop4:
			do {
				if ((LA(1)==VIRG)) {
					match(VIRG);
					match(ID);
					
					programa.addVariable(LT(0).getText());
					
				}
				else {
					break _loop4;
				}
				
			} while (true);
			}
			match(PF);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		}
	}
	
	public final void corpo() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_inicio);
			{
			int _cnt7=0;
			_loop7:
			do {
				if ((LA(1)==LITERAL_se||LA(1)==LITERAL_mostre||LA(1)==LITERAL_leia)) {
					comando();
				}
				else {
					if ( _cnt7>=1 ) { break _loop7; } else {throw new NoViableAltException(LT(1), getFilename());}
				}
				
				_cnt7++;
			} while (true);
			}
			match(LITERAL_fim);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_2);
		}
	}
	
	public final void comando() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			switch ( LA(1)) {
			case LITERAL_se:
			{
				cmdIf();
				break;
			}
			case LITERAL_mostre:
			{
				cmdPrnt();
				break;
			}
			case LITERAL_leia:
			{
				cmdRead();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void cmdIf() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_se);
			match(AP);
			{
			switch ( LA(1)) {
			case ID:
			{
				match(ID);
				break;
			}
			case NUM:
			{
				match(NUM);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			element = LT(0).getText();
			match(OPREL);
			element += LT(0).getText();
			{
			switch ( LA(1)) {
			case ID:
			{
				match(ID);
				break;
			}
			case NUM:
			{
				match(NUM);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			element += LT(0).getText();
			
			cmd = new ComandoIf();
			((ComandoIf)cmd).setLogicalExpr(element);
			stack.push(cmd);
			
			match(FP);
			match(LITERAL_entao);
			corpo();
			
			Comando cmd = stack.pop();
			if (stack.isEmpty()){
			programa.addCommand(cmd);
			}
			else{
			Comando tmp = stack.getTopo();
			((ComandoIf)tmp).addCommand(cmd);
			}
			
			
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void cmdPrnt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_mostre);
			cmd = new ComandoWrite();
			{
			switch ( LA(1)) {
			case ID:
			{
				match(ID);
				writeType = ComandoWrite.TYPE_ID;
				break;
			}
			case TEXTO:
			{
				match(TEXTO);
				writeType = ComandoWrite.TYPE_TEXT;
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			element = LT(0).getText();
			match(PF);
			
			
			((ComandoWrite)cmd).setType(writeType);
			((ComandoWrite)cmd).setContent(element);
			if (stack.isEmpty()){
			programa.addCommand(cmd);
			}
			else{
			Comando tmp = stack.getTopo();
			((ComandoIf)tmp).addCommand(cmd);
			}
			
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void cmdRead() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_leia);
			cmd = new ComandoRead();
			{
			match(ID);
			}
			
			element = LT(0).getText();
			
			match(PF);
			
			((ComandoRead)cmd).setId(element);
			if (stack.isEmpty()){
			programa.addCommand(cmd);
			}
			else{
			Comando tmp = stack.getTopo();
			((ComandoIf)tmp).addCommand(cmd);
			}
			
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"\"programa\"",
		"\"fimprog\"",
		"\"declare\"",
		"ID",
		"VIRG",
		"PF",
		"\"inicio\"",
		"\"fim\"",
		"\"se\"",
		"AP",
		"NUM",
		"OPREL",
		"FP",
		"\"entao\"",
		"\"mostre\"",
		"TEXTO",
		"\"leia\"",
		"WS"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 2L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { 1024L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { 1316896L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	private static final long[] mk_tokenSet_3() {
		long[] data = { 1316864L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_3 = new BitSet(mk_tokenSet_3());
	
	}
