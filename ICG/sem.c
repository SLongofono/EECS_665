/* @file 	sem.c
 * @author 	Stephen Longofono
 * @date	November 2017
 * @brief	This program works together with the grammar defined in
 * 		cgram.y to produce intermediate code.
 */


# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"

#include <string.h>
#define MAXLOOPS 500

// Forward declare the error function so gcc will shut up
extern void yyerror(const char *s);

// Tracks formal parameters and their types in the current scope level
extern int formalnum;
extern char formaltypes[];

// Tracks local variables and their types in the current scope level
extern int localnum;
extern char localtypes[];

// Tracks widths of locals 
extern int localwidths[];

int numlabels = 0;                      /* total labels in file */
int numblabels = 0;                     /* total backpatch labels in file */
int numloops = 0;			// Track how many times we have looped
struct sem_rec* loops[MAXLOOPS];	// Track n for patching

int infunc = 0;				// If we are in a function, we need to track the type
					// to handle implicit returns of
					// doubles
int functype = 0;			

void deepcopy(struct sem_rec *, struct sem_rec *);	// Local helper


/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k){

	/* Traverse the list, updating the place as we go.
	 *
	 * Note: for any given call, we can't know a priori whether we are
	 * updating the true or the false list, only that we need to update
	 * all the entries to the given label number.
	 *
	 * To handle this, the record passed in should have been merged and
	 * thus collapsed into a single list.  Not every record will have both
	 * defined, and to keep things simple, we use the convention of
	 * traversing only through s_link.
	 */

	struct sem_rec *curr = p;
	while(NULL != curr){
		printf("B%d=L%d\n", p->s_place, k);
		curr = curr->back.s_link;
	}
}


/*
 * bgnstmt - encountered the beginning of a statement
 */
void bgnstmt(){

	extern int lineno;
	printf("bgnstmt %d\n", lineno);
}


/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args){

	// Per C calling convention, the arguments should be prepared before
	// the call is made (i.e. pushed onto the stack.
	struct sem_rec *curr = args;
	int numargs = 0;

	while(NULL != curr){
		gen("arg", (struct sem_rec *)NULL, curr, curr->s_mode);
		numargs++;
		curr = curr->back.s_link;
	}

	// Check if it exists like we did for ids
	struct id_entry *p;

	if((p = lookup(f, 0)) == NULL){
		p = install(f, 0);
		p->i_type = T_PROC;
		// Per stackexchange, C cannot have local functions.  They may
		// be forward declared and used within a function, but
		// otherwise they should eb global to the file.
		p->i_scope = GLOBAL;
		p->i_defined = 1;
	}
	
	// At this point, we have a valid entry

	// Name the global identifier
	printf("t%d := global %s\n", nexttemp(), f);

	/*
	 * Use gen to print out the call
	 *
	 * We want to pass in the char* f, a null node with the name of global
	 * id above as its place, another null node with its place as the
	 * number of args, and the type associated with this function from the
	 * symbol table.
	 */

	return gen("f",
		   node(currtemp(), 0, (struct sem_rec *)NULL, (struct sem_rec *)NULL),
		   node(numargs, 0, (struct sem_rec *)NULL, (struct sem_rec *)NULL),
		   p->i_type);
}


/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2){

	// From the given grammar 6.43, rule 2
	// Fill in jump if first condition is true to the next condition code
	backpatch(e1->back.s_true, m);

	// Return record has merged false lists and the modified true list
	return node(0, 0, e2->back.s_true, merge(e1->s_false, e2->s_false));
}


