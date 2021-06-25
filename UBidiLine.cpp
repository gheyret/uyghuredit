#include "UBidiLine.h"

UBidiLine::UBidiLine()
{
	initialTypes=NULL;
	embeddings=NULL; // generated from processing format codes
	paragraphEmbeddingLevel=0; // undefined

	textLength=0; // for convenience
	resultTypes=NULL; // for paragraph, not lines
	resultLevels=NULL; // for paragraph, not lines
	resultIndex=NULL;
	Init();
}

UBidiLine::~UBidiLine()
{
	if(initialTypes!=NULL)
	{
		delete[] initialTypes;
		delete[] resultTypes;
		delete[] resultLevels;
		delete[] embeddings;

		initialTypes=NULL;
		resultTypes=NULL;
		resultIndex=NULL;
		resultLevels=NULL;
		embeddings=NULL;
	}
}


wchar_t *UBidiLine::ReorderLine(wchar_t *text, BOOL RTL)
{
	if(text==NULL) return text;
	textLength=wcslen(text);
	if(textLength==0) return text;
	paragraphEmbeddingLevel = 0;
	if(RTL)
	{
		paragraphEmbeddingLevel = 1;
	}
	if(initialTypes!=NULL)
	{
		delete[] initialTypes;
		delete[] resultTypes;
		delete[] resultLevels;
		delete[] embeddings;
	}
	initialTypes = new char[textLength];
	resultTypes=new char[textLength];
	resultIndex=new int[textLength];
	resultLevels = new char[textLength];
	embeddings = new char[textLength];

	for (int k = 0; k < textLength; k++)
	{
		initialTypes[k] = rtypes[text[k]];
		resultTypes[k] = initialTypes[k];
		resultLevels[k] = paragraphEmbeddingLevel;
		resultIndex[k] = k;
	}

	runAlgorithm();

	Reordering();
	wchar_t *visualChar=new wchar_t [textLength];
	int idx = 0;
	if(RTL)
	{
		for (int i=0; i<textLength; i++)
		{
			idx = resultIndex[i];
			visualChar[i]=Mirror(text[idx]);
		}
	}
	else
	{
		for (int i=0; i<textLength; i++)
		{
			idx = resultIndex[i];
			visualChar[i]=text[idx];
		}
	}
	visualChar[textLength]=0x0;
	return visualChar;
}

int *UBidiLine::getVisualOrder(wchar_t *text, BOOL RTL)

{
	if(text==NULL) return NULL;
	textLength=wcslen(text);
	if(textLength==0) return NULL;
	paragraphEmbeddingLevel = 0;
	if(RTL)
	{
		paragraphEmbeddingLevel = 1;
	}
	if(initialTypes!=NULL)
	{
		delete[] initialTypes;
		delete[] resultTypes;
		delete[] resultLevels;
		delete[] embeddings;
	}
	initialTypes = new char[textLength];
	resultTypes=new char[textLength];
	resultIndex=new int[textLength];
	resultLevels = new char[textLength];
	embeddings = new char[textLength];

	for (int k = 0; k < textLength; k++)
	{
		initialTypes[k] = rtypes[text[k]];
		resultTypes[k] = initialTypes[k];
		resultLevels[k] = paragraphEmbeddingLevel;
		resultIndex[k] = k;
	}
	runAlgorithm();
	Reordering();
	return resultIndex;
}

