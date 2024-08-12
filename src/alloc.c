#include <__syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PAGE HEADER: 64 bytes
0x00 -> 0x08: long long PAGE_TYPE (SPLIT=0; WHOLE=1; MP=2)
0x08 -> 0x10: Pointer to the next block
0x10 -> 0x18: Pointer to the previous block
0x18 -> 0x20: | SPLIT: Bitfield of which sections are allocated
              | MP: # of pages after this
0x20 -> 0x28: Beginning adress of page
0x28 -> 0x30: Ending adress of malloced range
0x30 -> 0x40: Padding
*/

struct __attribute__((packed)) mheader {
  unsigned long long ismulti;
  struct mheader *nextblock;
  struct mheader *prevblock;
  union {
    unsigned long long whichsections;
    unsigned long long npages;
  };
  void *startrange;
  void *endrange;
  long long endpadding_0;
  long long endpadding_1;
};

static struct mheader *mstart = NULL;

static int mmap_flags = 0x20 | 0x02; // MAP_ANON | MAP_PRIVATE
static int mmap_prots = 1 | 2 | 4;   // PROT_{READ,WRITE,EXEC}

static struct mheader *__new_page(struct mheader *prev, size_t size) {
  void *page = mmap(NULL, size, mmap_prots, mmap_flags, -1, 0);
  struct mheader *header = (struct mheader *)page;

  header->prevblock = prev;
  header->nextblock = NULL;
  header->startrange = page + 64;
  header->endrange = page + (size < 0x1000 ? 0x1000 : size);
  return header;
}

static struct mheader *__new_splitpage(struct mheader *prev) {
  void *page = __new_page(prev, 1);
  struct mheader *header = (struct mheader *)page;

  header->ismulti = 0;
  header->whichsections = 1; // The first section is always filled by the header
  header->endrange = page + 0x1000;
  return header;
}

static void __malloc_init() { mstart = __new_splitpage(NULL); }

void *malloc(size_t bytes) {
  if (!bytes) return NULL;
  if (!mstart) __malloc_init();

  if (bytes < 64) {
    struct mheader *probe = mstart, *trail;
    while (probe && (probe->ismulti || (!~probe->whichsections))) {
      trail = probe;
      probe = probe->nextblock;
    }
    if (probe) {
      int i = 0;
      while ((probe->whichsections >> i) & 1) i++;
      probe->whichsections |= (1 << i); // New allocation
      return (void *)(probe) + (64 * i);
    } else {
      trail->nextblock = __new_splitpage(trail);
      trail->nextblock->whichsections |= (1 << 2);
      return (void *)(trail->nextblock) + 64;
    }
  } else {
    struct mheader *probe = mstart;
    while (probe->nextblock) probe = probe->nextblock;
    probe->nextblock = __new_page(probe, bytes);
    probe->nextblock->ismulti = 1;
    probe->nextblock->npages = bytes;
    return probe->nextblock->startrange;
  }
}

static void __abort_free(void) {
  fputs("Invalid Free, Aborting\n", stderr);
  abort();
}

void free(void *ptr) {
  if (!ptr) return;

  struct mheader *probe = mstart;
  while (probe) {
    ptrdiff_t l = (void *)(ptr) - (void *)(probe);
    if (l < 0x1000 && l >= 0) break;
    probe = probe->nextblock;
  }

  if (probe) {
    if (!probe->ismulti) {
      int section = (ptr - (void *)(probe)) / 64;
      probe->whichsections &= ~(1 << section);
    }
    if (probe->ismulti || (!probe->ismulti && !probe->whichsections && probe != mstart)) {
      if (probe->prevblock) probe->prevblock->nextblock = probe->nextblock;
      if (probe->nextblock) probe->nextblock->prevblock = probe->prevblock;
      if (munmap(probe, probe->ismulti ? probe->npages : 0x1000)) __abort_free();
    }
  } else __abort_free();
}
