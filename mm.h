/* $begin mallocinterface */
int mm_init(void); 
void *mm_malloc(size_t size); 
void mm_free(void *bp);
/* $end mallocinterface */

void mm_checkheap(int verbose);
void *mm_realloc(void *ptr, size_t size);

#define FIRST_FIT 1
#define BEST_FIT 0
void change_fit(int fit);
void blocklist();

/* Unused. Just to keep us compatible with the 15-213 malloc driver */
typedef struct {
    char *team;
    char *name1, *email1;
    char *name2, *email2;
} team_t;

extern team_t team;
