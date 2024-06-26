/*
 * generated by ./tinfo/MKuserdefs.sh
 */

/*
 *    comp_userdefs.c -- The names of widely used user-defined capabilities
 *                       indexed via a hash table for the compiler.
 *
 */

#include "curses.priv.h"
#include "tic.h"
#include "hashsize.h"

#if NCURSES_XNAMES
/* 11 collisions out of 100 entries */
static const char user_names_text[] = \
"CO\0" "E3\0" "NQ\0" "RGB\0" "TS\0" "U8\0" "XM\0" "grbom\0" "gsbom\0" \
"xm\0" "Rmol\0" "Smol\0" "blink2\0" "norm\0" "opaq\0" "setal\0" \
"smul2\0" "AN\0" "AX\0" "C0\0" "C8\0" "CE\0" "CS\0" "E0\0" "G0\0" \
"KJ\0" "OL\0" "S0\0" "TF\0" "WS\0" "XC\0" "XT\0" "Z0\0" "Z1\0" "Cr\0" \
"Cs\0" "Csr\0" "Ms\0" "Se\0" "Smulx\0" "Ss\0" "rmxx\0" "smxx\0" "csl\0" \
"kDC3\0" "kDC4\0" "kDC5\0" "kDC6\0" "kDC7\0" "kDN\0" "kDN3\0" "kDN4\0" \
"kDN5\0" "kDN6\0" "kDN7\0" "kEND3\0" "kEND4\0" "kEND5\0" "kEND6\0" \
"kEND7\0" "kHOM3\0" "kHOM4\0" "kHOM5\0" "kHOM6\0" "kHOM7\0" "kIC3\0" \
"kIC4\0" "kIC5\0" "kIC6\0" "kIC7\0" "kLFT3\0" "kLFT4\0" "kLFT5\0" \
"kLFT6\0" "kLFT7\0" "kNXT3\0" "kNXT4\0" "kNXT5\0" "kNXT6\0" "kNXT7\0" \
"kPRV3\0" "kPRV4\0" "kPRV5\0" "kPRV6\0" "kPRV7\0" "kRIT3\0" "kRIT4\0" \
"kRIT5\0" "kRIT6\0" "kRIT7\0" "kUP\0" "kUP3\0" "kUP4\0" "kUP5\0" \
"kUP6\0" "kUP7\0" "ka2\0" "kb1\0" "kb3\0" "kc2\0" ;