wchar_t UBidiLine::Mirror(wchar_t c)
{
	wchar_t ret;
	switch(c)
	{
	case  0x0028:
		ret= 0x0029; // LEFT PARENTHESIS
		break;
	case  0x0029:
		ret= 0x0028; // RIGHT PARENTHESIS
		break;
	case  0x003C:
		ret= 0x003E; // LESS-THAN SIGN
		break;
	case  0x003E:
		ret= 0x003C; // GREATER-THAN SIGN
		break;
	case  0x005B:
		ret= 0x005D; // LEFT SQUARE BRACKET
		break;
	case  0x005D:
		ret= 0x005B; // RIGHT SQUARE BRACKET
		break;
	case  0x007B:
		ret= 0x007D; // LEFT CURLY BRACKET
		break;
	case  0x007D:
		ret= 0x007B; // RIGHT CURLY BRACKET
		break;
	case  0x00AB:
		ret= 0x00BB; // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
		break;
	case  0x00BB:
		ret= 0x00AB; // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
		break;
	case  0x2039:
		ret= 0x203A; // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
		break;
	case  0x203A:
		ret= 0x2039; // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
		break;
	case  0x2045:
		ret= 0x2046; // LEFT SQUARE BRACKET WITH QUILL
		break;
	case  0x2046:
		ret= 0x2045; // RIGHT SQUARE BRACKET WITH QUILL
		break;
	case  0x207D:
		ret= 0x207E; // SUPERSCRIPT LEFT PARENTHESIS
		break;
	case  0x207E:
		ret= 0x207D; // SUPERSCRIPT RIGHT PARENTHESIS
		break;
	case  0x208D:
		ret= 0x208E; // SUBSCRIPT LEFT PARENTHESIS
		break;
	case  0x208E:
		ret= 0x208D; // SUBSCRIPT RIGHT PARENTHESIS
		break;
	case  0x2208:
		ret= 0x220B; // ELEMENT OF
		break;
	case  0x2209:
		ret= 0x220C; // NOT AN ELEMENT OF
		break;
	case  0x220A:
		ret= 0x220D; // SMALL ELEMENT OF
		break;
	case  0x220B:
		ret= 0x2208; // CONTAINS AS MEMBER
		break;
	case  0x220C:
		ret= 0x2209; // DOES NOT CONTAIN AS MEMBER
		break;
	case  0x220D:
		ret= 0x220A; // SMALL CONTAINS AS MEMBER
		break;
	case  0x2215:
		ret= 0x29F5; // DIVISION SLASH
		break;
	case  0x223C:
		ret= 0x223D; // TILDE OPERATOR
		break;
	case  0x223D:
		ret= 0x223C; // REVERSED TILDE
		break;
	case  0x2243:
		ret= 0x22CD; // ASYMPTOTICALLY EQUAL TO
		break;
	case  0x2252:
		ret= 0x2253; // APPROXIMATELY EQUAL TO OR THE IMAGE OF
		break;
	case  0x2253:
		ret= 0x2252; // IMAGE OF OR APPROXIMATELY EQUAL TO
		break;
	case  0x2254:
		ret= 0x2255; // COLON EQUALS
		break;
	case  0x2255:
		ret= 0x2254; // EQUALS COLON
		break;
	case  0x2264:
		ret= 0x2265; // LESS-THAN OR EQUAL TO
		break;
	case  0x2265:
		ret= 0x2264; // GREATER-THAN OR EQUAL TO
		break;
	case  0x2266:
		ret= 0x2267; // LESS-THAN OVER EQUAL TO
		break;
	case  0x2267:
		ret= 0x2266; // GREATER-THAN OVER EQUAL TO
		break;
	case  0x2268:
		ret= 0x2269; // [BEST FIT] LESS-THAN BUT NOT EQUAL TO
		break;
	case  0x2269:
		ret= 0x2268; // [BEST FIT] GREATER-THAN BUT NOT EQUAL TO
		break;
	case  0x226A:
		ret= 0x226B; // MUCH LESS-THAN
		break;
	case  0x226B:
		ret= 0x226A; // MUCH GREATER-THAN
		break;
	case  0x226E:
		ret= 0x226F; // [BEST FIT] NOT LESS-THAN
		break;
	case  0x226F:
		ret= 0x226E; // [BEST FIT] NOT GREATER-THAN
		break;
	case  0x2270:
		ret= 0x2271; // [BEST FIT] NEITHER LESS-THAN NOR EQUAL TO
		break;
	case  0x2271:
		ret= 0x2270; // [BEST FIT] NEITHER GREATER-THAN NOR EQUAL TO
		break;
	case  0x2272:
		ret= 0x2273; // [BEST FIT] LESS-THAN OR EQUIVALENT TO
		break;
	case  0x2273:
		ret= 0x2272; // [BEST FIT] GREATER-THAN OR EQUIVALENT TO
		break;
	case  0x2274:
		ret= 0x2275; // [BEST FIT] NEITHER LESS-THAN NOR EQUIVALENT TO
		break;
	case  0x2275:
		ret= 0x2274; // [BEST FIT] NEITHER GREATER-THAN NOR EQUIVALENT TO
		break;
	case  0x2276:
		ret= 0x2277; // LESS-THAN OR GREATER-THAN
		break;
	case  0x2277:
		ret= 0x2276; // GREATER-THAN OR LESS-THAN
		break;
	case  0x2278:
		ret= 0x2279; // NEITHER LESS-THAN NOR GREATER-THAN
		break;
	case  0x2279:
		ret= 0x2278; // NEITHER GREATER-THAN NOR LESS-THAN
		break;
	case  0x227A:
		ret= 0x227B; // PRECEDES
		break;
	case  0x227B:
		ret= 0x227A; // SUCCEEDS
		break;
	case  0x227C:
		ret= 0x227D; // PRECEDES OR EQUAL TO
		break;
	case  0x227D:
		ret= 0x227C; // SUCCEEDS OR EQUAL TO
		break;
	case  0x227E:
		ret= 0x227F; // [BEST FIT] PRECEDES OR EQUIVALENT TO
		break;
	case  0x227F:
		ret= 0x227E; // [BEST FIT] SUCCEEDS OR EQUIVALENT TO
		break;
	case  0x2280:
		ret= 0x2281; // [BEST FIT] DOES NOT PRECEDE
		break;
	case  0x2281:
		ret= 0x2280; // [BEST FIT] DOES NOT SUCCEED
		break;
	case  0x2282:
		ret= 0x2283; // SUBSET OF
		break;
	case  0x2283:
		ret= 0x2282; // SUPERSET OF
		break;
	case  0x2284:
		ret= 0x2285; // [BEST FIT] NOT A SUBSET OF
		break;
	case  0x2285:
		ret= 0x2284; // [BEST FIT] NOT A SUPERSET OF
		break;
	case  0x2286:
		ret= 0x2287; // SUBSET OF OR EQUAL TO
		break;
	case  0x2287:
		ret= 0x2286; // SUPERSET OF OR EQUAL TO
		break;
	case  0x2288:
		ret= 0x2289; // [BEST FIT] NEITHER A SUBSET OF NOR EQUAL TO
		break;
	case  0x2289:
		ret= 0x2288; // [BEST FIT] NEITHER A SUPERSET OF NOR EQUAL TO
		break;
	case  0x228A:
		ret= 0x228B; // [BEST FIT] SUBSET OF WITH NOT EQUAL TO
		break;
	case  0x228B:
		ret= 0x228A; // [BEST FIT] SUPERSET OF WITH NOT EQUAL TO
		break;
	case  0x228F:
		ret= 0x2290; // SQUARE IMAGE OF
		break;
	case  0x2290:
		ret= 0x228F; // SQUARE ORIGINAL OF
		break;
	case  0x2291:
		ret= 0x2292; // SQUARE IMAGE OF OR EQUAL TO
		break;
	case  0x2292:
		ret= 0x2291; // SQUARE ORIGINAL OF OR EQUAL TO
		break;
	case  0x2298:
		ret= 0x29B8; // CIRCLED DIVISION SLASH
		break;
	case  0x22A2:
		ret= 0x22A3; // RIGHT TACK
		break;
	case  0x22A3:
		ret= 0x22A2; // LEFT TACK
		break;
	case  0x22A6:
		ret= 0x2ADE; // ASSERTION
		break;
	case  0x22A8:
		ret= 0x2AE4; // TRUE
		break;
	case  0x22A9:
		ret= 0x2AE3; // FORCES
		break;
	case  0x22AB:
		ret= 0x2AE5; // DOUBLE VERTICAL BAR DOUBLE RIGHT TURNSTILE
		break;
	case  0x22B0:
		ret= 0x22B1; // PRECEDES UNDER RELATION
		break;
	case  0x22B1:
		ret= 0x22B0; // SUCCEEDS UNDER RELATION
		break;
	case  0x22B2:
		ret= 0x22B3; // NORMAL SUBGROUP OF
		break;
	case  0x22B3:
		ret= 0x22B2; // CONTAINS AS NORMAL SUBGROUP
		break;
	case  0x22B4:
		ret= 0x22B5; // NORMAL SUBGROUP OF OR EQUAL TO
		break;
	case  0x22B5:
		ret= 0x22B4; // CONTAINS AS NORMAL SUBGROUP OR EQUAL TO
		break;
	case  0x22B6:
		ret= 0x22B7; // ORIGINAL OF
		break;
	case  0x22B7:
		ret= 0x22B6; // IMAGE OF
		break;
	case  0x22C9:
		ret= 0x22CA; // LEFT NORMAL FACTOR SEMIDIRECT PRODUCT
		break;
	case  0x22CA:
		ret= 0x22C9; // RIGHT NORMAL FACTOR SEMIDIRECT PRODUCT
		break;
	case  0x22CB:
		ret= 0x22CC; // LEFT SEMIDIRECT PRODUCT
		break;
	case  0x22CC:
		ret= 0x22CB; // RIGHT SEMIDIRECT PRODUCT
		break;
	case  0x22CD:
		ret= 0x2243; // REVERSED TILDE EQUALS
		break;
	case  0x22D0:
		ret= 0x22D1; // DOUBLE SUBSET
		break;
	case  0x22D1:
		ret= 0x22D0; // DOUBLE SUPERSET
		break;
	case  0x22D6:
		ret= 0x22D7; // LESS-THAN WITH DOT
		break;
	case  0x22D7:
		ret= 0x22D6; // GREATER-THAN WITH DOT
		break;
	case  0x22D8:
		ret= 0x22D9; // VERY MUCH LESS-THAN
		break;
	case  0x22D9:
		ret= 0x22D8; // VERY MUCH GREATER-THAN
		break;
	case  0x22DA:
		ret= 0x22DB; // LESS-THAN EQUAL TO OR GREATER-THAN
		break;
	case  0x22DB:
		ret= 0x22DA; // GREATER-THAN EQUAL TO OR LESS-THAN
		break;
	case  0x22DC:
		ret= 0x22DD; // EQUAL TO OR LESS-THAN
		break;
	case  0x22DD:
		ret= 0x22DC; // EQUAL TO OR GREATER-THAN
		break;
	case  0x22DE:
		ret= 0x22DF; // EQUAL TO OR PRECEDES
		break;
	case  0x22DF:
		ret= 0x22DE; // EQUAL TO OR SUCCEEDS
		break;
	case  0x22E0:
		ret= 0x22E1; // [BEST FIT] DOES NOT PRECEDE OR EQUAL
		break;
	case  0x22E1:
		ret= 0x22E0; // [BEST FIT] DOES NOT SUCCEED OR EQUAL
		break;
	case  0x22E2:
		ret= 0x22E3; // [BEST FIT] NOT SQUARE IMAGE OF OR EQUAL TO
		break;
	case  0x22E3:
		ret= 0x22E2; // [BEST FIT] NOT SQUARE ORIGINAL OF OR EQUAL TO
		break;
	case  0x22E4:
		ret= 0x22E5; // [BEST FIT] SQUARE IMAGE OF OR NOT EQUAL TO
		break;
	case  0x22E5:
		ret= 0x22E4; // [BEST FIT] SQUARE ORIGINAL OF OR NOT EQUAL TO
		break;
	case  0x22E6:
		ret= 0x22E7; // [BEST FIT] LESS-THAN BUT NOT EQUIVALENT TO
		break;
	case  0x22E7:
		ret= 0x22E6; // [BEST FIT] GREATER-THAN BUT NOT EQUIVALENT TO
		break;
	case  0x22E8:
		ret= 0x22E9; // [BEST FIT] PRECEDES BUT NOT EQUIVALENT TO
		break;
	case  0x22E9:
		ret= 0x22E8; // [BEST FIT] SUCCEEDS BUT NOT EQUIVALENT TO
		break;
	case  0x22EA:
		ret= 0x22EB; // [BEST FIT] NOT NORMAL SUBGROUP OF
		break;
	case  0x22EB:
		ret= 0x22EA; // [BEST FIT] DOES NOT CONTAIN AS NORMAL SUBGROUP
		break;
	case  0x22EC:
		ret= 0x22ED; // [BEST FIT] NOT NORMAL SUBGROUP OF OR EQUAL TO
		break;
	case  0x22ED:
		ret= 0x22EC; // [BEST FIT] DOES NOT CONTAIN AS NORMAL SUBGROUP OR EQUAL
		break;
	case  0x22F0:
		ret= 0x22F1; // UP RIGHT DIAGONAL ELLIPSIS
		break;
	case  0x22F1:
		ret= 0x22F0; // DOWN RIGHT DIAGONAL ELLIPSIS
		break;
	case  0x22F2:
		ret= 0x22FA; // ELEMENT OF WITH LONG HORIZONTAL STROKE
		break;
	case  0x22F3:
		ret= 0x22FB; // ELEMENT OF WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
		break;
	case  0x22F4:
		ret= 0x22FC; // SMALL ELEMENT OF WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
		break;
	case  0x22F6:
		ret= 0x22FD; // ELEMENT OF WITH OVERBAR
		break;
	case  0x22F7:
		ret= 0x22FE; // SMALL ELEMENT OF WITH OVERBAR
		break;
	case  0x22FA:
		ret= 0x22F2; // CONTAINS WITH LONG HORIZONTAL STROKE
		break;
	case  0x22FB:
		ret= 0x22F3; // CONTAINS WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
		break;
	case  0x22FC:
		ret= 0x22F4; // SMALL CONTAINS WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
		break;
	case  0x22FD:
		ret= 0x22F6; // CONTAINS WITH OVERBAR
		break;
	case  0x22FE:
		ret= 0x22F7; // SMALL CONTAINS WITH OVERBAR
		break;
	case  0x2308:
		ret= 0x2309; // LEFT CEILING
		break;
	case  0x2309:
		ret= 0x2308; // RIGHT CEILING
		break;
	case  0x230A:
		ret= 0x230B; // LEFT FLOOR
		break;
	case  0x230B:
		ret= 0x230A; // RIGHT FLOOR
		break;
	case  0x2329:
		ret= 0x232A; // LEFT-POINTING ANGLE BRACKET
		break;
	case  0x232A:
		ret= 0x2329; // RIGHT-POINTING ANGLE BRACKET
		break;
	case  0x2768:
		ret= 0x2769; // MEDIUM LEFT PARENTHESIS ORNAMENT
		break;
	case  0x2769:
		ret= 0x2768; // MEDIUM RIGHT PARENTHESIS ORNAMENT
		break;
	case  0x276A:
		ret= 0x276B; // MEDIUM FLATTENED LEFT PARENTHESIS ORNAMENT
		break;
	case  0x276B:
		ret= 0x276A; // MEDIUM FLATTENED RIGHT PARENTHESIS ORNAMENT
		break;
	case  0x276C:
		ret= 0x276D; // MEDIUM LEFT-POINTING ANGLE BRACKET ORNAMENT
		break;
	case  0x276D:
		ret= 0x276C; // MEDIUM RIGHT-POINTING ANGLE BRACKET ORNAMENT
		break;
	case  0x276E:
		ret= 0x276F; // HEAVY LEFT-POINTING ANGLE QUOTATION MARK ORNAMENT
		break;
	case  0x276F:
		ret= 0x276E; // HEAVY RIGHT-POINTING ANGLE QUOTATION MARK ORNAMENT
		break;
	case  0x2770:
		ret= 0x2771; // HEAVY LEFT-POINTING ANGLE BRACKET ORNAMENT
		break;
	case  0x2771:
		ret= 0x2770; // HEAVY RIGHT-POINTING ANGLE BRACKET ORNAMENT
		break;
	case  0x2772:
		ret= 0x2773; // LIGHT LEFT TORTOISE SHELL BRACKET
		break;
	case  0x2773:
		ret= 0x2772; // LIGHT RIGHT TORTOISE SHELL BRACKET
		break;
	case  0x2774:
		ret= 0x2775; // MEDIUM LEFT CURLY BRACKET ORNAMENT
		break;
	case  0x2775:
		ret= 0x2774; // MEDIUM RIGHT CURLY BRACKET ORNAMENT
		break;
	case  0x27D5:
		ret= 0x27D6; // LEFT OUTER JOIN
		break;
	case  0x27D6:
		ret= 0x27D5; // RIGHT OUTER JOIN
		break;
	case  0x27DD:
		ret= 0x27DE; // LONG RIGHT TACK
		break;
	case  0x27DE:
		ret= 0x27DD; // LONG LEFT TACK
		break;
	case  0x27E2:
		ret= 0x27E3; // WHITE CONCAVE-SIDED DIAMOND WITH LEFTWARDS TICK
		break;
	case  0x27E3:
		ret= 0x27E2; // WHITE CONCAVE-SIDED DIAMOND WITH RIGHTWARDS TICK
		break;
	case  0x27E4:
		ret= 0x27E5; // WHITE SQUARE WITH LEFTWARDS TICK
		break;
	case  0x27E5:
		ret= 0x27E4; // WHITE SQUARE WITH RIGHTWARDS TICK
		break;
	case  0x27E6:
		ret= 0x27E7; // MATHEMATICAL LEFT WHITE SQUARE BRACKET
		break;
	case  0x27E7:
		ret= 0x27E6; // MATHEMATICAL RIGHT WHITE SQUARE BRACKET
		break;
	case  0x27E8:
		ret= 0x27E9; // MATHEMATICAL LEFT ANGLE BRACKET
		break;
	case  0x27E9:
		ret= 0x27E8; // MATHEMATICAL RIGHT ANGLE BRACKET
		break;
	case  0x27EA:
		ret= 0x27EB; // MATHEMATICAL LEFT DOUBLE ANGLE BRACKET
		break;
	case  0x27EB:
		ret= 0x27EA; // MATHEMATICAL RIGHT DOUBLE ANGLE BRACKET
		break;
	case  0x2983:
		ret= 0x2984; // LEFT WHITE CURLY BRACKET
		break;
	case  0x2984:
		ret= 0x2983; // RIGHT WHITE CURLY BRACKET
		break;
	case  0x2985:
		ret= 0x2986; // LEFT WHITE PARENTHESIS
		break;
	case  0x2986:
		ret= 0x2985; // RIGHT WHITE PARENTHESIS
		break;
	case  0x2987:
		ret= 0x2988; // Z NOTATION LEFT IMAGE BRACKET
		break;
	case  0x2988:
		ret= 0x2987; // Z NOTATION RIGHT IMAGE BRACKET
		break;
	case  0x2989:
		ret= 0x298A; // Z NOTATION LEFT BINDING BRACKET
		break;
	case  0x298A:
		ret= 0x2989; // Z NOTATION RIGHT BINDING BRACKET
		break;
	case  0x298B:
		ret= 0x298C; // LEFT SQUARE BRACKET WITH UNDERBAR
		break;
	case  0x298C:
		ret= 0x298B; // RIGHT SQUARE BRACKET WITH UNDERBAR
		break;
	case  0x298D:
		ret= 0x2990; // LEFT SQUARE BRACKET WITH TICK IN TOP CORNER
		break;
	case  0x298E:
		ret= 0x298F; // RIGHT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
		break;
	case  0x298F:
		ret= 0x298E; // LEFT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
		break;
	case  0x2990:
		ret= 0x298D; // RIGHT SQUARE BRACKET WITH TICK IN TOP CORNER
		break;
	case  0x2991:
		ret= 0x2992; // LEFT ANGLE BRACKET WITH DOT
		break;
	case  0x2992:
		ret= 0x2991; // RIGHT ANGLE BRACKET WITH DOT
		break;
	case  0x2993:
		ret= 0x2994; // LEFT ARC LESS-THAN BRACKET
		break;
	case  0x2994:
		ret= 0x2993; // RIGHT ARC GREATER-THAN BRACKET
		break;
	case  0x2995:
		ret= 0x2996; // DOUBLE LEFT ARC GREATER-THAN BRACKET
		break;
	case  0x2996:
		ret= 0x2995; // DOUBLE RIGHT ARC LESS-THAN BRACKET
		break;
	case  0x2997:
		ret= 0x2998; // LEFT BLACK TORTOISE SHELL BRACKET
		break;
	case  0x2998:
		ret= 0x2997; // RIGHT BLACK TORTOISE SHELL BRACKET
		break;
	case  0x29B8:
		ret= 0x2298; // CIRCLED REVERSE SOLIDUS
		break;
	case  0x29C0:
		ret= 0x29C1; // CIRCLED LESS-THAN
		break;
	case  0x29C1:
		ret= 0x29C0; // CIRCLED GREATER-THAN
		break;
	case  0x29C4:
		ret= 0x29C5; // SQUARED RISING DIAGONAL SLASH
		break;
	case  0x29C5:
		ret= 0x29C4; // SQUARED FALLING DIAGONAL SLASH
		break;
	case  0x29CF:
		ret= 0x29D0; // LEFT TRIANGLE BESIDE VERTICAL BAR
		break;
	case  0x29D0:
		ret= 0x29CF; // VERTICAL BAR BESIDE RIGHT TRIANGLE
		break;
	case  0x29D1:
		ret= 0x29D2; // BOWTIE WITH LEFT HALF BLACK
		break;
	case  0x29D2:
		ret= 0x29D1; // BOWTIE WITH RIGHT HALF BLACK
		break;
	case  0x29D4:
		ret= 0x29D5; // TIMES WITH LEFT HALF BLACK
		break;
	case  0x29D5:
		ret= 0x29D4; // TIMES WITH RIGHT HALF BLACK
		break;
	case  0x29D8:
		ret= 0x29D9; // LEFT WIGGLY FENCE
		break;
	case  0x29D9:
		ret= 0x29D8; // RIGHT WIGGLY FENCE
		break;
	case  0x29DA:
		ret= 0x29DB; // LEFT DOUBLE WIGGLY FENCE
		break;
	case  0x29DB:
		ret= 0x29DA; // RIGHT DOUBLE WIGGLY FENCE
		break;
	case  0x29F5:
		ret= 0x2215; // REVERSE SOLIDUS OPERATOR
		break;
	case  0x29F8:
		ret= 0x29F9; // BIG SOLIDUS
		break;
	case  0x29F9:
		ret= 0x29F8; // BIG REVERSE SOLIDUS
		break;
	case  0x29FC:
		ret= 0x29FD; // LEFT-POINTING CURVED ANGLE BRACKET
		break;
	case  0x29FD:
		ret= 0x29FC; // RIGHT-POINTING CURVED ANGLE BRACKET
		break;
	case  0x2A2B:
		ret= 0x2A2C; // MINUS SIGN WITH FALLING DOTS
		break;
	case  0x2A2C:
		ret= 0x2A2B; // MINUS SIGN WITH RISING DOTS
		break;
	case  0x2A2D:
		ret= 0x2A2C; // PLUS SIGN IN LEFT HALF CIRCLE
		break;
	case  0x2A2E:
		ret= 0x2A2D; // PLUS SIGN IN RIGHT HALF CIRCLE
		break;
	case  0x2A34:
		ret= 0x2A35; // MULTIPLICATION SIGN IN LEFT HALF CIRCLE
		break;
	case  0x2A35:
		ret= 0x2A34; // MULTIPLICATION SIGN IN RIGHT HALF CIRCLE
		break;
	case  0x2A3C:
		ret= 0x2A3D; // INTERIOR PRODUCT
		break;
	case  0x2A3D:
		ret= 0x2A3C; // RIGHTHAND INTERIOR PRODUCT
		break;
	case  0x2A64:
		ret= 0x2A65; // Z NOTATION DOMAIN ANTIRESTRICTION
		break;
	case  0x2A65:
		ret= 0x2A64; // Z NOTATION RANGE ANTIRESTRICTION
		break;
	case  0x2A79:
		ret= 0x2A7A; // LESS-THAN WITH CIRCLE INSIDE
		break;
	case  0x2A7A:
		ret= 0x2A79; // GREATER-THAN WITH CIRCLE INSIDE
		break;
	case  0x2A7D:
		ret= 0x2A7E; // LESS-THAN OR SLANTED EQUAL TO
		break;
	case  0x2A7E:
		ret= 0x2A7D; // GREATER-THAN OR SLANTED EQUAL TO
		break;
	case  0x2A7F:
		ret= 0x2A80; // LESS-THAN OR SLANTED EQUAL TO WITH DOT INSIDE
		break;
	case  0x2A80:
		ret= 0x2A7F; // GREATER-THAN OR SLANTED EQUAL TO WITH DOT INSIDE
		break;
	case  0x2A81:
		ret= 0x2A82; // LESS-THAN OR SLANTED EQUAL TO WITH DOT ABOVE
		break;
	case  0x2A82:
		ret= 0x2A81; // GREATER-THAN OR SLANTED EQUAL TO WITH DOT ABOVE
		break;
	case  0x2A83:
		ret= 0x2A84; // LESS-THAN OR SLANTED EQUAL TO WITH DOT ABOVE RIGHT
		break;
	case  0x2A84:
		ret= 0x2A83; // GREATER-THAN OR SLANTED EQUAL TO WITH DOT ABOVE LEFT
		break;
	case  0x2A8B:
		ret= 0x2A8C; // LESS-THAN ABOVE DOUBLE-LINE EQUAL ABOVE GREATER-THAN
		break;
	case  0x2A8C:
		ret= 0x2A8B; // GREATER-THAN ABOVE DOUBLE-LINE EQUAL ABOVE LESS-THAN
		break;
	case  0x2A91:
		ret= 0x2A92; // LESS-THAN ABOVE GREATER-THAN ABOVE DOUBLE-LINE EQUAL
		break;
	case  0x2A92:
		ret= 0x2A91; // GREATER-THAN ABOVE LESS-THAN ABOVE DOUBLE-LINE EQUAL
		break;
	case  0x2A93:
		ret= 0x2A94; // LESS-THAN ABOVE SLANTED EQUAL ABOVE GREATER-THAN ABOVE SLANTED EQUAL
		break;
	case  0x2A94:
		ret= 0x2A93; // GREATER-THAN ABOVE SLANTED EQUAL ABOVE LESS-THAN ABOVE SLANTED EQUAL
		break;
	case  0x2A95:
		ret= 0x2A96; // SLANTED EQUAL TO OR LESS-THAN
		break;
	case  0x2A96:
		ret= 0x2A95; // SLANTED EQUAL TO OR GREATER-THAN
		break;
	case  0x2A97:
		ret= 0x2A98; // SLANTED EQUAL TO OR LESS-THAN WITH DOT INSIDE
		break;
	case  0x2A98:
		ret= 0x2A97; // SLANTED EQUAL TO OR GREATER-THAN WITH DOT INSIDE
		break;
	case  0x2A99:
		ret= 0x2A9A; // DOUBLE-LINE EQUAL TO OR LESS-THAN
		break;
	case  0x2A9A:
		ret= 0x2A99; // DOUBLE-LINE EQUAL TO OR GREATER-THAN
		break;
	case  0x2A9B:
		ret= 0x2A9C; // DOUBLE-LINE SLANTED EQUAL TO OR LESS-THAN
		break;
	case  0x2A9C:
		ret= 0x2A9B; // DOUBLE-LINE SLANTED EQUAL TO OR GREATER-THAN
		break;
	case  0x2AA1:
		ret= 0x2AA2; // DOUBLE NESTED LESS-THAN
		break;
	case  0x2AA2:
		ret= 0x2AA1; // DOUBLE NESTED GREATER-THAN
		break;
	case  0x2AA6:
		ret= 0x2AA7; // LESS-THAN CLOSED BY CURVE
		break;
	case  0x2AA7:
		ret= 0x2AA6; // GREATER-THAN CLOSED BY CURVE
		break;
	case  0x2AA8:
		ret= 0x2AA9; // LESS-THAN CLOSED BY CURVE ABOVE SLANTED EQUAL
		break;
	case  0x2AA9:
		ret= 0x2AA8; // GREATER-THAN CLOSED BY CURVE ABOVE SLANTED EQUAL
		break;
	case  0x2AAA:
		ret= 0x2AAB; // SMALLER THAN
		break;
	case  0x2AAB:
		ret= 0x2AAA; // LARGER THAN
		break;
	case  0x2AAC:
		ret= 0x2AAD; // SMALLER THAN OR EQUAL TO
		break;
	case  0x2AAD:
		ret= 0x2AAC; // LARGER THAN OR EQUAL TO
		break;
	case  0x2AAF:
		ret= 0x2AB0; // PRECEDES ABOVE SINGLE-LINE EQUALS SIGN
		break;
	case  0x2AB0:
		ret= 0x2AAF; // SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN
		break;
	case  0x2AB3:
		ret= 0x2AB4; // PRECEDES ABOVE EQUALS SIGN
		break;
	case  0x2AB4:
		ret= 0x2AB3; // SUCCEEDS ABOVE EQUALS SIGN
		break;
	case  0x2ABB:
		ret= 0x2ABC; // DOUBLE PRECEDES
		break;
	case  0x2ABC:
		ret= 0x2ABB; // DOUBLE SUCCEEDS
		break;
	case  0x2ABD:
		ret= 0x2ABE; // SUBSET WITH DOT
		break;
	case  0x2ABE:
		ret= 0x2ABD; // SUPERSET WITH DOT
		break;
	case  0x2ABF:
		ret= 0x2AC0; // SUBSET WITH PLUS SIGN BELOW
		break;
	case  0x2AC0:
		ret= 0x2ABF; // SUPERSET WITH PLUS SIGN BELOW
		break;
	case  0x2AC1:
		ret= 0x2AC2; // SUBSET WITH MULTIPLICATION SIGN BELOW
		break;
	case  0x2AC2:
		ret= 0x2AC1; // SUPERSET WITH MULTIPLICATION SIGN BELOW
		break;
	case  0x2AC3:
		ret= 0x2AC4; // SUBSET OF OR EQUAL TO WITH DOT ABOVE
		break;
	case  0x2AC4:
		ret= 0x2AC3; // SUPERSET OF OR EQUAL TO WITH DOT ABOVE
		break;
	case  0x2AC5:
		ret= 0x2AC6; // SUBSET OF ABOVE EQUALS SIGN
		break;
	case  0x2AC6:
		ret= 0x2AC5; // SUPERSET OF ABOVE EQUALS SIGN
		break;
	case  0x2ACD:
		ret= 0x2ACE; // SQUARE LEFT OPEN BOX OPERATOR
		break;
	case  0x2ACE:
		ret= 0x2ACD; // SQUARE RIGHT OPEN BOX OPERATOR
		break;
	case  0x2ACF:
		ret= 0x2AD0; // CLOSED SUBSET
		break;
	case  0x2AD0:
		ret= 0x2ACF; // CLOSED SUPERSET
		break;
	case  0x2AD1:
		ret= 0x2AD2; // CLOSED SUBSET OR EQUAL TO
		break;
	case  0x2AD2:
		ret= 0x2AD1; // CLOSED SUPERSET OR EQUAL TO
		break;
	case  0x2AD3:
		ret= 0x2AD4; // SUBSET ABOVE SUPERSET
		break;
	case  0x2AD4:
		ret= 0x2AD3; // SUPERSET ABOVE SUBSET
		break;
	case  0x2AD5:
		ret= 0x2AD6; // SUBSET ABOVE SUBSET
		break;
	case  0x2AD6:
		ret= 0x2AD5; // SUPERSET ABOVE SUPERSET
		break;
	case  0x2ADE:
		ret= 0x22A6; // SHORT LEFT TACK
		break;
	case  0x2AE3:
		ret= 0x22A9; // DOUBLE VERTICAL BAR LEFT TURNSTILE
		break;
	case  0x2AE4:
		ret= 0x22A8; // VERTICAL BAR DOUBLE LEFT TURNSTILE
		break;
	case  0x2AE5:
		ret= 0x22AB; // DOUBLE VERTICAL BAR DOUBLE LEFT TURNSTILE
		break;
	case  0x2AEC:
		ret= 0x2AED; // DOUBLE STROKE NOT SIGN
		break;
	case  0x2AED:
		ret= 0x2AEC; // REVERSED DOUBLE STROKE NOT SIGN
		break;
	case  0x2AF7:
		ret= 0x2AF8; // TRIPLE NESTED LESS-THAN
		break;
	case  0x2AF8:
		ret= 0x2AF7; // TRIPLE NESTED GREATER-THAN
		break;
	case  0x2AF9:
		ret= 0x2AFA; // DOUBLE-LINE SLANTED LESS-THAN OR EQUAL TO
		break;
	case  0x2AFA:
		ret= 0x2AF9; // DOUBLE-LINE SLANTED GREATER-THAN OR EQUAL TO
		break;
	case  0x3008:
		ret= 0x3009; // LEFT ANGLE BRACKET
		break;
	case  0x3009:
		ret= 0x3008; // RIGHT ANGLE BRACKET
		break;
	case  0x300A:
		ret= 0x300B; // LEFT DOUBLE ANGLE BRACKET
		break;
	case  0x300B:
		ret= 0x300A; // RIGHT DOUBLE ANGLE BRACKET
		break;
	case  0x300C:
		ret= 0x300D; // [BEST FIT] LEFT CORNER BRACKET
		break;
	case  0x300D:
		ret= 0x300C; // [BEST FIT] RIGHT CORNER BRACKET
		break;
	case  0x300E:
		ret= 0x300F; // [BEST FIT] LEFT WHITE CORNER BRACKET
		break;
	case  0x300F:
		ret= 0x300E; // [BEST FIT] RIGHT WHITE CORNER BRACKET
		break;
	case  0x3010:
		ret= 0x3011; // LEFT BLACK LENTICULAR BRACKET
		break;
	case  0x3011:
		ret= 0x3010; // RIGHT BLACK LENTICULAR BRACKET
		break;
	case  0x3014:
		ret= 0x3015; // LEFT TORTOISE SHELL BRACKET
		break;
	case  0x3015:
		ret= 0x3014; // RIGHT TORTOISE SHELL BRACKET
		break;
	case  0x3016:
		ret= 0x3017; // LEFT WHITE LENTICULAR BRACKET
		break;
	case  0x3017:
		ret= 0x3016; // RIGHT WHITE LENTICULAR BRACKET
		break;
	case  0x3018:
		ret= 0x3019; // LEFT WHITE TORTOISE SHELL BRACKET
		break;
	case  0x3019:
		ret= 0x3018; // RIGHT WHITE TORTOISE SHELL BRACKET
		break;
	case  0x301A:
		ret= 0x301B; // LEFT WHITE SQUARE BRACKET
		break;
	case  0x301B:
		ret= 0x301A; // RIGHT WHITE SQUARE BRACKET
		break;
	case  0xFF08:
		ret= 0xFF09; // FULLWIDTH LEFT PARENTHESIS
		break;
	case  0xFF09:
		ret= 0xFF08; // FULLWIDTH RIGHT PARENTHESIS
		break;
	case  0xFF1C:
		ret= 0xFF1E; // FULLWIDTH LESS-THAN SIGN
		break;
	case  0xFF1E:
		ret= 0xFF1C; // FULLWIDTH GREATER-THAN SIGN
		break;
	case  0xFF3B:
		ret= 0xFF3D; // FULLWIDTH LEFT SQUARE BRACKET
		break;
	case  0xFF3D:
		ret= 0xFF3B; // FULLWIDTH RIGHT SQUARE BRACKET
		break;
	case  0xFF5B:
		ret= 0xFF5D; // FULLWIDTH LEFT CURLY BRACKET
		break;
	case  0xFF5D:
		ret= 0xFF5B; // FULLWIDTH RIGHT CURLY BRACKET
		break;
	case  0xFF5F:
		ret= 0xFF60; // FULLWIDTH LEFT WHITE PARENTHESIS
		break;
	case  0xFF60:
		ret= 0xFF5F; // FULLWIDTH RIGHT WHITE PARENTHESIS
		break;
	case  0xFF62:
		ret= 0xFF63; // [BEST FIT] HALFWIDTH LEFT CORNER BRACKET
		break;
	case  0xFF63:
		ret= 0xFF62; // [BEST FIT] HALFWIDTH RIGHT CORNER BRACKET
		break;
	default:
		ret=c;
	}
	return ret;
}