/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e){
	
	struct sem_rec *t1;

	if(e){
		/* 
		 * For reference, node takes in two integers and two sem_rec*,
		 * representing place, mode, truelist, and falselist.  In this
		 * case, we need to generate a temporary for comparison from
		 * zero.  This is kind of a complicated process.
		 *
		 * First, gen is called, using not equals as the operator, the
		 * return of a cast of zero to the type of the given
		 * expression e, and the given expression's type.
		 *
		 * Constant does a lookup in the global scope (0) to see if an
		 * entry exists for the character given ('0').  If it does not
		 * exists, it installs it into the symbol table.  Within
		 * con(), it prints out a constant declaration in a temporary
		 * of the form ti := 0.  Then, it creates a new semantic
		 * record and the place used for ti with an integer type.
		 *
		 * This is fed into cast along with the type of e.  Cast
		 * checks to see if the record type is double and the
		 * conversion type is not or vice versa.  If either condition
		 * holds, a convert statement is printed using gen.
		 * otherwise, the semantic record is returned as is.
		 *
		 * Within gen, with cv passed as the operation, a new
		 * temporary is printed to be assigned.  Then, it falls
		 * through to print the op ('cv') and then is caught by the
		 * check for type double, which prints f, space, and finally
		 * is caught by the if y!= null clause to print the ti label.
		 * gen then returns a new sem_rec with the given type.
		 *
		 * The sem_rec returned by the call to gen in cast is passed
		 * upstream and then back down into gen for the call
		 * immediately below.  Again, a new temporary is preinted for
		 * assignment.  This time, the op is caught by the
		 * is(x!= NULL && *op != 'f') clause, and the place of the
		 * e sem_rec is printed, followed by the op, and then the
		 * place of the cast sem_rec: tnew := te !=f ti.  So we have
		 * converted zero if necessary, given it a temp, and now finally
		 * we are making a comparison and assigning it to a temp.
		 * 
		 * After returning, t1 holds the place of the result, so we
		 * can issue the conditional branch followed by the failure
		 * branch.  To wrap up, return a node with the truelist as the
		 * condition true record and the false list as the second
		 * branch.
		 */

		int realtype = e->s_mode &~ T_ADDR;
		//printf("GIVEN TYPE: %d, REAL: %d\n", e->s_mode, realtype);
		t1 = gen("!=", e, cast(con("0"), realtype), realtype);
		numblabels++;
		printf("bt t%d B%d\n", t1->s_place, numblabels);
		numblabels++;
		printf("br B%d\n", numblabels);
		return 	node(0,
			     0,
			     node(numblabels-1, 0, (struct sem_rec *) NULL, (struct sem_rec *) NULL),
			     node(numblabels, 0, (struct sem_rec *) NULL, (struct sem_rec *) NULL)
			);
	}
	else{
		fprintf(stderr, "Argument sem_rec is NULL\n");
	}
}


/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e){
	
	// From the given grammar 6.43, rule 3
	// Reverses the true and false lists
	return node(0, 0, e->s_false, e->back.s_true);
}


/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2){
	
	// From the given grammar 6.43 rule 1
	// Fill in with the label for short circuit destination of OR
	backpatch(e1->s_false, m);

	// Return record includes both true lists or the modified false list
	return node(0, 0, merge(e1->back.s_true, e2->back.s_true), e2->s_false);
}


/*
 * con - constant reference in an expression
 */
struct sem_rec *con(char *x){
	
	struct id_entry *p;

	if((p = lookup(x, 0)) == NULL){
		p = install(x, 0);
		p->i_type = T_INT;
		p->i_scope = GLOBAL;
		p->i_defined = 1;
	}

	/* print the quad t%d = const */
	printf("t%d := %s\n", nexttemp(), x);

	/* construct a new node corresponding to this constant generation 
	  into a temporary. This will allow this temporary to be referenced
	  in an expression later*/
	return(node(currtemp(), p->i_type, (struct sem_rec *) NULL, (struct sem_rec *) NULL));
}


/*
 * dobreak - break statement
 */
void dobreak(){
	
	// Jump out using nearest known endpoint label
	
	// Print out intermediate code
	numblabels++;
	printf("br B%d\n", numblabels);

	/*
	 * We need to incorporate the falselist of the current
	 * loop with the label we print.
	 */
	struct sem_rec *curr = loops[numloops]->s_false;

	if(NULL != curr){
		// The semantic record is a part of a list already.  Find the
		// end.
		while(NULL != curr->back.s_link){
			curr = curr->back.s_link;
		}
	}
	
	// Make a new node for the label number generated above
	curr = node(numblabels, 0, (struct sem_rec *)NULL, (struct sem_rec *)NULL);
}


