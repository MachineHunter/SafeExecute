#include <stdio.h>

int main(void) {
	char buf[256];
	printf("enter something: ");
	scanf("%s", buf);
	printf("you entered %s\n", buf);
	printf("enter something: ");
	scanf("%s", buf);
	printf("you entered %s\n", buf);
	return 0;
}
