class Token{
    // Container que guarda as infos do token reconhecido
    public int lin, col; 
    public TokenTypes code;
    public String str;

    Token(int lin, int col){
        this.str = "";
        this.lin = lin;
        this.col = col;
    }
}


enum TokenTypes{
	TOKEN_INVALIDO, LITERAL_true, LITERAL_false, T_BOOL,
	T_CHAR, T_ID, T_STRING, NUMBER, NUMBER2, COMMENT,
	DELIMIT_COMMA, DELIMIT_COLON, DELIMIT_SEMICOLON, P_DOT,
	DELIMIT_LBRACE, DELIMIT_LBRACK, DELIMIT_LPAR, DELIMIT_RBRACE, DELIMIT_RBRACK, DELIMIT_RPAR,
	OP_ASSIGN, OP_DEC, OP_DIV, OP_EXP, OP_INC, OP_MINUS, OP_MOD, OP_NEG, OP_PLUS, OP_TIMES,
	REL_EQT, REL_GE, REL_GT, REL_LE, REL_LT, REL_NE,
	BIT_AND, BIT_OR, REL_AND, REL_OR,
	LITERAL_FLOAT, LITERAL_INT, LITERAL_STRING, LITERAL_BOOL,
	LITERAL_PRINT, LITERAL_INPUT,
	LITERAL_IF, LITERAL_THEN, LITERAL_ELSE, LITERAL_ENDIF, 
	LITERAL_FOR, LITERAL_TO, LITERAL_STEP, LITERAL_NEXT, LITERAL_WHILE, LITERAL_UNTIL, 
	LITERAL_REM, LITERAL_GOTO, LITERAL_GOSUB, LITERAL_RETURN, LITERAL_SUB, LITERAL_ENDSUB, 
	EOF
}