char UBidiLine::getDirection(wchar_t  c)
{
	return rtypes[c];
}

/**
* The algorithm.
* Does not include line-based processing (Rules L1, L2).
* These are applied later in the line-based phase of the algorithm.
*/
void UBidiLine::runAlgorithm()
{
	// 2) Explicit levels and directions
	// Rules X1-X8.
	determineExplicitEmbeddingLevels();
	// Rule X9.
	int tLen= removeExplicitCodes();
	// Rule X10.
	// Run remainder of algorithm one level run at a time
	char prevLevel = paragraphEmbeddingLevel;
	int start = 0;
	while (start < tLen)
	{
		char level = resultLevels[start];
		char prevType = typeForLevel(MY_MAX(prevLevel, level));

		int limit = start + 1;
		while (limit < tLen && resultLevels[limit] == level)
		{
			++limit;
		}

		char succLevel = limit < tLen ? resultLevels[limit]: paragraphEmbeddingLevel;
		char succType = typeForLevel(MY_MAX(succLevel, level));

		// 3) resolving weak types
		// Rules W1-W7.
		resolveWeakTypes(start, limit, level, prevType, succType);

		// 4) resolving neutral types
		// Rules N1-N3.
		resolveNeutralTypes(start, limit, level, prevType, succType);

		// 5) resolving implicit embedding levels
		// Rules I1, I2.
		resolveImplicitLevels(start, limit, level, prevType, succType);

		prevLevel = level;
		start = limit;
	}

	// Reinsert explicit codes and assign appropriate levels to 'hide' them.
	// This is for convenience, so the resulting level array maps 1-1
	// with the initial array.
	// See the implementation suggestions section of TR#9 for guidelines on
	// how to implement the algorithm without removing and reinserting the codes.
	reinsertExplicitCodes(tLen);
}

