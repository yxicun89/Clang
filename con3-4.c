%{
#include<stdio.h>
#include<string.h>
#include"gen.c"
#include"ast.c"
#define YYSTYPE double

StmtNodePtr setStmt(StmtNodePtr list,StmtNodePtr stmt);
StmtNodePtr getStmtBottom(StmtNodePtr stmt);

ExprNodePtr setAlist(ExprNodePtr list,ExprNodePtr expr);
void reset(char*id);
SymEntryPtr addGvar(char*id);
void addParam(char*id);
void addLocal(char*id);
void checkParam();
extern int yydebug;
extern SymEntryPtr curfunc;
extern DefNodePtr sourcedefs;
extern SymEntryPtr symtable;
FILE*af;
int cntGlobal=0;
int cntParam=0;
int cntLocal=0;
int hasProto;

%}

%union{
    int ival;
    char*name;
    //StmtNodePtr stmt;
    //DefNodePtr def;
    //SymEntryPtr sym;
    }
%token<dval>EXPR
%token<ival>NUM
%token<name>ID
%token IF ELSE WHILE RETURN
%token TINT

%type<expr>expr
%type<stmt>st_list stmt if_part
%type<sym>decl_gvar
%type<def>program global_def func_def7
%type<alist>alist alist_1

%right ASSIGN
%left LOR
%left LAND
%left BLT BEQ BNE
%left ADD SUB
%left MUL DIV MOD
%left FUNCALL
%right NOT UM

%%

expr
:NUM{$$=makeExpr(OP_CONST,$1,NULL,NULL,NULL);}
|expr LOR expr{$$=makeExpr(OP_LOR,0,NULL,$1,$3);}
|expr LAND expr{$$=makeExpr(OP_LAND,0,NULL,$1,$3);}
|expr BLT expr{$$=makeExpr(OP_BLT,0,NULL,$1,$3);}
|expr BEQ expr{$$=makeExpr(OP_BEQ,0,NULL,$1,$3);}
|expr BNE expr{$$=makeExpr(OP_BNE,0,NULL,$1,$3);}
|expr ADD expr{$$=makeExpr(OP_ADD,0,NULL,$1,$3);}
|expr SUB expr{$$=makeExpr(OP_SUB,0,NULL,$1,$3);}
|SUB  expr%prec UM{$$=makeExpr(OP_UM,0,NULL,$2,NULL);}
| ’(’expr’)’ {$$=$2;}
|ID ASSIGN expr{$$=makeExpr(OP_ASSIGN,0,symLookup($1),$3,NULL);}
|ID’(’alist’)’ {$$=makeExpr(OP_VAR,0,symLookup($1),NULL,NULL);}
;


alist
:/*Empty*/ {$$=NULL;}
|alist_1
;


alist_1
:expr{$$=makeExpr(OP_ALIST,0,NULL,$1,NULL);}
|expr{$$=setAlist($1,NULL)}
;

st_list
: /*Empty rule*/ {$$=NULL;}
|st_list stmt{if(0){StmtNodePtr a=getStmtBottom($1);a->next=$2;$$=$1;}
else{$$=setStmt($1,$2);} }
;


stmt
: ’(’st_list’)’ {$$=NULL;}
|expr’;’{$$=makeStmt(STMT_EXPR,$1,NULL,NULL)}
|if_part/*implicit*/
|if_part  ELSE stmt{StmtNodePtr if_p=$1;if_p->st2=$1;$$=if_p;}
|WHILE’(’expr’)’stmt{$$=makeStmt(STMT_WHILE,$3,$5,NULL);}
|RETURN expr’;’ {$$=makeStmt(STMT_RETURN,$2,NULL,NULL);}
;

if_part
:IF’(’expr’)’stmt{$$=makeStmt(STMT_IF,&)}
;

program
:global_def{sourcedefs=$1;$$=$1;}
|program global_def{$1->next=$2;$$=$2;}
;

global_def
:decl_gvar’;’ {$$=makeDef(DEF_GLOBAL,$1,NULL);}
|f_head’;’ {if(hasProto== 1){
    fprintf(stderr,"error global_def!\n");
    }else{$$=makeDef(PROTOTYPE,curfunc,NULL);}}
    |func_def/*implicit*/
;

