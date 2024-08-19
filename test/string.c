#include <string.h>
#include <stdio.h>

int main()
{
	char s1[] = "Meow :3333", s2[] = "123456789ABCDEFGHIJKLMNOP";
	char buf[10], buf2[30];

	// memset
	memset(buf2, 40, 30);
	printf("%d\n", (int)buf2[3]);

	// memcpy
	memcpy(buf, buf2+5, 10);
	printf("%d\n", (int)buf[8]);

	// memmove
	memmove(s2+5, s2+8, 5);
	puts(s2+5);

	// strcpy
	strcpy(s2, "Meow");
	puts(s2);

	// strcat
	strcat(s2, " UwU");
	puts(s2);

	// memcmp
	printf("%d", memcmp("\0\0\0\0", "\xde\xad\xbe\xef", 5) > 0);
	printf("%d", memcmp("\xde\xad\xbe\xef", "\0\0\0\0", 5) < 0);
	printf("%d\n", memcmp("\0\0\0\0", "\0\0\0\0", 5));

	// strchr && strrchr
	char *foo = "A monad is a moniod in a catagory of endofunctors";
	puts(strchr(foo, 'o'));
	puts(strrchr(foo, 'o'));
	puts(memchr(foo, 'o', strlen(foo)));

	// strcmp && strncmp
	printf("%d, ", strcmp("Prrrrr", "Meow"));
	printf("%d, ", strcmp("Meow", "Meow"));
	printf("%d\n", strcmp("Awawawawawa", "Meow"));
	printf("%d\n", strncmp("Meow", "Meowwwww", 4));

	// strncpy && strncat
	printf("%s\n", strncat(s2, s1, 7));
	puts(s2);
	printf("%s\n", strncpy(s2, s1, 7));
	puts(s2);

}
