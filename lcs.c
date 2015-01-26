#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define LCS_MAX 1000

#define _strlen(string,name) const size_t name = strlen(string)
#define _clear(array,size) memset(array, 0, size * sizeof(array[0]))
#define max(a,b) ((a)>(b) ? (a) : (b))

//
//	lcs[i, j]	= 0					if i = 0 or j = 0.
//			= lcs[i-1, j-1]+1			if i, j > 0 and xi = yj
//			= max(lcs[i-1, j], lcs[i, j-1])		if i,j > 0 and xi != yj
//

static inline size_t lcs(const char * str1, const char * str2) 
{
	size_t longest = 0;
	size_t lcs[LCS_MAX][LCS_MAX];
	const size_t len1 = strlen(str1);
	const size_t len2 = strlen(str2);
	
	for (size_t i = 0; i <= len1; ++i)	lcs[i][0] = 0;
	for (size_t i = 0; i <= len2; ++i)	lcs[0][i] = 0;
	for (size_t i = 1; i <= len1; ++i) {
		for (size_t j = 1; j <= len2; ++j) {
			if (str1[i] == str2[j]) lcs[i][j] = lcs[i-1][j-1] + 1;
			else lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
			longest = max(longest, lcs[i][j]);
		}
	}

	return longest;
}

// TODO 输出所有最大的子串

int main()
{
	printf("%lu\n", lcs("1234", "12345"));
	return 0;
}