/**
* 1) determining the paragraph level.
* <p>
* Rules P2, P3.
* <p>
* At the end of this function, the member variable paragraphEmbeddingLevel is set to either 0 or 1.
*/
void UBidiLine::determineParagraphEmbeddingLevel()
{
	char strongType = -1; // unknown
	// Rule P2.
	for (int i = 0; i < textLength; ++i)
	{
		char t = resultTypes[i];
		if (t == L || t == AL || t == R)
		{
			strongType = t;
			break;
		}
	}

	// Rule P3.
	if (strongType == -1)
	{ // none found
		// default embedding level when no strong types found is 0.
		paragraphEmbeddingLevel = 0;
	}
	else if (strongType == L)
	{
		paragraphEmbeddingLevel = 0;
	}
	else
	{ // AL, R
		paragraphEmbeddingLevel = 1;
	}
}

/**
* Process embedding format codes.
* <p>
* Calls processEmbeddings to generate an embedding array from the explicit format codes.  The
* embedding overrides in the array are then applied to the result types, and the result levels are
* initialized.
* @see #processEmbeddings
*/
void UBidiLine::determineExplicitEmbeddingLevels()
{
	processEmbeddings();
	for (int i = 0; i < textLength; ++i)
	{
		char level = embeddings[i];
		if ((level & 0x80) != 0)
		{
			level &= 0x7f;
			resultTypes[i] = typeForLevel(level);
		}
		resultLevels[i] = level;
	}
}

