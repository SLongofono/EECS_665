# include <stdio.h>
# include <stdlib.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"


/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k)
{  }

/*
 * bgnstmt - encountered the beginning of a statement
 */
void bgnstmt()
{  }

/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args)
{
  	return ((struct sem_rec *) NULL);
}

/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2)
{
	 return ((struct sem_rec *) NULL);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e)
{
	 return ((struct sem_rec *) NULL);
}

/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e)
{
	 return ((struct sem_rec *) NULL);
}

/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2)
{
	 return ((struct sem_rec *) NULL);
}

/*
 * con - constant reference in an expression
 */
struct sem_rec *con(char *x)
{
	 return ((struct sem_rec *) NULL);
}

/*
 * dobreak - break statement
 */
void dobreak()
{  }

/*
 * docontinue - continue statement
 */
void docontinue()
{  }

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3)
{  }

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1, int m3, struct sem_rec *n2, int m4)
{  }

/*
 * dogoto - goto statement
 */
void dogoto(char *id)
{  }

/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2)
{  }

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n, int m2, int m3)
{  }

/*
 * doret - return statement
 */
void doret(struct sem_rec *e)
{  }

/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n, int m3)
{  }

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m)
{  }

/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e)
{
  	return ((struct sem_rec *) NULL);
}

/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
	/*
	 * For some strange reason, if we do the enterblock() call here, the
	 * dumping scope gets printed at the wrong time (according to the 
	 * given correct output).  I think this is why:
	 *
	 * fhead: fname fargs '{' dcls { fhead($1) }
	 *
	 * Since the translation scheme statement gets executed last, if we
	 * enter the block, here, we will erroneaously open and close a block
	 * after the function has been parsed.  The desired behavior is that
	 * the function and arguments scope are opened before any statements
	 * within the statement scope.
	 *
	 * By calling enterblock in fname, we can be sure that its scope block
	 * is opened, then the args scope block, and finally fhead can resolve
	 * so that statements can be resolved in the func rule.
	 *
	 * TL;DR Nothing to do here...
	 */
}

/*
 * blockdcl - begining of new block
 */
void blockdcl()
{
	/*
	 * We have a new block.  Blocks are anonymous, and have no value.
	 * Thus we can just call enter_block() and move on.
	 */
	enterblock();
}

/*
 * btail - end of block
 */
void btail()
{
	/*
	 * We have the end of a block, leave the current level and wrap up
	 */
	leaveblock();
}

/*
 * fname - function declaration
 */
struct id_entry *fname(int t, char *id)
{
	/*
	 * We have a function declaration, make an entry for it...
	 *
	 * Since the author does not believe in documentation or meaningful
	 * variable names, we dig into the Yacc file:
	 *
	 * int t: the return type of the function, codified as:
	 * 	char -> 1
	 * 	float -> 4
	 * 	double -> 4
	 * 	int -> 1
	 *
	 * char * id: the name string for the function parsed by Yacc
	 *
	 *  
	 */
	
	// Check if this id already exists at the global scope level
	struct id_entry *ret = NULL;
		
	if(NULL != lookup(id, LOCAL)){
		yyerror("function already declared");
	}
	else{
		ret = install(id, LOCAL);
		ret->i_type = t;
		ret->i_scope = LOCAL;
		ret->i_defined = 1;
	}
	enterblock();
	return ret;
}

/*
 * ftail - end of function body
 */
void ftail()
{
	/*
	 * We have reached the end of a function body, leave the current scope
	 */
	leaveblock();
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
	struct id_entry *p;

	if ((p = lookup(x, 0)) == NULL) {
		yyerror("undeclared identifier");
		printf("ID %s installed\n", x);
		p = install(x, -1);
		p->i_type = T_INT;
		p->i_scope = LOCAL;
		p->i_defined = 1;
	}

		return ((struct sem_rec *) NULL);
}

/*
 * index1 - subscript
 */
struct sem_rec *index1(struct sem_rec *x, struct sem_rec *i)
{
  	return ((struct sem_rec *) NULL);
}

/*
 * labeldcl - process a label declaration
 */
void labeldcl(char *id)
{  }

/*
 * m - generate label and return next temporary number
 */
int m()
{
  	return (0);
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
  	return ((struct sem_rec *) NULL);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{
  	return ((struct sem_rec *) NULL);
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y)
{
  	return ((struct sem_rec *) NULL);
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(char *op, struct sem_rec *x, struct sem_rec *y)
{
  	return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y)
{
  	return ((struct sem_rec *) NULL);
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y)
{
	 return ((struct sem_rec *) NULL);
}

/*
 * startloopscope - start the scope for a loop
 */
void startloopscope()
{  }

/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s)
{
	 return ((struct sem_rec *) NULL);
}
