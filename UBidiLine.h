#ifndef _UBIDILINE_H
#define _UBIDILINE_H 1

#include <windows.h>
#include "ortaq.h"

#define L		0 /** Left-to-right*/
#define LRE		1 /** Left-to-Right Embedding */
#define LRO		2 /** Left-to-Right Override */
#define R		3 /** Right-to-Left */
#define AL		4 /** Right-to-Left Arabic */
#define RLE		5 /** Right-to-Left Embedding */
#define RLO		6 /** Right-to-Left Override */
#define PDF		7 /** Pop Directional Format */
#define EN		8 /** European Number */
#define ES		9 /** European Number Separator */
#define ET		10 /** European Number Terminator */
#define AN		11 /** Arabic Number */
#define CS		12 /** Common Number Separator */
#define NSM		13 /** Non-Spacing Mark */
#define BN		14 /** Boundary Neutral */
#define B		15 /** Paragraph Separator */
#define S		16 /** Segment Separator */
#define WS		17 /** Whitespace */
#define ON		18 /** Other Neutrals */
#define TYPE_MIN    0 /** Minimum bidi type value. */
#define TYPE_MAX	18 /** Maximum bidi type value. */
#define  EXPLICIT_LEVEL_LIMIT  62

#define MY_MAX(a, b) (a > b ? a: b)

class UBidiLine
{
private:
	char *initialTypes;
	char *embeddings; // generated from processing format codes
	char paragraphEmbeddingLevel; // undefined
	
	int textLength; // for convenience
	char *resultTypes; // for paragraph, not lines
	char *resultLevels; // for paragraph, not lines
	int *resultIndex;
	char rtypes[0x10000];
	char embeddingValueStack[EXPLICIT_LEVEL_LIMIT];
	void Init();
	void runAlgorithm();
	void Reordering();
	char getDirection(wchar_t c) ;
	void determineExplicitEmbeddingLevels();
	int removeExplicitCodes();
	void determineParagraphEmbeddingLevel();
	void reinsertExplicitCodes(int tLen);
	void processEmbeddings();
	char typeForLevel(int level);
	void resolveWeakTypes(int start, int limit, char level, char sor, char eor);
	void resolveNeutralTypes(int start, int limit, char level, char sor, char eor);
	void resolveImplicitLevels(int start, int limit, char level, char sor, char eor);
	int  findRunLimit(int index, int limit, char *validSet);
	void setTypes(int start, int limit, char newType);
	bool isWhitespace(char biditype) ;

public:
	UBidiLine();
	virtual ~UBidiLine();
	wchar_t *ReorderLine(wchar_t *text, BOOL RTL);
	int *getVisualOrder(wchar_t *text, BOOL RTL);
	wchar_t Mirror(wchar_t c);
};

#endif