/**
* Rules X9.
* Remove explicit codes so that they may be ignored during the remainder
* of the main portion of the algorithm.  The length of the resulting text
* is returned.
* @return the length of the data excluding explicit codes and BN.
*/

int UBidiLine::removeExplicitCodes()
{
	int w = 0;
	for (int i = 0; i < textLength; ++i)
	{
		char t = initialTypes[i];
		if (!(t == LRE || t == RLE || t == LRO || t == RLO || t == PDF || t == BN))
		{
			embeddings[w] = embeddings[i];
			resultTypes[w] = resultTypes[i];
			resultLevels[w] = resultLevels[i];
			w++;
		}
	}
	return w; // new textLength while explicit levels are removed
}

/**
* Reinsert levels information for explicit codes.
* This is for ease of relating the level information
* to the original input data.  Note that the levels
* assigned to these codes are arbitrary, they're
* chosen so as to avoid breaking level runs.
* @param textLength the length of the data after compression
* @return the length of the data (original length of
* types array supplied to constructor)
*/
void UBidiLine::reinsertExplicitCodes(int tLen)
{
	int i;
	for (i =textLength; --i >= 0;)
	{
		char t = initialTypes[i];
		if (t == LRE || t == RLE || t == LRO || t == RLO || t == PDF || t == BN)
		{
			embeddings[i] = 0;
			resultTypes[i] = t;
			resultLevels[i] = -1;
		}
		else
		{
			--tLen;
			embeddings[i] = embeddings[tLen];
			resultTypes[i] = resultTypes[tLen];
			resultLevels[i] = resultLevels[tLen];
		}
	}

	// now propagate forward the levels information (could have
	// propagated backward, the main thing is not to introduce a level
	// break where one doesn't already exist).

	if (resultLevels[0] == -1)
	{
		resultLevels[0] = paragraphEmbeddingLevel;
	}
	for (i = 1; i <textLength; ++i)
	{
		if (resultLevels[i] == -1)
		{
			resultLevels[i] = resultLevels[i-1];
		}
	}
}

