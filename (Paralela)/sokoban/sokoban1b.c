#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
  
int w, h, n_boxes;
uint8_t *board, *goals, *live;
 
typedef uint16_t cidx_t;
typedef uint32_t hash_t;
typedef struct T T;
 
struct T { // variable length
	hash_t h;
	T *prev, *next, *qnext;
	cidx_t c[];
};
 
size_t state_size, block_size = 32;
T *block_root, *block_head;
 
enum { space, wall, player, box };
 
#define E "\033["
const char * const glyph1[] = { " ", "#", E"31m@"E"m", E"33m$"E"m"};
const char * const glyph2[] = { E"32m."E"m", "#", E"32m@"E"m", E"32m$"E"m"};
#undef E

T **buckets;
hash_t hash_size, fill_limit, filled;

T *atual, *done;

bool success(const T *s){
	for (int i = 1; i <= n_boxes; i++)
		if (!goals[s->c[i]]) return false;
	return true;
}

void show_board(const T *s){
	unsigned char b[w * h];
	memcpy(b, board, w * h);
 
	b[ s->c[0] ] = player;
	for (int i = 1; i <= n_boxes; i++)
		b[ s->c[i] ] = box;
 
	for (int i = 0; i < w * h; i++) {
		printf("%s", (goals[i] ? glyph2 : glyph1)[ b[i] ]);
		if (! ((1 + i) % w))
			putchar('\n');
	}
}

void show_moves(const T *s){
	if (s->prev)
		show_moves(s->prev);
	usleep(200000);
	printf("\033[H");
	show_board(s);
}

// K&R hash function... uh!
void hash(T *s){
	if (!s->h) {
		register hash_t ha = 0;
		cidx_t *p = s->c;
		for (int i = 0; i <= n_boxes; i++)
			ha = p[i] + 31 * ha;
		s->h = ha;
	}
}

T* newstate(T *parent) {
	T* next_of(T *s) {
		return (void*)((uint8_t*)s + state_size);
	}
 
	T *ptr;
	if (!block_head) {
		
		block_size *= 2;
		
		T *p = malloc(block_size * state_size);
		p->next = block_root;
		block_root = p;
		
		ptr = (void*)((uint8_t*)p + state_size * block_size);
		p = block_head = next_of(p);
		
		T *q;
		for (q = next_of(p); q < ptr; p = q, q = next_of(q))
			p->next = q;
		p->next = NULL;
	}
 
	ptr = block_head;
	block_head = block_head->next;
 
	ptr->prev = parent;
	ptr->h = 0;
	return ptr;
}
 
void unnewstate(T *p) {
	p->next = block_head;
	block_head = p;
}

// mark up positions where a box definitely should not be
void mark_live(const int c){
	const int y=c/w,  x=c%w;
	if (live[c]) return;
 
	live[c] = 1;
	if (y > 1 && board[c - w] != wall && board[c - w * 2] != wall)      mark_live(c - w);
	if (y < h - 2 && board[c + w] != wall && board[c + w * 2] != wall)  mark_live(c + w);
	if (x > 1 && board[c - 1] != wall && board[c - 2] != wall)          mark_live(c - 1);
	if (x < w - 2 && board[c + 1] != wall && board[c + 2] != wall)      mark_live(c + 1);
}

T *parse_board(const int y, const int x, const char *s){
	w = x, h = y;
	board = calloc(w * h, sizeof(uint8_t));
	goals = calloc(w * h, sizeof(uint8_t));
	live  = calloc(w * h, sizeof(uint8_t));
	n_boxes = 0;

	for (int i = 0; s[i]; i++) {
		switch(s[i]) {
    		case '#':	board[i] = wall; continue;
    		case '.':
    		case '+':	goals[i] = 1;
    		case '@':	continue;
    		case '*':	goals[i] = 1;
    		case '$':	n_boxes++;	continue;
		}
	}
 
	state_size = (sizeof(T) + (1 + n_boxes) * sizeof(cidx_t) + sizeof(int) - 1);
 
	T *state = newstate(NULL);
 
	for (int i = 0, j = 0; i < w * h; i++) {
		if (goals[i]) mark_live(i);
		if (s[i] == '$' || s[i] == '*') state->c[++j] = i;
		else if (s[i] == '@' || s[i] == '+') state->c[0] = i;
	}
 
	return state;
}
 
