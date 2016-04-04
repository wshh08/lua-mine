/*
** $Id: llex.h,v 1.78 2014/10/29 15:38:24 roberto Exp $
** Lexical Analyzer
** See Copyright Notice in lua.h
*/

#ifndef llex_h
#define llex_h

#include "lobject.h"
#include "lzio.h"


#define FIRST_RESERVED	257


#if !defined(LUA_ENV)
#define LUA_ENV		"_ENV"
#endif


/*
* WARNING: if you change the order of this enumeration,
* grep "ORDER RESERVED"
*/
/**
 * @brief token类型枚举变量，从FIRST_RESERVED=257开始.
 * lua里面的token大致分为：\n
 * 1. 数字和字符串\n
 * 2. 特殊字符：包括运算符和括号\n
 * 3. 关键词\n
 * 对于每一类token lua都有唯一的id与之对应，此id用int来表示，
 * 对于第2种类型，直接用该字符的ASCII码来表示，
 * 对于1,3两类，则定义一组枚举，为了与第2种区别开，枚举从257开始。
 * 比如关键字break对应TK_BREAK， do对应TK_DO
 * */
enum RESERVED {
  /* terminal symbols denoted by reserved words */
  TK_AND = FIRST_RESERVED, TK_BREAK,
  TK_DO, TK_ELSE, TK_ELSEIF, TK_END, TK_FALSE, TK_FOR, TK_FUNCTION,
  TK_GOTO, TK_IF, TK_IN, TK_LOCAL, TK_NIL, TK_NOT, TK_OR, TK_REPEAT,
  TK_RETURN, TK_THEN, TK_TRUE, TK_UNTIL, TK_WHILE,
  /* other terminal symbols */
  TK_IDIV, TK_CONCAT, TK_DOTS, TK_EQ, TK_GE, TK_LE, TK_NE,
  TK_SHL, TK_SHR,
  TK_DBCOLON, TK_EOS,
  TK_FLT, TK_INT, TK_NAME, TK_STRING
};

/* number of reserved words */
#define NUM_RESERVED	(cast(int, TK_WHILE-FIRST_RESERVED+1))

/**
 * @brief 代表语义信息的结构体
 * */
typedef union {
  lua_Number r;
  lua_Integer i;
  TString *ts;
} SemInfo;  /* semantics information */

/**
 * @brief Token代表一个单词，其中token成员代表单词的类型，seminfo代表单词的语义信息
 * */
typedef struct Token {
  int token;
  SemInfo seminfo;
} Token;


/**
 * @brief state of the lexer plus state of the parser when shared by all
   functions. LexState不仅用于保存当前的词法分析状态信息，而且也保存了整个编译系统的全局状态.
 */
typedef struct LexState {
  int current;  /* current character (charint) */
  int linenumber;  /* input line counter */
  int lastline;  /* line of last token 'consumed' */
  Token t;  /* current token */
  Token lookahead;  /* look ahead token */
  struct FuncState *fs;  /* current function (parser) */
  struct lua_State *L;
  ZIO *z;  /* input stream */
  Mbuffer *buff;  /* buffer for tokens */
  Table *h;  /* to avoid collection/reuse strings */
  struct Dyndata *dyd;  /* dynamic structures used by the parser */
  TString *source;  /* current source name */
  TString *envn;  /* environment variable name */
  char decpoint;  /* locale decimal point */
} LexState;


LUAI_FUNC void luaX_init (lua_State *L);
LUAI_FUNC void luaX_setinput (lua_State *L, LexState *ls, ZIO *z,
                              TString *source, int firstchar);
LUAI_FUNC TString *luaX_newstring (LexState *ls, const char *str, size_t l);
LUAI_FUNC void luaX_next (LexState *ls);
LUAI_FUNC int luaX_lookahead (LexState *ls);
LUAI_FUNC l_noret luaX_syntaxerror (LexState *ls, const char *s);
LUAI_FUNC const char *luaX_token2str (LexState *ls, int token);


#endif