/*
 * docontinue - continue statement
 */
void docontinue(){
	
	// Jump back to nearest known loop start label
	
	// Print out intermediate code
	numblabels++;
	printf("br B%d\n", numblabels);

	/*
	 * We need to incorporate the truelist of the current
	 * loop with the label we print.
	 */
	struct sem_rec *curr = loops[numloops]->back.s_true;

	if(NULL != curr){
		// The semantic record is a part of a list already.  Find the
		// end.
		while(NULL != curr->back.s_link){
			curr = curr->back.s_link;
		}
	}
	
	// Make a new node for the label number generated above
	curr = node(numblabels, 0, (struct sem_rec *)NULL, (struct sem_rec *)NULL);
}


/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3){

	/*
	 * From the grammaer in cgram.y
	 * Do m1 s lblstmt WHILE ( m2 cexpr e ); m3
	 *
	 * Three points of interest:
	 *
	 * do{
	 *	m1:
	 *	<stmts>
	 * }
	 * while(
	 * 		m2:
	 *		expr
	 * 	)
	 * m3
	 *
	 * So we want e->true to go back to m1
	 * so we want e->false to go to m3
	 * so m2 needs to be linked to the n(), but that isn't given.
	 * If the n exists, it would need to be backpatch to m2.  We need to
	 * track loops somehow, so we have an existing n to use.
	 *
	 */
	backpatch(e->back.s_true, m1);
	backpatch(e->s_false, m3);

	/*
	 * To track looping, we need to track the beginning and endpoint
	 * targets for the loop clause.  This will allow access to each for
	 * break and continue when we are not in this function.  We want to
	 * use m2 to increment and start another loop, or m4 to kick out
	 */
	
	backpatch(loops[numloops]->back.s_true, m2);

	// Pass the endpoint target to endloopscope to let it clean up.
	endloopscope(m3);
}


/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1, int m3,
	   struct sem_rec *n2, int m4){
	/*
	 * From cgram.y, we see the following pattern:
	 *
	 * for(i=j; i<k; i++) matches
	 * e1 (assignment)
	 * m1: e2 (condition check)
	 * m2: increment n1()
	 * m3: loop statements n2()
	 * m4: end construct
	 *
	 * m1 labels the condition
	 * m2 labels the increment, followed by a jump to the condition at m1
	 * m3 is the beginning of the loop section
	 * n1 is the jump to the condition check after incrementing
	 * The final m is the endpoint
	 * n2 is the jump to the increment label m2 after each loop
	 *
	 * So e2 true jumps to m3, e2 false jumps to m4
	 *
	 * After incrementing, we need to jump into the loop section, so n1
	 * unconditionally jumps to m2
	 *
	 * n2 starts the process over, so it needs to jump to the condition
	 * label m1
	 */
	backpatch(e2->back.s_true, m3);
	backpatch(e2->s_false, m4);
	backpatch(n1, m1);
	backpatch(n2, m2);

	/*
	 * To track looping, we need to track the beginning and endpoint
	 * targets for the loop clause.  This will allow access to each for
	 * break and continue when we are not in this function.  We want to
	 * use m2 to increment and start another loop, or m4 to kick out
	 */
	
	backpatch(loops[numloops]->back.s_true, m2);

	// Pass the endpoint target to endloopscope to let it clean up.
	endloopscope(m4);
}


/*
 * dogoto - goto statement
 */
void dogoto(char *id){
	
	// Use the symbol table to get the appropriate entry to jump to
	printf("br L%s\n", slookup(id));
}


/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2){

	// Update the true label to jump into the then clause
	backpatch(e->back.s_true, m1);
	
	// Update the false label to jump to the end 
	backpatch(e->s_false, m2);
}


/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
	      int m2, int m3){
	
	// Update the true label to jump into the then clause
	backpatch(e->back.s_true, m1);
	
	// Update the false label to the else clause
	backpatch(e->s_false, m2);

	// Update the end of each clause to jump to the end
	backpatch(n, m3);
}


/*
 * doret - return statement
 * 
 */
