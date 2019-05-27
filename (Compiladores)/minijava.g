BNF for minijava.jj

TOKENS

<DEFAULT>    SKIP : {" " | "\t" | "\n" | "\r" | "\f"}
 
<DEFAULT> SPECIAL : { <SINGLE_LINE_COMMENT: "//" (~["\n","\r"])* ("\n" | "\r" | "\r\n")> 

				| <FORMAL_COMMENT:    "/**" (~["*"])* "*" ("*" | ~["*","/"] (~["*"])* "*")* "/">
				| <MULTI_LINE_COMMENT: "/*" (~["*"])* "*" ("*" | ~["*","/"] (~["*"])* "*")* "/">
				
			}

   
<DEFAULT> TOKEN : {
  <LPAREN: "(">
| <RPAREN: ")">
| <LSQPAREN: "[">
| <RSQPAREN: "]">
| <LBRACE: "{">
| <RBRACE: "}">
| <SEMICOLON: ";">
| <DOT: ".">
| <ASSIGN: "=">
| <LT: "<">
| <PLUS: "+">
| <MINUS: "-">
| <AND: "&">
| <NOT: "!">

| <BOOLEAN: "boolean">
| <CLASS: "class">
| <INTERFACE: "interface">
| <ELSE: "else">
| <EXTENDS: "extends">
| <FALSE: "false">
| <IF: "if">
| <WHILE: "while">
| <INTEGER: "int">
| <LENGTH: "length">
| <MAIN: "main">
| <NEW: "new">
| <PUBLIC: "public">
| <RETURN: "return">
| <STATIC: "static">
| <STRING: "String">
| <THIS: "this">
| <TRUE: "true">
| <PRINT: "System.out.println">
| <VOID: "void">
}

   
<DEFAULT> TOKEN : {
<INTEGER_LITERAL: ["1"-"9"] (["0"-"9"])* | "0">
}

   
<DEFAULT> TOKEN : {
<IDENTIFIER: <LETTER> (<LETTER> | <DIGIT>)*>
| <#LETTER: ["$","A"-"Z","_","a"-"z","\u00c0"-"\u00d6","\u00d8"-"\u00f6","\u00f8"-"\u00ff","\u0100"-"\u1fff","\u3040"-"\u318f","\u3300"-"\u337f","\u3400"-"\u3d2d","\u4e00"-"\u9fff","\uf900"-"\ufaff"]>
| <#DIGIT: ["0"-"9","\u0660"-"\u0669","\u06f0"-"\u06f9","\u0966"-"\u096f","\u09e6"-"\u09ef","\u0a66"-"\u0a6f","\u0ae6"-"\u0aef","\u0b66"-"\u0b6f","\u0be7"-"\u0bef","\u0c66"-"\u0c6f","\u0ce6"-"\u0cef","\u0d66"-"\u0d6f","\u0e50"-"\u0e59","\u0ed0"-"\u0ed9","\u1040"-"\u1049"]>
}

   
NON-TERMINALS

/************************************
 * The MiniJava Grammar Starts Here *
 ************************************/
Goal			    ::=	MainClass ( TypeDeclaration )* <EOF>
MainClass		    ::=	"class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" PrintStatement "}" "}"
TypeDeclaration		::=	ClassDeclaration | ClassExtendsDeclaration
ClassDeclaration	::=	"class" Identifier "{" ( VarDeclaration )* ( MethodDeclaration )* "}"
ClassExtendsDeclaration	::=	"class" Identifier "extends" Identifier "{" ( VarDeclaration )* ( MethodDeclaration )* "}"
VarDeclaration		::=	Type Identifier ";"
MethodDeclaration	::=	"public" Type Identifier "(" ( FormalParameterList )? ")" "{" ( VarDeclaration )* ( Statement )* "return" Expression ";" "}"
FormalParameterList	::=	FormalParameter ( FormalParameterRest )*
FormalParameter		::=	Type Identifier
FormalParameterRest	::=	"," FormalParameter
Type			    ::=	ArrayType | BooleanType | IntegerType |	Identifier 
ArrayType		    ::=	"int" "[" "]"
BooleanType		    ::=	"boolean"
IntegerType		    ::=	"int"
Statement		    ::=	Block |	AssignmentStatement | ArrayAssignmentStatement | IfStatement | WhileStatement |	PrintStatement 
Block			    ::=	"{" ( Statement )* "}"
AssignmentStatement	::=	Identifier "=" Expression ";"
ArrayAssignmentStatement::=	Identifier "[" Expression "]" "=" Expression ";"
IfStatement		    ::=	"if" "(" Expression ")" Statement "else" Statement
WhileStatement		::=	"while" "(" Expression ")" Statement
PrintStatement		::=	"System.out.println" "(" Expression ")" ";"
Expression		    ::=	AndExpression |	CompareExpression | PlusExpression | MinusExpression | TimesExpression | ArrayLookup | ArrayLength | MessageSend | PrimaryExpression 
AndExpression		::=	PrimaryExpression "&" PrimaryExpression
CompareExpression	::=	PrimaryExpression "<" PrimaryExpression
PlusExpression		::=	PrimaryExpression "+" PrimaryExpression
MinusExpression		::=	PrimaryExpression "-" PrimaryExpression
TimesExpression		::=	PrimaryExpression "*" PrimaryExpression
ArrayLookup		    ::=	PrimaryExpression "[" PrimaryExpression "]"
ArrayLength		    ::=	PrimaryExpression "." "length"
MessageSend		    ::=	PrimaryExpression "." Identifier "(" ( ExpressionList )? ")"
ExpressionList		::=	Expression ( ExpressionRest )*
ExpressionRest		::=	"," Expression
PrimaryExpression	::=	IntegerLiteral | TrueLiteral |	FalseLiteral | Identifier | ThisExpression | ArrayAllocationExpression | AllocationExpression | NotExpression | BracketExpression 
IntegerLiteral		::=	<INTEGER_LITERAL>
TrueLiteral		    ::=	"true"
FalseLiteral		::=	"false"
Identifier		    ::=	<IDENTIFIER>
ThisExpression		::=	"this"
ArrayAllocationExpression ::=	"new" "int" "[" Expression "]"
AllocationExpression	::=	"new" Identifier "(" ")"
NotExpression		::=	"!" Expression
BracketExpression	::=	"(" Expression ")"