/**
* 2) determining explicit levels
* Rules X1 - X8
*
* The interaction of these rules makes handling them a bit complex.
* This examines resultTypes but does not modify it.  It returns embedding and
* override information in the result array.  The low 7 bits are the level, the high
* bit is set if the level is an override, and clear if it is an embedding.
*/
void UBidiLine::processEmbeddings()
{
	int stackCounter = 0;

	// An LRE or LRO at level 60 is invalid, since the new level 62 is invalid.  But
	// an RLE at level 60 is valid, since the new level 61 is valid.  The current wording
	// of the rules requires that the RLE remain valid even if a previous LRE is invalid.
	// This keeps track of ignored LRE or LRO codes at level 60, so that the matching PDFs
	// will not try to pop the stack.
	int overflowAlmostCounter = 0;

	// This keeps track of ignored pushes at level 61 or higher, so that matching PDFs will
	// not try to pop the stack.
	int overflowCounter = 0;

	// Rule X1.

	// Keep the level separate from the value (level | override status flag) for ease of access.
	char currentEmbeddingLevel = paragraphEmbeddingLevel;
	char currentEmbeddingValue = paragraphEmbeddingLevel;

	// Loop through types, handling all remaining rules
	for (int i = 0; i < textLength; ++i)
	{
		embeddings[i] = currentEmbeddingValue;
		char t = resultTypes[i];
		// Rules X2, X3, X4, X5
		switch (t)
		{
		case RLE:
		case LRE:
		case RLO:
		case LRO:
			// Only need to compute new level if current level is valid
			if (overflowCounter == 0)
			{
				char newLevel;
				if (t == RLE || t == RLO)
				{
					newLevel = (char)((currentEmbeddingLevel + 1) | 1); // least greater odd
				}
				else
				{ // t == LRE || t == LRO
					newLevel = (char)((currentEmbeddingLevel + 2) & ~1); // least greater even
				}

				// If the new level is valid, push old embedding level and override status
				// No check for valid stack counter, since the level check suffices.
				if (newLevel < EXPLICIT_LEVEL_LIMIT)
				{
					embeddingValueStack[stackCounter] = currentEmbeddingValue;
					stackCounter++;

					currentEmbeddingLevel = newLevel;
					if (t == LRO || t == RLO)
					{ // override
						currentEmbeddingValue = (char)(newLevel | 0x80);
					}
					else
					{
						currentEmbeddingValue = newLevel;
					}

					// Adjust level of format mark (for expositional purposes only, this gets
					// removed later).
					embeddings[i] = currentEmbeddingValue;
					break;
				}

				// Otherwise new level is invalid, but a valid level can still be achieved if this
				// level is 60 and we encounter an RLE or RLO further on.  So record that we
				// 'almost' overflowed.
				if (currentEmbeddingLevel == 60)
				{
					overflowAlmostCounter++;
					break;
				}
			}

			// Otherwise old or new level is invalid.
			overflowCounter++;
			break;

		case PDF:
			// The only case where this did not actually overflow but may have almost overflowed
			// is when there was an RLE or RLO on level 60, which would result in level 61.  So we
			// only test the almost overflow condition in that case.
			//
			// Also note that there may be a PDF without any pushes at all.

			if (overflowCounter > 0)
			{
				--overflowCounter;
			}
			else if (overflowAlmostCounter > 0 && currentEmbeddingLevel != 61)
			{
				--overflowAlmostCounter;
			}
			else if (stackCounter > 0)
			{
				--stackCounter;
				currentEmbeddingValue = embeddingValueStack[stackCounter];
				currentEmbeddingLevel = (char)(currentEmbeddingValue & 0x7f);
			}
			break;

		case B:
			// Rule X8.

			// These values are reset for clarity, in this implementation B can only
			// occur as the last code in the array.
			stackCounter = 0;
			overflowCounter = 0;
			overflowAlmostCounter = 0;
			currentEmbeddingLevel = paragraphEmbeddingLevel;
			currentEmbeddingValue = paragraphEmbeddingLevel;

			embeddings[i] = paragraphEmbeddingLevel;
			break;

		default:
			break;
		}
	}
}