func_def
:f_head{fprintf(stdout,"func: %s\n",curfunc->name);}
’{’ {fprintf(stdout, "+++LocalVarList+++\n");}
decl_lvar_list{fprintf(stdout, "+++stmtList+++++++\n");}
st_list{fprintf(stdout, "+++++++++++\n"); } ’}’
{curfunc->nVar=cntLocal;
$$=makeDef(DEF_FUNC,curfunc,$7);fprintf(stdout, "func_end\n");}
;

f_head
:TINT ID’(’{reset($2);}p_list’)’  {checkParam();}
;
p_list
: /*Empty!*/
|p_list_1
;

p_list_1
:decl_par9
|p_list_1’,’decl_par
;

decl_par
:TINT ID{degvar($2);}
;

decl_lvar_list
: /*Empty!*/
|decl_lvar_list decl_lvar’;’
;

decl_lvar
:TINT ID{degvar($2);}
;
decl_gvar
:TINT ID{$$=degvar($2);}
;
%%
void reset(char*id){
    fprintf(stdout,"\nreset: %s\n",id);
    SymEntryPtr found;
    SymEntryPtr added;
    curfunc=NULL;
    
    if((found==symLookup(id)) ==NULL){
        added=symAdd(SYM_FUNC,id,cntGlobal++,0,0,NULL);
        hasProto= 0;
        curfunc=added;
        }else{
            if(found->sort==SYM_VAR&&found->belong==NULL){
                fprintf(stderr, "error!!",found->name);
                }else if(found->sort==SYM_FUNC){
                    DefNodePtr dnp=sourcedefs;
                    while(dnp!=NULL){
                        if(strcmp(dnp->sym->name,id) == 0)
                        break;
                        dnp=dnp->next;
                        }
                        if(dnp!=NULL&&dnp->sort==DEF_FUNC){

                        }else if(dnp!=NULL&&dnp->sort==PROTOTYPE{
                            hasProto= 1;
                        }
                }
        }
}
void checkParam(){
    fprintf(stdout, "checkParam()\n");
    if(hasProto){
        if(curfunc->nParam!=cntParam){
            fprintf(stderr, "Error checkParam!!\n");
        }
    }else{
        curfunc->nParam=cntParam;
    }
}

void degvar(char*id){
    fprintf(stdout, "degvar%s\n",id);
    if(symLookup(id) ==NULL){
        symAdd(STM_PARAM,id,cntParam++,0,0,curfunc);
        }else{
            fprintf(stderr, "degvar Error!!\n");
        }
}

StmtNodePtr getStmtBottom(StmtNodePtr stmt){
    fprintf(stdout, "getStmtBottom()\n");
    if(stmt==NULL)
      return NULL;
    StmtNodePtr b=stmt;
    while(b->next!=NULL){
        b=b->next;
    }
        return b;
}

StmtNodePtr setStmt(StmtNodePtr list,StmtNodePtr stmt){
    fprintf(stdout,"setStmt()\n");
    StmtNodePtr btm=list;
    if(list==NULL){
        return stmt;
        }else{
            while(btm->next!=NULL)
            btm=btm->next;
            btm->next=stmt
        }
}

ExprNodePtr setAlist(ExprNodePtr list,ExprNodePtr expr){
    fprintf(stdout,"setAlist();\n");
    ExprNodePtr btm=list;
    if(btm==NULL)
    areturn makeExpr(OP_ALIST,0,NULL,expr,NULL);
    else{
        while(btm->sub2!=NULL){
            btm=btm->btm2;
        }
            btm->sub2=makeExpr(OP_ALIST,0,NULL,expr,NULL);
    }
            return list;
}
            
int yyerror(char*msg){
                fprintf(stderr,"yyerror(): \"%s\".\n",msg);
                return0;
                *ExprNodePtr setAlist(ExprNodePtr list,ExprNodePtr expr){
                    fprintf(stdout, "setAlist()\n");
                    ExprNodePtr btm=list;
                    if(btm==NULL){
                    return makeExpr(OP_ALIST,0,NULL,expr,NULL);
                    }else{
                        while(btm->sub2!=NULL){
                        btm=btm->sub2;257btm->sub2=makeExpr(OP_ALIST,0,NULL,expr,NULL);
                        }
                    }
                }
                return list;
}