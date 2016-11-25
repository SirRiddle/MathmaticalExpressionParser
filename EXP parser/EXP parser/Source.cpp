#include "Parsing.h"

int main()
{
	Test("1+2+3+4");
	Test("000");
	Test("1*2*3*4");
	Test("1-2-3-4");
	Test("1/2/3/4");
	Test("1*2+3*4");
	Test("1+2*3+4");
	Test("(1+2)*(3+4)");
	Test("1+(2*3)*(4+5)");
	Test("1+(2*3)/4+5");
	Test("5/(4+3)/2");
	Test("1 + 2.5");
	Test("125");
	Test("-1");
	Test("-1+(-2)");
	Test("-1+(-2.0)");
	Test("   1*2,5");
	Test("   1*2.5e2");
	Test("M1 + 2.5");
	Test("1 + 2&5");
	Test("1 * 2.5.6");
	Test("1 ** 2.5");
	Test("*1 / 2.5");

	return 0;
}