/**
* 3) resolving weak types
* Rules W1-W7.
*
* Note that some weak types (EN, AN) remain after this processing is complete.
*/
void UBidiLine::resolveWeakTypes(int start, int limit, char level, char sor, char eor)
{
	char runU[]={ ET,0x0};
	// Rule W1.
	// Changes all NSMs.
	char preceedingCharacterType = sor;
	int i;
	for (i = start; i < limit; ++i)
	{
		char t = resultTypes[i];
		if (t == NSM)
		{
			resultTypes[i] = preceedingCharacterType;
		}
		else
		{
			preceedingCharacterType = t;
		}
	}

	// Rule W2.
	// EN does not change at the start of the run, because sor != AL.
	for (i = start; i < limit; ++i)
	{
		if (resultTypes[i] == EN)
		{
			for (int j = i - 1; j >= start; --j)
			{
				char t = resultTypes[j];
				if (t == L || t == R || t == AL)
				{
					if (t == AL)
					{
						resultTypes[i] = AN;
					}
					break;
				}
			}
		}
	}

	// Rule W3.
	for (i = start; i < limit; ++i)
	{
		if (resultTypes[i] == AL)
		{
			resultTypes[i] = R;
		}
	}

	// Rule W4.
	// Since there must be values on both sides for this rule to have an
	// effect, the scan skips the first and last value.
	//
	// Although the scan proceeds left to right, and changes the type values
	// in a way that would appear to affect the computations later in the scan,
	// there is actually no problem.  A change in the current value can only
	// affect the value to its immediate right, and only affect it if it is
	// ES or CS.  But the current value can only change if the value to its
	// right is not ES or CS.  Thus either the current value will not change,
	// or its change will have no effect on the remainder of the analysis.

	for (i = start + 1; i < limit - 1; ++i)
	{
		if (resultTypes[i] == ES || resultTypes[i] == CS)
		{
			char prevSepType = resultTypes[i-1];
			char succSepType = resultTypes[i+1];
			if (prevSepType == EN && succSepType == EN)
			{
				resultTypes[i] = EN;
			}
			else if (resultTypes[i] == CS && prevSepType == AN && succSepType == AN)
			{
				resultTypes[i] = AN;
			}
		}
	}

	// Rule W5.
	for (i = start; i < limit; ++i)
	{
		if (resultTypes[i] == ET)
		{
			// locate end of sequence
			int runstart = i;
			int runlimit = findRunLimit(runstart, limit, runU);

			// check values at ends of sequence
			char t = runstart == start ? sor: resultTypes[runstart - 1];

			if (t != EN)
			{
				t = runlimit == limit ? eor: resultTypes[runlimit];
			}

			if (t == EN)
			{
				setTypes(runstart, runlimit, EN);
			}

			// continue at end of sequence
			i = runlimit;
		}
	}

	// Rule W6.
	for (i = start; i < limit; ++i)
	{
		char t = resultTypes[i];
		if (t == ES || t == ET || t == CS)
		{
			resultTypes[i] = ON;
		}
	}

	// Rule W7.
	for (i = start; i < limit; ++i)
	{
		if (resultTypes[i] == EN)
		{
			// set default if we reach start of run
			char prevStrongType = sor;
			for (int j = i - 1; j >= start; --j)
			{
				char t = resultTypes[j];
				if (t == L || t == R)
				{ // AL's have been removed
					prevStrongType = t;
					break;
				}
			}
			if (prevStrongType == L)
			{
				resultTypes[i] = L;
			}
		}
	}
}

/**
* 6) resolving neutral types
* Rules N1-N2.
*/

void UBidiLine::resolveNeutralTypes(int start, int limit, char level, char sor, char eor)
{
	char runU[]= {B, S, WS, ON,0x0};
	for (int i = start; i < limit; ++i)
	{
		char t = resultTypes[i];
		if (t == WS || t == ON || t == B || t == S)
		{
			// find bounds of run of neutrals
			int runstart = i;
			int runlimit = findRunLimit(runstart, limit,runU);

			// determine effective types at ends of run
			char leadingType;
			char trailingType;

			if (runstart == start)
			{
				leadingType = sor;
			}
			else
			{
				leadingType = resultTypes[runstart - 1];
				if (leadingType == L || leadingType == R)
				{
					// found the strong type
				}
				else if (leadingType == AN)
				{
					leadingType = R;
				}
				else if (leadingType == EN)
				{
					// Since EN's with previous strong L types have been changed
					// to L in W7, the leadingType must be R.
					leadingType = R;
				}
			}

			if (runlimit == limit)
			{
				trailingType = eor;
			}
			else
			{
				trailingType = resultTypes[runlimit];
				if (trailingType == L || trailingType == R)
				{
					// found the strong type
				}
				else if (trailingType == AN)
				{
					trailingType = R;
				}
				else if (trailingType == EN)
				{
					trailingType = R;
				}
			}

			char resolvedType;
			if (leadingType == trailingType)
			{
				// Rule N1.
				resolvedType = leadingType;
			}
			else
			{
				// Rule N2.
				// Notice the embedding level of the run is used, not
				// the paragraph embedding level.
				resolvedType = typeForLevel(level);
			}

			setTypes(runstart, runlimit, resolvedType);

			// skip over run of (former) neutrals
			i = runlimit;
		}
	}
}

/**
* 7) resolving implicit embedding levels
* Rules I1, I2.
*/
void UBidiLine::resolveImplicitLevels(int start, int limit, char level, char sor, char eor)
{
	if ((level & 1) == 0)
	{ // even level
		for (int i = start; i < limit; ++i)
		{
			char t = resultTypes[i];
			// Rule I1.
			if (t == L )
			{
				// no change
			}
			else if (t == R)
			{
				resultLevels[i] += 1;
			}
			else
			{ // t == AN || t == EN
				resultLevels[i] += 2;
			}
		}
	}
	else
	{ // odd level
		for (int i = start; i < limit; ++i)
		{
			char t = resultTypes[i];
			// Rule I2.
			if (t == R)
			{
				// no change
			}
			else
			{ // t == L || t == AN || t == EN
				resultLevels[i] += 1;
			}
		}
	}
}


/**
* Return reordering array for a given level array.  This reorders a single line.
* The reordering is a visual to logical map.  For example,
* the leftmost wchar_t  is string.wchar_t At(order[0]).
* Rule L2.
*/
void UBidiLine::Reordering()
{
	// locate highest level found on line.
	// Note the rules say text, but no reordering across line bounds is performed,
	// so this is sufficient.
	char highestLevel = 0;
	char lowestOddLevel = 63;
	for (int i = 0; i < textLength; ++i)
	{
		char level = resultLevels[i];
		if (level > highestLevel)
		{
			highestLevel = level;
		}
		if (((level & 1) != 0) && level < lowestOddLevel)
		{
			lowestOddLevel = level;
		}
	}

	for (int level = highestLevel; level >= lowestOddLevel; --level)
	{
		for (int i = 0; i < textLength; ++i)
		{
			if (resultLevels[i] >= level)
			{
				// find range of text at or above this level
				int start = i;
				int limit = i + 1;
				while (limit < textLength && resultLevels[limit] >= level)
				{
					++limit;
				}

				// reverse run
				for (int j = start, k = limit - 1; j < k; ++j, --k)
				{
					int temp = resultIndex[j];
					resultIndex[j] = resultIndex[k];
					resultIndex[k] = temp;
				}
				// skip to end of level run
				i = limit;
			}
		}
	}
}

/**
* Return true if the type is considered a whitespace type for the line break rules.
*/
bool UBidiLine::isWhitespace(char biditype)
{
	switch (biditype)
	{
	case LRE:
	case RLE:
	case LRO:
	case RLO:
	case PDF:
	case BN:
	case WS:
		return true;
	default:
		return false;
	}
}

/**
* Return the strong type (L or R) corresponding to the level.
*/

char UBidiLine::typeForLevel(int level)
{
	return ((level & 0x1) == 0) ? (char)L: (char)R;
}

