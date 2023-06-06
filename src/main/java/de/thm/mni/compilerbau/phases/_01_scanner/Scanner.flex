package de.thm.mni.compilerbau.phases._01_scanner;

import de.thm.mni.compilerbau.utils.SplError;
import de.thm.mni.compilerbau.phases._02_03_parser.Sym;
import de.thm.mni.compilerbau.absyn.Position;
import de.thm.mni.compilerbau.table.Identifier;
import de.thm.mni.compilerbau.CommandLineOptions;
import java_cup.runtime.*;

%%


%class Scanner
%public
%line
%column
%cup
%eofval{
    return new java_cup.runtime.Symbol(Sym.EOF, yyline + 1, yycolumn + 1);   //This needs to be specified when using a custom sym class name
%eofval}

%{
    public CommandLineOptions options = null;
  
    private Symbol symbol(int type) {
      return new Symbol(type, yyline + 1, yycolumn + 1);
    }

    private Symbol symbol(int type, Object value) {
      return new Symbol(type, yyline + 1, yycolumn + 1, value);
    }
%}

// TODO (assignment 1): The regular expressions for all tokens need to be defined here.

/* declare macros */
Identifier = [:jletter:] [:jletterdigit:]*
DecIntegerLiteral = 0 | [1-9][0-9]*
HexIntegerLiteral = [0x] [0-9A-Fa-f]+
AnyLiteral = ['] {InputCharacter}* [']

WhiteSpace     = {LineTerminator} | [ \t\f]
LineTerminator = [\r] | [\n] | [\r\n]
InputCharacter = [^\r\n]

Comment = {TraditionalComment} | {EndOfLineComment} | {DocumentationComment}
TraditionalComment   = "/*" [^*] ~"*/" | "/*" "*"+ "/"
EndOfLineComment     = "//" {InputCharacter}* {LineTerminator}?
DocumentationComment = "/**" {CommentContent} "*"+ "/"
CommentContent       = ( [^*] | \*+ [^/*] )*

%%

/* keywords */
<YYINITIAL> "array"             { return symbol(Sym.ARRAY); }
<YYINITIAL> "else"              { return symbol(Sym.ELSE); }
<YYINITIAL> "if"                { return symbol(Sym.IF); }
<YYINITIAL> "of"                { return symbol(Sym.OF); }
<YYINITIAL> "proc"              { return symbol(Sym.PROC); }
<YYINITIAL> "ref"               { return symbol(Sym.REF); }
<YYINITIAL> "type"              { return symbol(Sym.TYPE); }
<YYINITIAL> "var"               { return symbol(Sym.VAR); }
<YYINITIAL> "while"             { return symbol(Sym.WHILE); }

<YYINITIAL> {
  /* identifiers */
  {Identifier}                  { return symbol(Sym.IDENT); }

  /* literals */
  {DecIntegerLiteral}           { return symbol(Sym.INTLIT); }
  {HexIntegerLiteral}           { return symbol(Sym.INTLIT); }
  {AnyLiteral}                  { return symbol(Sym.INTLIT); }

  /* operators */
  "<"                           { return symbol(Sym.LT); }
  "#"                           { return symbol(Sym.NE); }
  ":="                          { return symbol(Sym.ASGN); }
  "+"                           { return symbol(Sym.PLUS); }
  "/"                           { return symbol(Sym.SLASH); }
  "*"                           { return symbol(Sym.STAR); }
  ">"                           { return symbol(Sym.GT); }
  "<="                          { return symbol(Sym.LE); }
  "-"                           { return symbol(Sym.MINUS); }
  ">="                          { return symbol(Sym.GE); }
  "="                           { return symbol(Sym.EQ); }

  /* brackets */
  "("                           { return symbol(Sym.LPAREN); }
  ")"                           { return symbol(Sym.RPAREN); }
  "["                           { return symbol(Sym.LBRACK); }
  "]"                           { return symbol(Sym.RBRACK); }
  "{"                           { return symbol(Sym.LCURL); }
  "}"                           { return symbol(Sym.RCURL); }

  /* other */
  ":"                           { return symbol(Sym.COLON); }
  ";"                           { return symbol(Sym.SEMIC); }
  ","                           { return symbol(Sym.COMMA);}

  /* comments */
  {Comment}                     { /* ignore */ }

  /* whitespace */
  {WhiteSpace}                  { /* ignore */ }
}

/* error fallback */
[^]		{throw SplError.IllegalCharacter(new Position(yyline + 1, yycolumn + 1), yytext().charAt(0));}

/*
ressources:
https://www.jflex.de/manual.html#ExampleOptions
*/