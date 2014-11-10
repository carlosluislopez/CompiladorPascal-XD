#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum TokenType
{
    Int,
    Float,
    String,
    Char,
    Bool,
    Array,
    Binary,
    Hexadecimal,
    HTML,

    Id,
    EndOfFile,
    Number,
    SemiColon,
    Colon,
    Dot,
    Comma,
    Op_Range,
    LeftParenthesis,
    RightParenthesis,
    LeftBrackets,
    RightBrackets,
    LeftCurlyBrackets,
    RightCurlyBrackets,
    SingleQuote,
    DoubleQuote,

    Op_Assign,
    Op_Sum,
    Op_Substract,
    Op_Multiply,
    Op_Divide,
    Op_Exp,
    Op_Equals,
    Op_NotEquals,
    Op_LessThan,
    Op_GreaterThan,
    Op_LessEqualThan,
    Op_GreaterEqualThan,

    OP_CommentLine,
    OP_CommentBlockOpen,
    OP_CommentBlockClose,
    OP_EscapeCharacter,

    OP_DoublePeriod,
    OP_Hexadecimal,
    OP_Binary,
    OP_LeftxD,
    OP_RightxD,

    Rw_Div,
    Rw_Mod,
    Rw_Not,
    Rw_In,
    Rw_Or,
    Rw_And,
    Rw_If,
    Rw_While,
    Rw_Read,
    Rw_Print,
    Rw_Else,
    Rw_Then,
    Rw_Array,
    Rw_Packed,
    Rw_To,
    Rw_Begin,
    Rw_End,
    Rw_Of,
    Rw_Record,
    Rw_Type,
    Rw_For,
    Rw_Label,
    Rw_Repeat,
    Rw_With,
    Rw_Const,
    Rw_Case,
    Rw_Function,
    Rw_Procedure,
    Rw_Program,
    Rw_Until,
    Rw_Do,
    Rw_True,
    Rw_False,
    Rw_Int,
    Rw_Float,
    Rw_String,
    Rw_Char,
    Rw_Bool,
    Rw_Downto,
    Rw_Var,
    Rw_Get,
    Rw_Post,
    Rw_Integer,
    Rw_Real
};

class Token
{
public:
    Token(){}
    ~Token(){}
    TokenType Type;
    string Lexeme;
    string LexemeValue;
    unsigned int Column;
    unsigned int Line;
};

#endif // TOKEN_H
