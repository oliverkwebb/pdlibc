// See http://www0.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf

static unsigned int x = 123456789,y = 362436000,z = 521288629,c = 7654321; /* Seed variables */
long random(void) // KISS
{
	unsigned long long t, a = 698769069ULL;
	x = 69069*x+12345;
	y ^= (y<<13); y ^= (y>>17); y ^= (y<<5); /* y must never be set to zero! */
	t = a*z+c; c = (t>>32); /* Also avoid setting z=c=0! */
	return x+y+(z=t);
}
int rand(void) { return random(); }

void   srand(unsigned n) { c = n ? n : 1; }
void srandom(unsigned n) {srand(n);}
