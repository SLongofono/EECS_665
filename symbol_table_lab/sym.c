/* symbol table management */

# include <stdio.h>
// # include <malloc.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include "cc.h"
# include "sym.h"

# define STABSIZE 119			   /* hash table size for strings */
# define ITABSIZE 37			   /* hash table size for identifiers */
# define MAXSTK   1000

struct sem_rec *stk[MAXSTK];               /* stack of ptrs to semantic recs */
struct sem_rec **top = stk;                /* stack pointer */
struct sem_rec **prevtop = NULL;           /* previous top */

/*
 * A note on semantic records...
 *
 * The semantic records are used to compute and otherwise track the values of
 * expressions as Yacc moves through the input tokens.  sem.h declares a
 * smattering of functions that are called by Yacc as it encounters certain
 * productions.  For the purposes of the symbol table, we need to create
 * additional stack entries for each block, so that they are there when the
 * rest of the tokens within the block are evaluated and passed back upstream.
 *
 * Note that all the actual populating and computation of semantic records is
 * handled in the yacc file.  Here, we only care about separating scope by way
 * of a stack with pointer to the most recent semantic records.
 */

int numrecs = 0;                           /* number of semantic recs */

int level = 0;                             /* current block level */

struct s_chain {
	char *s_ptr;                            /* string pointer */
	struct s_chain *s_next;                 /* next in chain */
	} *str_table[STABSIZE] = {0};           /* string hash table */

struct id_entry *id_table[ITABSIZE] = {0}; /* identifier hash table */

/*
 *  dump - dump identifiers with block level >= blev to f
 */
void dump(int blev, FILE *f)
{
	fprintf(f, "Dumping identifier table\n");

	/*
	 * For each entry in the id_table
	 */
	for(int i = 0; i < ITABSIZE; ++i){
		if(NULL != id_table[i]){
			struct id_entry *temp = id_table[i];
			while(NULL != temp){
				// If the entry level matches the current
				// level...
				if(temp->i_blevel == level){
					/* 
					 * Dump all relevant fields;  we want
					 * the name, the block level, the type
					 * mapping, and the bool saying if it
					 * is defined or not
					 */
					fprintf(f, "%-12s\t", temp->i_name);
					fprintf(f, "%d\t", level);
					fprintf(f, "%d\t", temp->i_type);
					fprintf(f, "%d\n", temp->i_defined);
				}

				temp = temp->i_link;
			} // End while(NULL...)
		} // End if(NULL...)
	} // End for(...)
}


/*
 * new_block - save previous stack top and mark a new one
 *
 * How does this work?
 *
 * 1. save_rec sets the current stack top to look at the pointer passed in,
 *    and then increments top
 * 2. prevtop is set to look at the same record it just pointed to, which is
 *    now at top - 1
 *
 * This is written in a confusing way, but really it's just putting it into
 * the stack and advancing the pointers.
 */
void new_block()
{
	save_rec((struct sem_rec *) prevtop);
	prevtop = top - 1;
}


/*
 * exit_block - exit block, free up semantic records
 *
 * How does this work?
 *
 * Assumptions: top is always looking at an unallocated stack address
 * 
 * 1. Decrement top to actually look at the last element
 * 2. Decrement stack size (numrecs)
 * 3. Free the element on top, and decrement top again
 * 4. Repeat until top and prevtop are the same address
 * 5. Set prevtop to look at top
 *
 * This is strange... it should not be decrementing top again.  This seems to
 * violating the stack pointer position relative to prevtop.  Following this
 * same trend of needlessly confusing code, the last line should read:
 *
 * 	prevtop = (struct sem_rec **) *top++;
 */
void exit_block()
{
	for (top--; top > prevtop;) {
		numrecs--;
		free((char *) *top--);
	}
	prevtop = (struct sem_rec **) *top;
}


/*
 * enterblock - enter a new block
 */