/**
* Return the limit of the run starting at index that includes only resultTypes in validSet.
* This checks the value at index, and will return index if that value is not in validSet.
*/
int UBidiLine::findRunLimit(int index, int limit, char *validSet)
{
	--index;
loop:
	while (++index < limit)
	{
		char t = resultTypes[index];
		for (int i = 0; i < (int)strlen(validSet); ++i)
		{
			if (t == validSet[i])
			{
				goto loop;
			}
		}
		// didn't find a match in validSet
		return index;
	}
	return limit;
}

/**
* Set resultTypes from start up to (but not including) limit to newType.
*/
void UBidiLine::setTypes(int start, int limit, char newType)
{
	for (int i = start; i < limit; ++i)
	{
		resultTypes[i] = newType;
	}
}


void UBidiLine::Init()
{
	unsigned short baseTypes[] = {
		9,BN,
			1,S,
			1,B,
			1,S,
			1,WS,
			1,B,
			14,BN,
			3,B,
			1,S,
			1,WS,
			2,ON,
			3,ET,
			5,ON,
			1,ES,
			1,CS,
			1,ES,
			2,CS,
			10,EN,
			1,CS,
			6,ON,
			26,L,
			6,ON,
			26,L,
			4,ON,
			6,BN,
			1,B,
			26,BN,
			1,CS,
			1,ON,
			4,ET,
			4,ON,
			1,L,
			2,ON,
			1,BN,
			2,ON,
			2,ET,
			2,EN,
			1,ON,
			1,L,
			3,ON,
			1,EN,
			1,L,
			5,ON,
			23,L,
			1,ON,
			31,L,
			1,ON,
			449,L,
			2,ON,
			7,L,
			14,ON,
			2,L,
			14,ON,
			5,L,
			9,ON,
			1,L,
			17,ON,
			116,NSM,
			6,ON,
			4,L,
			8,ON,
			1,L,
			1,ON,
			110,L,
			1,ON,
			140,L,
			7,NSM,
			256,L,
			7,ON,
			45,NSM,
			1,R,
			1,NSM,
			1,R,
			2,NSM,
			1,R,
			12,NSM,
			48,R,
			12,AL,
			1,CS,
			1,AL,
			2,ON,
			11,NSM,
			48,AL,
			21,NSM,
			10,AN,
			1,ET,
			2,AN,
			3,AL,
			1,NSM,
			101,AL,
			7,NSM,
			1,AL,
			7,NSM,
			2,AL,
			2,NSM,
			1,ON,
			4,NSM,
			2,AL,
			10,EN,
			21,AL,
			1,BN,
			1,AL,
			1,NSM,
			30,AL,
			29,NSM,
			89,AL,
			11,NSM,
			336,AL,
			2,NSM,
			57,L,
			1,NSM,
			4,L,
			8,NSM,
			4,L,
			3,NSM,
			1,L,
			7,NSM,
			10,L,
			2,NSM,
			29,L,
			1,NSM,
			58,L,
			1,NSM,
			4,L,
			6,NSM,
			6,L,
			10,NSM,
			11,L,
			4,NSM,
			12,L,
			2,ET,
			13,L,
			2,NSM,
			57,L,
			2,NSM,
			3,L,
			24,NSM,
			23,L,
			2,NSM,
			15,L,
			2,NSM,
			57,L,
			1,NSM,
			4,L,
			8,NSM,
			4,L,
			3,NSM,
			18,L,
			4,NSM,
			11,L,
			16,ET,
			1,NSM,
			58,L,
			1,NSM,
			2,L,
			1,NSM,
			1,L,
			6,NSM,
			6,L,
			10,NSM,
			43,L,
			1,NSM,
			61,L,
			1,NSM,
			12,L,
			10,NSM,
			28,L,
			6,ON,
			1,ET,
			7,ON,
			61,L,
			3,NSM,
			5,L,
			26,NSM,
			92,L,
			1,NSM,
			15,L,
			9,NSM,
			108,L,
			5,NSM,
			7,L,
			10,NSM,
			115,L,
			5,NSM,
			3,L,
			6,NSM,
			89,L,
			1,NSM,
			2,L,
			11,NSM,
			1,ET,
			7,L,
			8,NSM,
			98,L,
			1,NSM,
			2,L,
			9,NSM,
			11,L,
			8,NSM,
			72,L,
			2,NSM,
			27,L,
			1,NSM,
			1,L,
			1,NSM,
			1,L,
			1,NSM,
			4,ON,
			51,L,
			14,NSM,
			1,L,
			5,NSM,
			1,L,
			2,NSM,
			8,L,
			46,NSM,
			8,L,
			1,NSM,
			102,L,
			4,NSM,
			1,L,
			6,NSM,
			1,L,
			7,NSM,
			24,L,
			72,NSM,
			1504,L,
			1,WS,
			26,L,
			5,ON,
			114,L,
			14,NSM,
			18,L,
			3,NSM,
			29,L,
			14,NSM,
			18,L,
			14,NSM,
			55,L,
			7,NSM,
			8,L,
			1,NSM,
			2,L,
			11,NSM,
			7,L,
			1,ET,
			1,L,
			3,NSM,
			16,L,
			27,ON,
			3,NSM,
			2,WS,
			153,L,
			87,NSM,
			32,L,
			3,NSM,
			4,L,
			9,NSM,
			2,L,
			1,NSM,
			6,L,
			7,NSM,
			6,ON,
			154,L,
			800,ON,
			701,L,
			1,ON,
			1,L,
			3,ON,
			11,L,
			3,ON,
			13,L,
			3,ON,
			13,L,
			5,ON,
			11,L,
			3,ON,
			11,WS,
			3,BN,
			1,L,
			1,R,
			24,ON,
			1,WS,
			1,B,
			1,LRE,
			1,RLE,
			1,PDF,
			1,LRO,
			1,RLO,
			1,WS,
			5,ET,
			15,ON,
			1,CS,
			26,ON,
			1,WS,
			16,BN,
			1,EN,
			3,L,
			6,EN,
			2,ET,
			3,ON,
			1,L,
			10,EN,
			2,ET,
			20,ON,
			48,ET,
			48,NSM,
			2,ON,
			1,L,
			4,ON,
			1,L,
			2,ON,
			10,L,
			1,ON,
			1,L,
			3,ON,
			5,L,
			6,ON,
			1,L,
			1,ON,
			1,L,
			1,ON,
			1,L,
			1,ON,
			4,L,
			1,ET,
			3,L,
			1,ON,
			7,L,
			3,ON,
			3,L,
			5,ON,
			5,L,
			22,ON,
			48,L,
			130,ON,
			2,ET,
			290,ON,
			69,L,
			26,ON,
			1,L,
			242,ON,
			20,EN,
			78,L,
			790,ON,
			256,L,
			1792,ON,
			1,WS,
			4,ON,
			3,L,
			25,ON,
			9,L,
			6,NSM,
			1,ON,
			5,L,
			2,ON,
			5,L,
			4,ON,
			88,L,
			2,NSM,
			2,ON,
			3,L,
			1,ON,
			90,L,
			1,ON,
			289,L,
			3,ON,
			48,L,
			16,ON,
			28,L,
			3,ON,
			50,L,
			15,ON,
			12,L,
			4,ON,
			167,L,
			4,ON,
			99,L,
			2,ON,
			31,L,
			1,ON,
			6592,L,
			64,ON,
			22160,L,
			1904,ON,
			20253,L,
			1,R,
			1,NSM,
			10,R,
			1,ET,
			38,R,
			494,AL,
			18,ON,
			173,AL,
			3,ON,
			48,NSM,
			32,ON,
			1,CS,
			1,ON,
			2,CS,
			1,ON,
			1,CS,
			9,ON,
			1,ET,
			2,ON,
			2,ET,
			5,ON,
			2,ET,
			5,ON,
			143,AL,
			2,BN,
			2,ON,
			3,ET,
			5,ON,
			1,ET,
			1,CS,
			1,ET,
			1,CS,
			1,ES,
			10,EN,
			1,CS,
			6,ON,
			26,L,
			6,ON,
			26,L,
			11,ON,
			122,L,
			2,ET,
			3,ON,
			3,ET,
			24,ON
			};

			int k=0;
			int Count;
			char type;
			unsigned short Herp=0;

			//base typening sani 862
			while(k<862)
			{
				Count= baseTypes[k++];
				type= (char)baseTypes[k++];
				while (Count>0)
				{
					rtypes[Herp++] = type;
					Count--;
				}
			}
}