static user_table_data const user_names_data[] =
{
	{               0,	(1<<NUMBER),	0,0,	  0,  -1 },
	{               3,	(1<<STRING),	0,0,	  0,  -1 },
	{               6,	(1<<BOOLEAN),	0,0,	  0,  -1 },
	{               9,	(1<<BOOLEAN|1<<NUMBER|1<<STRING),	0,0,	  1,  -1 },
	{              13,	(1<<STRING),	0,0,	  2,  -1 },
	{              16,	(1<<NUMBER),	0,0,	  2,  -1 },
	{              19,	(1<<STRING),	1,0,	  3,  -1 },
	{              22,	(1<<STRING),	0,0,	  4,  -1 },
	{              28,	(1<<STRING),	0,0,	  5,  -1 },
	{              34,	(1<<STRING),	8,8,	 14,  -1 },
	{              37,	(1<<STRING),	0,0,	 15,  -1 },
	{              42,	(1<<STRING),	0,0,	 16,  -1 },
	{              47,	(1<<STRING),	0,0,	 17,  -1 },
	{              54,	(1<<STRING),	0,0,	 18,  -1 },
	{              59,	(1<<STRING),	0,0,	 19,  -1 },
	{              64,	(1<<STRING),	1,0,	 20,  -1 },
	{              70,	(1<<STRING),	0,0,	 21,  -1 },
	{              76,	(1<<BOOLEAN),	0,0,	  2,  -1 },
	{              79,	(1<<BOOLEAN),	0,0,	  3,  -1 },
	{              82,	(1<<STRING),	0,0,	 22,  -1 },
	{              85,	(1<<BOOLEAN),	0,0,	  4,  -1 },
	{              88,	(1<<STRING),	0,0,	 23,  -1 },
	{              91,	(1<<STRING),	0,0,	 24,  -1 },
	{              94,	(1<<STRING),	0,0,	 25,  -1 },
	{              97,	(1<<BOOLEAN),	0,0,	  5,  -1 },
	{             100,	(1<<STRING),	1,1,	 26,  -1 },
	{             103,	(1<<NUMBER),	0,0,	  3,  -1 },
	{             106,	(1<<STRING),	1,1,	 27,  -1 },
	{             109,	(1<<BOOLEAN),	0,0,	  6,  -1 },
	{             112,	(1<<STRING),	2,0,	 28,  -1 },
	{             115,	(1<<STRING),	1,1,	 29,  -1 },
	{             118,	(1<<BOOLEAN),	0,0,	  7,  -1 },
	{             121,	(1<<STRING),	0,0,	 30,  -1 },
	{             124,	(1<<STRING),	0,0,	 31,  -1 },
	{             127,	(1<<STRING),	0,0,	 32,  -1 },
	{             130,	(1<<STRING),	1,1,	 33,  -1 },
	{             133,	(1<<STRING),	1,0,	 34,  -1 },
	{             137,	(1<<STRING),	2,3,	 35,  -1 },
	{             140,	(1<<STRING),	0,0,	 36,  -1 },
	{             143,	(1<<STRING),	1,0,	 37,  -1 },
	{             149,	(1<<STRING),	1,0,	 38,  -1 },
	{             152,	(1<<STRING),	0,0,	 39,  -1 },
	{             157,	(1<<STRING),	0,0,	 40,  -1 },
	{             162,	(1<<STRING),	0,0,	 41,  -1 },
	{             166,	(1<<STRING),	0,0,	 42,  -1 },
	{             171,	(1<<STRING),	0,0,	 43,  -1 },
	{             176,	(1<<STRING),	0,0,	 44,  -1 },
	{             181,	(1<<STRING),	0,0,	 45,  -1 },
	{             186,	(1<<STRING),	0,0,	 46,  17 },
	{             191,	(1<<STRING),	0,0,	 47,  -1 },
	{             195,	(1<<STRING),	0,0,	 48,  -1 },
	{             200,	(1<<STRING),	0,0,	 49,  -1 },
	{             205,	(1<<STRING),	0,0,	 50,  -1 },
	{             210,	(1<<STRING),	0,0,	 51,  18 },
	{             215,	(1<<STRING),	0,0,	 52,  -1 },
	{             220,	(1<<STRING),	0,0,	 53,  -1 },
	{             226,	(1<<STRING),	0,0,	 54,  -1 },
	{             232,	(1<<STRING),	0,0,	 55,  16 },
	{             238,	(1<<STRING),	0,0,	 56,  -1 },
	{             244,	(1<<STRING),	0,0,	 57,  -1 },
	{             250,	(1<<STRING),	0,0,	 58,  -1 },
	{             256,	(1<<STRING),	0,0,	 59,  -1 },
	{             262,	(1<<STRING),	0,0,	 60,  -1 },
	{             268,	(1<<STRING),	0,0,	 61,  -1 },
	{             274,	(1<<STRING),	0,0,	 62,  -1 },
	{             280,	(1<<STRING),	0,0,	 63,  -1 },
	{             285,	(1<<STRING),	0,0,	 64,  -1 },
	{             290,	(1<<STRING),	0,0,	 65,  -1 },
	{             295,	(1<<STRING),	0,0,	 66,  -1 },
	{             300,	(1<<STRING),	0,0,	 67,  -1 },
	{             305,	(1<<STRING),	0,0,	 68,  62 },
	{             311,	(1<<STRING),	0,0,	 69,  63 },
	{             317,	(1<<STRING),	0,0,	 70,  64 },
	{             323,	(1<<STRING),	0,0,	 71,  -1 },
	{             329,	(1<<STRING),	0,0,	 72,  -1 },
	{             335,	(1<<STRING),	0,0,	 73,  -1 },
	{             341,	(1<<STRING),	0,0,	 74,  -1 },
	{             347,	(1<<STRING),	0,0,	 75,  -1 },
	{             353,	(1<<STRING),	0,0,	 76,  -1 },
	{             359,	(1<<STRING),	0,0,	 77,  -1 },
	{             365,	(1<<STRING),	0,0,	 78,  -1 },
	{             371,	(1<<STRING),	0,0,	 79,  -1 },
	{             377,	(1<<STRING),	0,0,	 80,  75 },
	{             383,	(1<<STRING),	0,0,	 81,  76 },
	{             389,	(1<<STRING),	0,0,	 82,  77 },
	{             395,	(1<<STRING),	0,0,	 83,  -1 },
	{             401,	(1<<STRING),	0,0,	 84,  -1 },
	{             407,	(1<<STRING),	0,0,	 85,  -1 },
	{             413,	(1<<STRING),	0,0,	 86,  -1 },
	{             419,	(1<<STRING),	0,0,	 87,  -1 },
	{             425,	(1<<STRING),	0,0,	 88,  -1 },
	{             429,	(1<<STRING),	0,0,	 89,  -1 },
	{             434,	(1<<STRING),	0,0,	 90,  -1 },
	{             439,	(1<<STRING),	0,0,	 91,  -1 },
	{             444,	(1<<STRING),	0,0,	 92,  -1 },
	{             449,	(1<<STRING),	0,0,	 93,  -1 },
	{             454,	(1<<STRING),	0,0,	 94,  -1 },
	{             458,	(1<<STRING),	0,0,	 95,  96 },
	{             462,	(1<<STRING),	0,0,	 96,  -1 },
	{             466,	(1<<STRING),	0,0,	 97,  98 } 
};