void doret(struct sem_rec *e){
	if(NULL != e){
		// Pass first record as null to catch return case properly
		gen("ret", (struct sem_rec *)NULL, e,  e->s_mode);
	}
	else{
		// If there is no return, use the function type to print
		// return properly
		if(functype & T_DOUBLE){
			printf("retf\n");
		}
		else{
			printf("reti\n");
		}
	}
}


/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n,
	     int m3){

	// Update with earliest label if while condition if true
	backpatch(e->back.s_true, m2);

	// Update with end label if result of the while condition if false
	backpatch(e->s_false, m3);

	// Update the end of the while loop with a jump back to the beginning
	backpatch(n, m1);

	// To track looping, need to set the current loop record to use the
	// same target as n.  In this way, we can implement continue without
	// direct access to m and n as given here.
	backpatch(loops[numloops]->back.s_true, m1);

	// Since this is the last thing done for the loop, and at this point
	// everything is computed, adjust the scope and pass in the endpoint 
	endloopscope(m3);
}


/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m){
	
	/*
	 * Now, we need to clean up the looping tracking.  First, patch in the
	 * given m, such that it will jump to the endpoint.  Then, set the
	 * current loop pointer to NULL and decrement the loop counter
	 */
	
	backpatch(loops[numloops]->s_false, m);
	loops[numloops] = NULL;
	numloops--;

	// Close scope in symbol tablew
	leaveblock();
}


/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e){
	
	return merge(l,e);
}


/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p){
	
	/* The return of fname is passed in, per the grammar
	 * This allows us to print out the formal arguments based on their
	 * type.  We want the form: "formal" <b> where b is the size in bytes
	 * of the parameter type.
	 *
	 *
	 * Looking at dcl, we see that declarations are stored as letters in
	 * the formaltypes and localtypes arrays, or in an array (in which
	 * case the intermediate code is already handled for us by dclr).  So
	 * per the examples, we simply traverse these two arrays, printing the
	 * as by the time fhead is called, they are already populated with the
	 * types of formal and local parameters as they were encountered.
	 *
	 * Per the examples, we print formals first, then locals.
	 */

	for(int i = 0; i<formalnum; ++i){
		if('i' == formaltypes[i]){
			// integer types 4 bytes
			printf("formal 4\n");
		}
		else{
			// others are 8 (pointer or double)
			printf("formal 8\n");
		}
	}

	for(int i = 0; i<localnum; ++i){
		if('i' == localtypes[i]){
			// integer types 4 bytes
			printf("localloc 4\n");
		}
		else{
			// others are 8 (pointer or double)
			printf("localloc 8\n");
		}		
	}
}


/*
 * fname - function declaration
 */
struct id_entry *fname(int t, char *id){
	// Width is byte width of the return
	int width;
	infunc = 1;
	switch(t){
		case T_INT:
			width = 4;
			functype = T_INT;
			break;
		default:
			// Everything else is system address length, including
			// doubles
			width = 8;
			functype = T_DOUBLE;
	}

	// Print out the intermediate code
	printf("func %s\n", id);
	
	// Initialize formals and locals list for this context
	formalnum = 0;
	localnum = 0;

	// Create symbol table entry for the given function using the given
	// type t, the name id, and the width.
	struct id_entry * ret = dclr(id, t, width);


	// Create a new scope for the function
	enterblock();
	

	if(NULL != ret){
		return ret;
	}
	
	yyerror("function declaration returned null");
	
	return (struct id_entry *) NULL;
}


/*
 * ftail - end of function body
 */
void ftail(){
	
	// Print intermediate code stmt
	printf("fend\n");
	
	// Leave function scope
	leaveblock();
	infunc = 0;
}


/*
 * id - variable reference
 */
struct sem_rec *id(char *x){
	struct id_entry *p;

	if((p = lookup(x, 0)) == NULL){
		yyerror("undeclared identifier");
		p = install(x, -1);
		p->i_type = T_INT;
		p->i_scope = LOCAL;
		p->i_defined = 1;
	}
	if (p->i_scope == GLOBAL){
		printf("t%d := global %s\n", nexttemp(), x);
	}
	else if(p->i_scope == LOCAL){
		printf("t%d := local %d\n", nexttemp(), p->i_offset);
	}
	else if(p->i_scope == PARAM){
		printf("t%d := param %d\n", nexttemp(), p->i_offset);
		if(p->i_type & T_ARRAY){
	   		(void) nexttemp();
			printf("t%d := @i t%d\n", currtemp(), currtemp()-1);
		}
	}

