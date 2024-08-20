#include <stdlib.h>
#include <stdio.h>
extern void  *mmap(void *, size_t, int, int, int, long);
extern int  munmap(void *, size_t);

static struct mheader { // No need for attribute packed, all elements are the same size on LP64 systems
  unsigned long   sections; // Is 0 when a page isn't split
  struct mheader *prev;
  struct mheader *next;
  struct mheader *end;     // Not actually a mheader, makes pointer math easier
} *mstart = NULL;

static struct mheader *getpage(struct mheader *prev, size_t size) {
  struct mheader *page = mmap(NULL, size, 0x7 /*PROT_{READ,WRITE,EXEC}*/, 0x22 /*MAP_{ANON,PRIVATE}*/, -1, 0);

  page->sections = (size <= 0x1000) ? 1 : 0;
  page->prev     = prev;
  page->next     = NULL;
  page->end      = page + size;

  return page;
}

void *malloc(size_t bytes) {
  if (!bytes) return NULL;
  if (!mstart) mstart = getpage(NULL, 0x1000);

  struct mheader *probe = mstart;

  if (bytes > 64) {
    while (probe->next) probe = probe->next;
    return (void *)(probe->next = getpage(probe, bytes)) + 64;
  }

  while (probe->next && (!probe->next->sections || (!~probe->next->sections)))
  	probe = probe->next;

  if (!probe->next) probe->next = getpage(probe, 0x1000);

  int section = __builtin_ctzll(~probe->next->sections); // Find first unset bit
  probe->next->sections |= (1 << section);               // Mark new allocation
  return (void *)(probe->next) + (64 * section);
}

static void badfree(void) {
  fputs("Invalid Free, Aborting\n", stderr);
  abort();
}

void free(void *ptr) {
  if (!ptr) return;

  struct mheader *probe = mstart;
  while (probe && !((ptr - (void *)probe) < 0x1000 && (ptr - (void *)probe) >= 64))
    probe = probe->next;

  if (!probe) badfree();

  if (probe->sections) probe->sections &= ~(1 << ((ptr - (void *)(probe)) / 64));

  if (!probe->sections || (probe->sections == 1 && probe != mstart)) {
    probe->prev->next = probe->next; // Not first page (isn't split || (...  && isn't mstart))
    if (probe->next) probe->next->prev = probe->prev;
    if (munmap(probe, probe->end - probe)) badfree();
  }
}

#include <string.h>

void *calloc(size_t nmemb, size_t size)
{
	void *p = malloc(nmemb * size);
	memset(p, 0, nmemb * size);
	return p;
}

// Debug function
void mallinfo(void)
{
  struct mheader *probe = mstart;
  int mp = 0, sp = 0;
  while (probe) {
  	if (!probe->sections) {
  		fprintf(stderr, "Large Alloc: %p\n", probe);
  		mp++;
  	}
  	else {
  		fprintf(stderr, "Split Alloc: %p, Blocks %p\n", probe,
  			(void *)(probe->sections));
  		sp++;
  	}
  	probe = probe->next;
  }
  fprintf(stderr, "Single %d, Split %d, Total %d\n", mp, sp, mp+sp);
}
