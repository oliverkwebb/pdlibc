int iscntrl(int c) { return (unsigned)c < ' ' || c == 0x7F; }
int isdigit(int c) { return c <= '9' && c >= '0'; }
int isgraph(int c) { return c > ' ' && c < 0x7F; }
int islower(int c) { return (unsigned)c - 'a' < 26; }
int isupper(int c) { return (unsigned)c - 'A' < 26; }
int isalpha(int c) { return islower(c) || isupper(c); } // Y
int isalnum(int c) { return isalpha(c) || isdigit(c); } // Y
int isprint(int c) { return c >= ' ' && c < 0x7F; }
int ispunct(int c) { return isgraph(c) && !isalnum(c); }
int isspace(int c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f'; }
int isxdigit(int c) { return isdigit(c) || (unsigned)c - 'a' < 6 || (unsigned)c - 'A' < 6; }
int tolower(int c) { return islower(c) ? c - ('A' - 'a') : c; }
int toupper(int c) { return isupper(c) ? c + ('A' - 'a') : c; }