	/* add the T_ADDR to know that it is still an address */
	return node(	currtemp(),
			p->i_type|T_ADDR,
			(struct sem_rec *) NULL,
			(struct sem_rec *) NULL
			);
}


/*
 * index - subscript
 */
struct sem_rec *tom_index(struct sem_rec *x, struct sem_rec *i){

	return (gen("[]", x, cast(i, T_INT), x->s_mode&~(T_ARRAY)));
}


/*
 * labeldcl - process a label declaration
 */
void labeldcl(char *id){
	// Cue the lookup table to install an id (or error out)
	slookup(id);
	
	// Make a new local label
	numlabels++;
	printf("label L%d\n", numlabels);
	
}


/*
 * m - generate label and return next temporary number
 */
int m(){

	/*
	 * M is used as an anchor of sorts, to create a label to return to in
	 * any branching construct.  For each, we need a unique number to
	 * refer to it by, which we track with the global numlabels.
	 */

	numlabels++;
	printf("label L%d\n", numlabels);
	return numlabels;
}


/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n(){
	/*
	 * N represents a common endpoint that branching constructs can use to
	 * move to a specific point in a looping construct.  This might be the
	 * end, but not necessarily.
	 */

	// Print the goto as an unconditional branch
	numblabels++;
	printf("br B%d\n", numblabels);
	return node(numblabels, 0, (struct sem_rec *)NULL, (struct sem_rec *)NULL);
}


/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y){

	if(*op == '@' && !(y->s_mode&T_ARRAY)){
	 /* get rid of T_ADDR if it is being dereferenced so can handle
	    T_DOUBLE types correctly */
		y->s_mode &= ~T_ADDR;
		return (gen(op, (struct sem_rec *) NULL, y, y->s_mode));
	}
	else{
		return gen(op, (struct sem_rec *)NULL, y, y->s_mode);
	}
}


/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y){
	
	struct sem_rec *p;
	if(NULL != x){
		if(x->s_mode & T_DOUBLE && y->s_mode & T_INT){
			p = cast(y, x->s_mode);
			deepcopy(p,y);
		}
		else if (x->s_mode & T_INT && y->s_mode & T_DOUBLE){
			p = cast(x, y->s_mode);
			deepcopy(p,x);
		}
		return gen(op,x,y,y->s_mode);
	}
	else{
		return (struct sem_rec *)NULL;
	}
}


/*
 * opb - bitwise operators
 */
struct sem_rec *opb(char *op, struct sem_rec *x, struct sem_rec *y){

	struct sem_rec *p;

	if(x->s_mode & T_DOUBLE || y->s_mode & T_DOUBLE){
		yyerror("Double operands with bitwise operator");
		return ((struct sem_rec *) NULL);
	}
	else{
		return gen(op,x,y,T_INT);
	}
}


/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y){

	int realtypex = x->s_mode & ~T_ADDR;
	int realtypey = y->s_mode & ~T_ADDR;

	struct sem_rec *p;
	//if(x->s_mode & T_DOUBLE && y->s_mode & T_INT){
	if(realtypex > realtypey){
		p = cast(y, x->s_mode);
		deepcopy(p,y);
	}
	//else if (x->s_mode & T_INT && y->s_mode & T_DOUBLE){
	else if(realtypey > realtypex){
		p = cast(x, y->s_mode);
		deepcopy(p,x);
	}

	struct sem_rec *ret = gen(op, x, y,y->s_mode);

	// Need to generate the branches to be taken for this
	// condition per the grammar 6.43
	numblabels++;
	printf("bt t%d B%d\n", currtemp(), numblabels);
	ret->back.s_true = node(numblabels, x->s_mode, (struct sem_rec *)NULL, (struct sem_rec *)NULL);
	
	numblabels++;
	ret->s_false = node(numblabels, x->s_mode, (struct sem_rec *)NULL, (struct sem_rec *)NULL);
	printf("br B%d\n", numblabels);
	
	return ret;
}


