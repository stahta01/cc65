/*****************************************************************************/
/*                                                                           */
/*				   scanner.h				     */
/*                                                                           */
/*		    The scanner for the ca65 macroassembler		     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 1998-2000 Ullrich von Bassewitz                                       */
/*               Wacholderweg 14                                             */
/*               D-70597 Stuttgart                                           */
/* EMail:        uz@musoftware.de                                            */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/



#ifndef SCANNER_H
#define SCANNER_H



/* common */
#include "filepos.h"



/*****************************************************************************/
/*     	       	    	       	     Data				     */
/*****************************************************************************/



/* Tokens */
enum Token {
    TOK_NONE,	 	/* Start value, invalid */
    TOK_EOF,           	/* End of input file */
    TOK_SEP, 	 	/* Separator (usually newline) */
    TOK_IDENT,	 	/* An identifier */
    TOK_MNEMO, 	 	/* A mnemonic */

    TOK_INTCON,  	/* Integer constant */
    TOK_CHARCON, 	/* Character constant */
    TOK_STRCON,		/* String constant */

    TOK_A,		/* A)ccu */
    TOK_X,		/* X register */
    TOK_Y,		/* Y register */
    TOK_S,		/* S register */

    TOK_ULABEL,		/* :++ or :-- */

    TOK_EQ,	 	/* = */
    TOK_NE,	 	/* <> */
    TOK_LT,	 	/* < */
    TOK_GT,  	 	/* > */
    TOK_LE,	 	/* <= */
    TOK_GE,	 	/* >= */

    TOK_BAND,  		/* .and */
    TOK_BOR,		/* .or */
    TOK_BXOR,  		/* .xor */
    TOK_BNOT,		/* .not */

    TOK_PLUS,	 	/* + */
    TOK_MINUS,	 	/* - */
    TOK_MUL,	 	/* * */
    TOK_STAR = TOK_MUL,	/* Alias */
    TOK_DIV,	 	/* / */
    TOK_MOD,	 	/* ! */
    TOK_OR,	 	/* | */
    TOK_XOR,	 	/* ^ */
    TOK_AND,	 	/* & */
    TOK_SHL,	 	/* << */
    TOK_SHR,	 	/* >> */
    TOK_NOT, 		/* ~ */

    TOK_PC,		/* $ if enabled */
    TOK_NAMESPACE,	/* :: */
    TOK_DOT,		/* . */
    TOK_COMMA,		/* , */
    TOK_HASH,		/* # */
    TOK_COLON, 		/* : */
    TOK_LPAREN,		/* ( */
    TOK_RPAREN,		/* ) */
    TOK_LBRACK,		/* [ */
    TOK_RBRACK,	 	/* ] */

    TOK_MACPARAM,	/* Macro parameter, not generated by scanner */
    TOK_REPCOUNTER,	/* Repeat counter, not generated by scanner */

    /* The next ones are tokens for the pseudo instructions. Keep together! */
    TOK_FIRSTPSEUDO,
    TOK_A16	   	= TOK_FIRSTPSEUDO,
    TOK_A8,
    TOK_ADDR,
    TOK_ALIGN,
    TOK_ASCIIZ,
    TOK_AUTOIMPORT,
    TOK_BLANK,
    TOK_BSS,
    TOK_BYTE,
    TOK_CASE,
    TOK_CODE,
    TOK_CONCAT,
    TOK_CONST,
    TOK_CPU,
    TOK_DATA,
    TOK_DBYT,
    TOK_DEBUGINFO,
    TOK_DEFINE,
    TOK_DEFINED,
    TOK_DWORD,
    TOK_ELSE,
    TOK_ELSEIF,
    TOK_END,
    TOK_ENDIF,
    TOK_ENDMACRO,
    TOK_ENDPROC,
    TOK_ENDREP,
    TOK_ERROR,
    TOK_EXITMACRO,
    TOK_EXPORT,
    TOK_EXPORTZP,
    TOK_FARADDR,
    TOK_FEATURE,
    TOK_FILEOPT,
    TOK_FORCEWORD,
    TOK_GLOBAL,
    TOK_GLOBALZP,
    TOK_I16,
    TOK_I8,
    TOK_IF,
    TOK_IFBLANK,
    TOK_IFCONST,
    TOK_IFDEF,
    TOK_IFNBLANK,
    TOK_IFNCONST,
    TOK_IFNDEF,
    TOK_IFNREF,
    TOK_IFP02,
    TOK_IFP816,
    TOK_IFPC02,
    TOK_IFREF,
    TOK_IMPORT,
    TOK_IMPORTZP,
    TOK_INCBIN,
    TOK_INCLUDE,
    TOK_LEFT,
    TOK_LINECONT,
    TOK_LIST,
    TOK_LISTBYTES,
    TOK_LOCAL,
    TOK_LOCALCHAR,
    TOK_MACPACK,
    TOK_MACRO,
    TOK_MATCH,
    TOK_MID,
    TOK_NULL,
    TOK_ORG,
    TOK_OUT,
    TOK_P02,
    TOK_P816,
    TOK_PAGELENGTH,
    TOK_PARAMCOUNT,
    TOK_PC02,
    TOK_PROC,
    TOK_REFERENCED,
    TOK_RELOC,
    TOK_REPEAT,
    TOK_RES,
    TOK_RIGHT,
    TOK_RODATA,
    TOK_SEGMENT,
    TOK_SMART,
    TOK_STRAT,
    TOK_STRING,
    TOK_STRLEN,
    TOK_SUNPLUS,
    TOK_TCOUNT,
    TOK_WARNING,
    TOK_WORD,
    TOK_XMATCH,
    TOK_ZEROPAGE,
    TOK_LASTPSEUDO	= TOK_ZEROPAGE,

    TOK_COUNT  	 	/* Count of tokens */
};



/* Scanner variables */
#define MAX_INPUT_FILES	254		/* No more than this files total */
#define MAX_STR_LEN    	255		/* Maximum length of any string */
extern enum Token Tok;	      	       	/* Current token */
extern int WS; 	 			/* Flag: Whitespace before token */
extern long IVal;      	 		/* Integer token attribute */
extern char SVal [MAX_STR_LEN+1];	/* String token attribute */

extern FilePos 	CurPos;			/* Name and position in file */
extern int     	ForcedEnd;		/* Force end of assembly */



/*****************************************************************************/
/*     	       	       	       	     Code    				     */
/*****************************************************************************/



const char* GetFileName (unsigned char Name);
/* Get the name of a file where the name index is known */

void NewInputFile (const char* Name);
/* Open a new input file */

void DoneInputFile (void);
/* Close the current input file */

void NewInputData (const char* Data, int Malloced);
/* Add a chunk of input data to the input stream */

void UpcaseSVal (void);
/* Make SVal upper case */

void NextRawTok (void);
/* Read the next raw token from the input stream */

int TokHasSVal (enum Token Tok);
/* Return true if the given token has an attached SVal */

int TokHasIVal (enum Token Tok);
/* Return true if the given token has an attached IVal */

int GetSubKey (const char** Keys, unsigned Count);
/* Search for a subkey in a table of keywords. The current token must be an
 * identifier and all keys must be in upper case. The identifier will be
 * uppercased in the process. The function returns the index of the keyword,
 * or -1 if the keyword was not found.
 */

void WriteFiles (void);
/* Write the list of input files to the object file */

void InitScanner (const char* InFile);
/* Initialize the scanner, open the given input file */

void DoneScanner (void);
/* Release scanner resources */



/* End of scanner.h */

#endif



