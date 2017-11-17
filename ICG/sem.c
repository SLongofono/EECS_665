# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"
#include <string.h>
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

/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k){

	// Traverse the list, updating the place as we go.
	//
	// Note: for any given call, we can't know a priori whether we are
	// updating the true or the false list, only that we need to update
	// all the entries to the given label number.
	//
	// To handle this, the record passed in should have been merged and
	// thus collapsed into a single list.  Not every record will have both
	// defined, and to keep things simple, we use the convention of
	// traversing only through s_link.
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
	fprintf(stderr, "sem: call not implemented\n");
	return ((struct sem_rec *) NULL);
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
		t1 = gen("!=", e, cast(con("0"), e->s_mode), e->s_mode);
		printf("bt t%d B%d\n", t1->s_place, ++numblabels);
		printf("br B%d\n", ++numblabels);
		return (node(0, 0, node(numblabels-1, 0, (struct sem_rec *) NULL, (struct sem_rec *) NULL), node(numblabels, 0, (struct sem_rec *) NULL, (struct sem_rec *) NULL)));
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
	fprintf(stderr, "sem: dobreak not implemented\n");
}


/*
 * docontinue - continue statement
 */
void docontinue(){
	fprintf(stderr, "sem: docontinue not implemented\n");
}

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3){
	fprintf(stderr, "sem: dodo not implemented\n");
}

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1, int m3,
	   struct sem_rec *n2, int m4){
	fprintf(stderr, "sem: dofor not implemented\n");
}

/*
 * dogoto - goto statement
 */
void dogoto(char *id){
	fprintf(stderr, "sem: dogoto not implemented\n");
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

	// Pass firs record as null to catch return case properly
	gen("ret", (struct sem_rec *)NULL, e,  e->s_mode);
	/*
	if(NULL != e){
		if(e->s_mode == T_INT){
			printf("reti t%d\n", e->s_place);	
		}
		else{
			printf("retf t%d\n", e->s_place);	
		}

	}
	else{
		printf("reti\n");
	}
	*/
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
}

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m){
	for(int i = 0; i<m; ++i){
		leaveblock();
	}
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

	// Create symbol table entry for the given function using the given
	// type t, the name id, and the width.  The width specifies the size
	// of the return
	int width;
	switch(t){
		case T_INT:
			width = 4;
			break;
		default:
			// Everything else is system address length, including
			// doubles
			width = 8;
	}

	// Print out the intermediate code
	printf("func %s\n", id);
	
	// Create a new scope for the function
	enterblock();

	return dclr(id, t, width);
}


/*
 * ftail - end of function body
 */
void ftail(){
	
	// Print intermediate code stmt
	printf("fend\n");
	
	// Leave function scope
	leaveblock();
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
	return (node(currtemp(), p->i_type|T_ADDR, (struct sem_rec *) NULL,
	             (struct sem_rec *) NULL));
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
	return node(numblabels, T_INT, (struct sem_rec *)NULL, (struct sem_rec *)NULL);
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
	if(NULL != x){
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
	if(NULL != x){
		return gen(op,x,y,y->s_mode);
	}
	else{
		return ((struct sem_rec *) NULL);
	}
}


/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y){
	struct sem_rec *ret = gen(op, x, cast(y, x->s_mode), x->s_mode);

	// Need to generate the branches to be taken for this
	// condition per the grammar 6.43
	numblabels++;
	printf("bt t%d B%d\n", currtemp(), numblabels);
	numblabels++;
	printf("br B%d\n", numblabels);
	ret->back.s_true = node(numblabels-1, x->s_mode, (struct sem_rec *)NULL, (struct sem_rec *)NULL);
	ret->s_false = node(numblabels, x->s_mode, (struct sem_rec *)NULL, (struct sem_rec *)NULL);

	return ret;

}


/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y){
	/* assign the value of expression y to the lval x */
	struct sem_rec *p, *cast_y;

	if(*op!='\0' || x==NULL || y==NULL){
		return gen(op, x, cast(y, x->s_mode), x->s_mode);
	}

	/* if for type consistency of x and y */
	cast_y = y;
	if((x->s_mode & T_DOUBLE) && !(y->s_mode & T_DOUBLE)){
	
		/*cast y to a double*/
		printf("t%d := cvf t%d\n", nexttemp(), y->s_place);
		cast_y = node(currtemp(), T_DOUBLE, (struct sem_rec *) NULL, (struct sem_rec *) NULL);
	}
	else if((x->s_mode & T_INT) && !(y->s_mode & T_INT)){

		/*convert y to integer*/
		printf("t%d := cvi t%d\n", nexttemp(), y->s_place);
		cast_y = node(currtemp(), T_INT, (struct sem_rec *) NULL, (struct sem_rec *) NULL);
		printf("t%d := t%d\n", nexttemp(), y->s_place);
	}


	return (node(currtemp(), (x->s_mode&~(T_ARRAY)), (struct sem_rec *)NULL, (struct sem_rec *)NULL));
}


/*
 * startloopscope - start the scope for a loop
 */
void startloopscope(){
	enterblock();
}


/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s){
	// Prepare a semantic record from the given string.
	struct sem_rec *ret = node(nexttemp(), T_STR, (struct sem_rec *)NULL, (struct sem_rec *)NULL);	

	// Print the intermediate code
	printf("t%d := \"%s\"\n", ret->s_place, s);

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