/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y){
	
	/* assign the value of expression y to the lval x */
	struct sem_rec *p, *cast_y, *p2;
	
	
	// Generate an intermediate temp if one of our operands was null, we
	// need to dereference.
	if(*op!='\0' || x==NULL || y==NULL){
	
		/*
		printf("\n\nType X: %d\nType Y: %d\n\n", x->s_mode, y->s_mode);
		printf("X and not T_ADDR: %d\n", x->s_place &~T_ADDR);
		printf("X and not T_ARRAY: %d\n", x->s_place &~T_ARRAY);
		printf("X and not T_ADDR and not T_ARRAY: %d\n", x->s_place &~T_ADDR &~T_ADDR);
		*/
		int realtypex = x->s_mode & ~T_ADDR;
		int realtypey = y->s_mode & ~T_ADDR;
		//printf("TYPE X: %d\n", realtypex);
		//printf("TYPE Y: %d\n", realtypey);
		//printf("%d", realtypex & T_INT);
		//printf("%d", realtypex & T_DOUBLE);

		// Print dereference statement	
		if(1 == realtypex){
			// first needs to be null or it comes out backwards
			p = gen("@", (struct sem_rec *)NULL, x, T_INT);
			
			// Print casting if necessary
			cast_y = cast(y, T_INT);
		}
		else{
			p = gen("@", (struct sem_rec *)NULL, x, T_DOUBLE);
			
			// Print casting if necessary
			cast_y = cast(y, T_DOUBLE);
		}
		
		// Print given operation statements (+ for +=, | for
		// |=, etc)
		p2 = gen(op, p, cast_y, cast_y->s_mode);
		
		// Do the assignment
		return gen("=", x, p2, cast_y->s_mode);

		/*
		p = op1("@", x);

		// Print dereference statement
		if(p->s_mode & T_INT){

			// Print casting if necessary
			cast_y = cast(y, T_INT);
		}
		else{
			// Print casting if necessary
			cast_y = cast(y, T_DOUBLE);
		}

		// Print given operation statements (+ for +=, | for
		// |=, etc)
		p2 = gen(op, p, cast_y, cast_y->s_mode);

		// Do the assignment
		printf("t%d := t%d =%c t%d\n", nexttemp(), x->s_place, (p->s_mode & T_INT ? 'i':'f'), cast_y->s_place);
		*/
	}
	else{
		//type consistency of x and y
			
		cast_y = y;

		int realtypex = x->s_mode & ~T_ADDR;
		int realtypey = y->s_mode & ~T_ADDR;

		/*
		printf("\n\nType X: %d\nType Y: %d\n\n", x->s_mode, y->s_mode);
		printf("X - T_ADDR: %d\n", x->s_place -T_ADDR);
		printf("X - T_ARRAY: %d\n", x->s_place -T_ARRAY);
		printf("X and not T_ADDR and not T_ARRAY: %d\n", x->s_place &~T_ADDR &~T_ADDR);
		printf("X DEREFERENCED: %d\n", realtypex);
		*/

		if((x->s_mode & T_DOUBLE) && !(y->s_mode & T_DOUBLE)){
			//cast y to a double
			//printf("t%d := cvf t%d\n", nexttemp(), y->s_place);
			cast_y = cast(y, T_DOUBLE);
			//node(currtemp(), T_DOUBLE, (struct sem_rec *) NULL,(struct sem_rec *) NULL);
		}
		else if((x->s_mode & T_INT) && !(y->s_mode & T_INT)){
			//convert y to integer
			//printf("t%d := cvi t%d\n", nexttemp(), y->s_place);
			cast_y = cast(y, T_INT);
			//node(currtemp(), T_INT, (struct sem_rec *) NULL, (struct sem_rec *) NULL);
		}

		/*output quad for assignment*/
		if((x->s_mode &~ T_ARRAY)& T_INT){
			printf("t%d := t%d =i t%d\n", nexttemp(), x->s_place, cast_y->s_place);
		}
		else{
			printf("t%d := t%d =f t%d\n", nexttemp(), x->s_place, cast_y->s_place);
		}
	}

	/*create a new node to allow just created temporary to be referenced later */
	return(	node(currtemp(),
		     (x->s_mode&~(T_ARRAY)),
		     (struct sem_rec *)NULL,
		     (struct sem_rec *)NULL)
	);
}


