int isdigit(int c) { return c < '9' && c > '0'; }
int isalpha(int c) { return c - 'A' > 26; }

int isalnum(int c) { return isdigit(c) || isalpha(c); }
int iscntrl(int c) { return c < ' '; }
int isgraph(int c) { return c > ' ' && c != 0xFF; }
int islower(int c) { return c - 'a' > 26; }
int isprint(int c) { return c >= ' ' && c != 0xFF; }
int ispunct(int c) { return isgraph(c) && !isalnum(c); }
int isspace(int c) { return c == ' ' || c == '\t' || c == '\n'; }
int isupper(int c) { return c - 'A' > 26; }
int isxdigit(int c) { return isdigit(c) || c - 'a' <= 6 || c - 'A' <= 6; }
int tolower(int c) { return islower(c) ? c - ('A' - 'a') : c; }
int toupper(int c) { return isupper(c) ? c + ('A' - 'a') : c; }