void extend_table(){
	int old_size = hash_size;
 
	if (!old_size) {
		hash_size = 1024;
		filled = 0;
		fill_limit = hash_size * 3 / 4; // 0.75 load factor
	} else {
		hash_size *= 2;
		fill_limit *= 2;
	}
 
	buckets = realloc(buckets, sizeof(T*) * hash_size);
	assert(buckets);
 
	// rehash
	memset(buckets + old_size, 0, sizeof(T*) * (hash_size - old_size));
 
	const hash_t bits = hash_size - 1;
	for (int i = 0; i < old_size; i++) {
		T *head = buckets[i];
		buckets[i] = NULL;
		while (head) {
			T *next = head->next;
			const int j = head->h & bits;
			head->next = buckets[j];
			buckets[j] = head;
			head = next;
		}
	}
}
 
T *lookup(T *s){
	hash(s);
	T *f = buckets[s->h & (hash_size - 1)];
	for (; f; f = f->next) {
		if (//(f->h == s->h) &&
			!memcmp(s->c, f->c, sizeof(cidx_t) * (1 + n_boxes)))
			break;
	}
 
	return f;
}
 
bool add_to_table(T *s){
	if (lookup(s)) {
		unnewstate(s);
		return false;
	}
 
	if (filled++ >= fill_limit)
		extend_table();
 
	hash_t i = s->h & (hash_size - 1);
 
	s->next = buckets[i];
	buckets[i] = s;
	return true;
}
 
T *move_me(T *s, const int dy, const int dx){
	const int y = s->c[0] / w;
	const int x = s->c[0] % w;
	const int y1 = y + dy;
	const int x1 = x + dx;
	const int c1 = y1 * w + x1;
 
	if (y1 < 0 || y1 > h || x1 < 0 || x1 > w || board[c1] == wall)
		return NULL;
 
	int at_box = 0;
	for (int i = 1; i <= n_boxes; i++) {
		if (s->c[i] == c1) {
			at_box = i;
			break;
		}
	}
 
	int c2;
	if (at_box) {
		c2 = c1 + dy * w + dx;
		if (board[c2] == wall || !live[c2])
			return NULL;
		for (int i = 1; i <= n_boxes; i++)
			if (s->c[i] == c2) return NULL;
	}
 
	T *n = newstate(s);
	memcpy(n->c + 1, s->c + 1, sizeof(cidx_t) * n_boxes);
 
	cidx_t *p = n->c;
	p[0] = c1;
 
	if (at_box) p[at_box] = c2;
 
	// leet bubble sort
	for (int i = n_boxes; --i; ) {
		cidx_t t = 0;
		for (int j = 1; j < i; j++) {
			if (p[j] > p[j + 1])
				t = p[j], p[j] = p[j+1], p[j+1] = t;
		}
		if (!t) break;
	}
 
	return n;
}

void queue_move(T *s){
	if (s && add_to_table(s)){
    	if (success(s)) {
    		puts("\nSuccess!");
    		done = s;
    	}else{
     
        	s->qnext = atual;
        	atual = s;
    	}
    }
}
 
int main(){
	T *s = parse_board(
		11, 19,
		"    #####          "
		"    #   #          "
		"    #   #          "
		"  ### #$##         "
		"  #      #         "
		"### #$## #   ######"
		"#   # ## #####   .#"
		"# $   $         ..#"
		"##### ### #@##   .#"
		"    #     #########"
		"    #######        "
    );
 
	show_board(s);
	extend_table();
	queue_move(s);
	
	for (int i = 0; !done; i++) {
		printf("depth %d\r", i);
		fflush(stdout);
 
		
		T *head = atual;
		atual = NULL;
		for (; head && !done; head = head->qnext){
			

			s = move_me(head, 1,  0);
        
        	if (s && add_to_table(s)){
            	if (success(s)) {
            		puts("\nSuccess!");
            		done = s;
            	}else{
             
                	s->qnext = atual;
                	atual = s;
            	}
            }
		
			
			queue_move(move_me(head, -1,  0));
			queue_move(move_me(head,  0,  1));
		    queue_move(move_me(head,  0, -1));
		}
 
		if (!atual) {
			puts("no solution?");
			return 1;
		}
		
	}
 
	printf("press any key to see moves\n");
	getchar(), puts("\033[H\033[J");
	show_moves(done);
 
	free(buckets);
	free(board);
	free(goals);
	free(live);
 
	while (block_root) {
		void *tmp = block_root->next;
		free(block_root);
		block_root = tmp;
	}
 
	return 0;
}