/*
 * startloopscope - start the scope for a loop
 */
void startloopscope(){

	// This is always called for a dowhile, while, or for statement.  Thus
	// we can use this to begin counting loops.  From the grammar, we can
	// see that in general, s will occur before at the beginning of the
	// clause.

	/* For breaks and continues, we need to track either the endpoint or
	 * the beginning of the conditional/clause so we have a point of
	 * reference to jump to.  However, this could happen many times over,
	 * so we need to extract the appropriate line to jump to.
	 *
	 * If we count loops as they are entered, we can chain together
	 * semantic records with the appropriate m and n targets for the given
	 * level of looping.  So long as we clean up at the end, we then
	 * always have a record of the appropriate line to jump to.
	 */
	
	// increment loop count
	numloops++;

	// Create a new node to jump to
	struct sem_rec * curr = node(0, 0, (struct sem_rec *)NULL, (struct sem_rec *)NULL);

	// Track it in our array
	loops[numloops] = curr;
	
	// Enter new scope for symbol table
	enterblock();
}


/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s){
	
	// Prepare a semantic record from the given string.
	struct sem_rec *ret = node(nexttemp(), T_STR, (struct sem_rec *)NULL, (struct sem_rec *)NULL);	

	// Print the intermediate code
	printf("t%d := %s\n", ret->s_place, s);

	return ret;
}


/************* Helper Functions **************/

/*
 * cast - force conversion of datum y to type t
 */
struct sem_rec *cast(struct sem_rec *y, int t){
	
	if(t == T_DOUBLE && y->s_mode != T_DOUBLE){
		return (gen("cv", (struct sem_rec *) NULL, y, t));
	}
	else if(t != T_DOUBLE && y->s_mode == T_DOUBLE){
		return (gen("cv", (struct sem_rec *) NULL, y, t));
	}
	else{
		return (y);
	}
}


/*
 * gen - generate and return quadruple "z := x op y"
 *
 * Would have been very nice to have instructions for this helper function.
 * Not so much about what it does, but what you did and did not intend this to
 * be used for.  The use was kind of inconsistent in the given code, and it
 * might have been better to separate this into several helper functions that
 * each handle one use pattern.
 *
 * As far as I understand it, we can use this one function for:
 * 	args
 * 	returns
 * 	general binary operations
 * 	making soup
 *	certain unary operations
 *	function calls
 *	toasting marshmallows
 *	the assignment of assignment operators
 *	the operator of assignment operators
 */
struct sem_rec *gen(char *op, struct sem_rec *x, struct sem_rec *y, int t){
	
	if(strncmp(op, "arg", 3) != 0 && strncmp(op, "ret", 3) != 0){
		printf("t%d := ", nexttemp());
	}
	if(x != NULL && *op != 'f'){
	   printf("t%d ", x->s_place);
	}
	printf("%s", op);
	if(t & T_DOUBLE && (!(t & T_ADDR) || (*op == '[' && *(op+1) == ']'))) {
		printf("f");
		if(*op == '%'){
			yyerror("cannot %% floating-point values");
		}
	}
	else{
		printf("i");
	}
	if(x != NULL && *op == 'f'){
		printf(" t%d %d", x->s_place, y->s_place);
	}
	else if(y != NULL){
		printf(" t%d", y->s_place);
	}
	printf("\n");
	return (node(currtemp(), t, (struct sem_rec *) NULL, (struct sem_rec *) NULL));
}


void deepcopy(struct sem_rec *src, struct sem_rec* dest){
	dest->s_place = src->s_place;
	dest->s_mode = src->s_mode;
	dest->back.s_link = src->back.s_link;
	dest->s_false = src->s_false;
}