void enterblock()
{
	/*
	 * Steps:
	 *
	 *	increment level
	 *	create a new block for this level
	 */
	level++;
	new_block();
}


/*
 * install - install name with block level blev, return ptr
 */
struct id_entry *install(char *name, int blev)
{
	struct id_entry *ip, **q;
	int index;

	if (blev < 0)
		blev = level;

	/* allocate space */
	ip = (struct id_entry *) alloc(sizeof(struct id_entry));

	/* set fields of symbol table */
	ip->i_name = name;
	ip->i_blevel = blev;
	index = hash(name) % ITABSIZE;
	for (q = &id_table[index]; *q; q = &((*q)->i_link))
		if (blev >= (*q)->i_blevel)
			break;
	ip->i_link = *q;
	*q = ip;
	return (ip);
}


/*
 * leaveblock - exit a block
 */
void leaveblock()
{

	/*
	 * Steps:
	 *
	 * 	print out table at this level
	 * 	clear out table at this level
	 * 	decrement level
	 */

	dump(level, stdout);

	struct id_entry *temp;

	for(int i =0; i< ITABSIZE; ++i){
		if(NULL != id_table[i]){
			// For each entry, if it belongs to the current scope,
			// it needs to be removed.
			struct id_entry *cur = id_table[i];
			while(NULL != cur){
					
				// These are set up like a linked list.  So if
				// we remove one, simply set the id table
				// entry to look at the next one.
				if(level == cur->i_blevel){
					id_table[i] = cur->i_link;
					free(cur);
				}
				// We don't want to set cur to NULL,
				// it's a struct* so after freeing it,
				// referencing cur->i_link will take us
				// to that offset within the memory,
				// and its zero value will kill the
				// loop
				cur = cur->i_link;
			}
		}
	}
	level--;
	exit_block();
}


/*
 * lookup - lookup name, return ptr; use default scope if blev == 0
 */
struct id_entry *lookup(char *name, int blev)
{
	struct id_entry *p;

	for (p = id_table[hash(name)%ITABSIZE]; p; p = p->i_link)
		if (name == p->i_name && (blev == 0 || blev == p->i_blevel))
			return (p);
	return (NULL);
}


/*
 * sdump - dump string table to f
 */
void sdump(FILE *f)
{
	struct s_chain **s, *p;

	fprintf(f, "Dumping string table\n");
	for (s = str_table; s < &str_table[STABSIZE]; s++)
		for (p = *s; p; p = p->s_next)
			fprintf(f, "%s\n", p->s_ptr);
}


/*
 * slookup - lookup str in string table, install if necessary, return ptr
 */
char *slookup(char str[])
{
	struct s_chain *p;
	int i, k;

	for (k = i = 0; i < 5; i++)	/* simple hash function */
		if (str[i])
			k += str[i];
		else
			break;

	k %= STABSIZE;
	for (p = str_table[k]; p; p = p->s_next)
		if (strcmp(str, p->s_ptr) == 0)
			return (p->s_ptr);
	p = (struct s_chain *) alloc(sizeof(struct s_chain));
	p->s_next = str_table[k];
	str_table[k] = p;
	p->s_ptr = (char *) alloc((unsigned) strlen((const char*)str) + 1);
	p->s_ptr = strcpy(p->s_ptr, str);
	return (p->s_ptr);
}


/*
 * hash - hash name, turn address into hash number
 */
intptr_t hash(char *s)
{
	return((intptr_t)s);
}


/*
 * alloc - alloc space
 */
char *alloc(unsigned n)
{
	char *p;

	if ((p = calloc(1, n)) == NULL) {
		yyerror("csem: out of space");
		exit (1);
	}
	return (p);
}


/*
 * save_rec - save a semantic record so it can be reclaimed later
 */
void save_rec(struct sem_rec *s)
{
	/* save on stack so can reclaim */
	if (numrecs++ > MAXSTK) {
		fprintf(stderr, "too many semantic records\n");
		exit(1);
	}
	*top++ = s;
}
