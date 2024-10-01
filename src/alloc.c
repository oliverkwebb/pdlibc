#include <stdlib.h>
extern void  *mmap(void *, size_t, int, int, int, long);
extern int  munmap(void *, size_t);

static struct mheader { // No need for attribute packed, all elements are the same size on LP64 systems
  unsigned long   sections; // Is 0 when a page isn't split
  unsigned long   size;
  struct mheader *prev;
  struct mheader *next;
} *mstart = NULL;

static struct mheader *getpage(struct mheader *prev, size_t size) {
  struct mheader *page = mmap(NULL, size, 0x3/*PROT_{READ,WRITE}*/, 0x22/*MAP_{ANON,PRIVATE}*/, -1, 0);

  page->sections = (size <= 0x1000) ? 1 : 0;
  page->prev     = prev;
  page->next     = NULL;
  page->size     = size;

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

void free(void *ptr) {
  if (!ptr) return;

  struct mheader *probe = mstart;
  while (probe && !((ptr - (void *)probe) < 0x1000 && (ptr - (void *)probe) >= 64))
    probe = probe->next;

  if (!probe) abort();

  if (probe->sections) probe->sections &= ~(1 << ((ptr - (void *)(probe)) / 64));

  if (!probe->sections || (probe->sections == 1 && probe != mstart)) {
    if (probe->prev) probe->prev->next = probe->next;
    if (probe->next) probe->next->prev = probe->prev;
    if (munmap(probe, probe->size)) abort();
  }
}

#include <string.h>

void *realloc(void *ptr, size_t size)
{
	if (!size) {
		free(ptr);
		return NULL;
	} else if (!ptr) {
		return malloc(size);
	} else {
		void *new = malloc(size);
		struct mheader *probe = mstart;
		while (probe && !((ptr - (void *)probe) < 0x1000 && (ptr - (void *)probe) >= 64))
			probe = probe->next;
		int origsize = probe->sections ? 64 : probe->size;
		memcpy(new, ptr, origsize < size ? origsize : size);
		free(ptr);
		return new;
	}
}