static struct user_table_entry *_nc_user_table = 0;

static const HashValue _nc_user_hash_table[995] =
{
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 67,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 71,
	 -1,
	  2,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 50,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  8,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 54,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 85,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 97,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 89,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 56,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 28,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 83,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 38,
	 44,
	 -1,
	 -1,
	 -1,
	 -1,
	 12,
	 -1,
	 -1,
	 -1,
	 -1,
	 25,
	 -1,
	 -1,
	 -1,
	 -1,
	 92,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 15,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 48,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 60,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 68,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 36,
	 -1,
	 72,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 51,
	 -1,
	  9,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 86,
	 -1,
	 -1,
	 41,
	 42,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 14,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 57,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 30,
	 -1,
	 -1,
	 80,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 84,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 45,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 39,
	 13,
	 -1,
	 -1,
	 -1,
	 -1,
	 93,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 19,
	 -1,
	 23,
	 -1,
	 24,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 65,
	 -1,
	  0,
	 27,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 32,
	 61,
	 -1,
	  3,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 69,
	 -1,
	 22,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 73,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 34,
	 -1,
	  4,
	 -1,
	 20,
	 29,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 52,
	 -1,
	 -1,
	 -1,
	 -1,
	  5,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 87,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 99,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 58,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 81,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 78,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 46,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 26,
	 94,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 66,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 43,
	 -1,
	 -1,
	 33,
	 70,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 90,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 74,
	 -1,
	 -1,
	  7,
	 -1,
	 -1,
	 35,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 31,
	 -1,
	 -1,
	 -1,
	 37,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 40,
	 53,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 49,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 88,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 55,
	 -1,
	 -1,
	 -1,
	 -1,
	 10,
	 11,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 21,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 59,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 82,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 91,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 79,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 47,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 95,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  6,
	 -1,
	 -1,
	0	/* base-of-table */
};


#define USERTABSIZE SIZEOF(user_names_data)

#if 1
static void
next_string(const char *strings, unsigned *offset)
{
    *offset += (unsigned) strlen(strings + *offset) + 1;
}

static const struct user_table_entry *
_nc_build_names(struct user_table_entry **actual,
		const user_table_data *source,
		const char *strings)
{
    if (*actual == 0) {
	*actual = typeCalloc(struct user_table_entry, USERTABSIZE);
	if (*actual != 0) {
	    unsigned n;
	    unsigned len = 0;
	    for (n = 0; n < USERTABSIZE; ++n) {
		(*actual)[n].ute_name = strings + len;
		(*actual)[n].ute_type = (int) source[n].ute_type;
		(*actual)[n].ute_argc = source[n].ute_argc;
		(*actual)[n].ute_args = source[n].ute_args;
		(*actual)[n].ute_index = source[n].ute_index;
		(*actual)[n].ute_link = source[n].ute_link;
		next_string(strings, &len);
	    }
	}
    }
    return *actual;
}

#define build_names(root) _nc_build_names(&_nc_##root##_table, \
					  root##_names_data, \
					  root##_names_text)
#else
#define build_names(root) _nc_ ## root ## _table
#endif

NCURSES_EXPORT(const struct user_table_entry *) _nc_get_userdefs_table (void)
{
    return build_names(user) ;
}

static HashValue
info_hash(const char *string)
{
    long sum = 0;

    DEBUG(9, ("hashing %s", string));
    while (*string) {
	sum += (long) (*string + (*(string + 1) << 8));
	string++;
    }

    DEBUG(9, ("sum is %ld", sum));
    return (HashValue) (sum % HASHTABSIZE);
}

static int
compare_info_names(const char *a, const char *b)
{
    return !strcmp(a, b);
}

static const HashData hash_data[] = {
    { HASHTABSIZE, _nc_user_hash_table, info_hash, compare_info_names }
};

NCURSES_EXPORT(const HashData *) _nc_get_hash_user (void)
{
    return hash_data;
}

#if NO_LEAKS
NCURSES_EXPORT(void) _nc_comp_userdefs_leaks(void)
{
#if 1
    FreeIfNeeded(_nc_user_table);
#endif
}
#endif /* NO_LEAKS */

#else /*! NCURSES_XNAMES */
NCURSES_EXPORT(void) _nc_comp_userdefs(void);
NCURSES_EXPORT(void) _nc_comp_userdefs(void) { }
#endif /* NCURSES_XNAMES */
