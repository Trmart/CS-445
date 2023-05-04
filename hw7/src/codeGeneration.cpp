/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW7
Dr. Wilder
DUE: 5/5/2023

FILE: codeGeneration.cpp
DESC:  Code generation functions implementation
*/

#include <string.h>
#include "codeGeneration.h"
#include "emitCode.h"



#define MAXCHILDREN 3

using namespace std;

extern int globalOffset;
extern int localOffset;

FILE *code;

extern SymbolTable symbolTable;

int tempOffset = - 2;
bool stFlag = false;
bool isUnary = false;
int cpdSize = 0;
int tmpIdx;
bool opKarr;
int thenLoc = 0, breakLoc = 0;
int nestThen = 0;
bool mpCall = false;
bool nestCall = false;
bool nestAsgn = false;
int doingFor = false;
bool inIF = false;


void generateCode(TreeNode* node, char* inputFile)
{

    code = fopen(inputFile, "w");

    emitComment((char*)"C- compiler version C-S23");
    emitComment((char*)"Built: 4-17 - 5-05");
    emitComment((char*)"Author: Taylor Martin");
    emitComment((char*)"File compiled: ", inputFile);
    emitComment((char*)"");
    emitIO(node);
    emitStart(node);
    emitInit(node);
    fclose(code);

}

//Emit info about compiler at beginning
void emitAbout(char* inputFile)
{

    emitComment((char*)"C- compiler version C-S23");
    emitComment((char*)"Built: 4-17 - 5-05");
    emitComment((char*)"Author: Taylor Martin");
    emitComment((char*)"File compiled: ", inputFile);
    emitSkip(1);
}

void emitInput(TreeNode* node)
{
    while(node->sibling != nullptr)
    {
        //t = node->sibling;
        emitStart(node);
    }
}

//recursive function for emitting, mimic syntax tree set up
void emitStart(TreeNode* node)
{
    if(node == nullptr)
    {
        return;
    }
    else
    {
        switch(node->nodekind)
        {

            case DeclK:
                    {
                        emitDecl(node);
                    }
                    break;

            case StmtK:
                    {
                        emitStmt(node);
                    }
                    break;

            case ExpK:
                    {
                        emitExp(node);
                    }
                    break;
        }
    }

    if(node->sibling != nullptr && !mpCall)
    {
        emitStart(node->sibling);
    }
}

//emit code for nodekind Decl
void emitDecl(TreeNode *node)
{

    switch(node->subkind.decl)
    {

        case ParamK:
                {
                    emitParam(node);
                }
                break;


        case VarK:
                {
                    emitVar(node);
                }
                break;

        case FuncK:
                {
                    emitFunc(node);
                }
                break;
    }

}

void emitVar(TreeNode* node)
{
            //printf("Here: %s, %d\n", node->attr.name, node->linenum);

            if((!node->isGlobal && !node->isStatic))
            {

                //check for arrays
                if(node->isArray)
                {

                    emitRM((char*)"LDC", 3, node->memorySize - 1, 6, (char*)"load array size 124", (char*)node->attr.name);
                    emitRM((char*)"ST", 3, node->memoryOffset + 1, 1, (char*)"save array size", (char*)node->attr.name);

                    //check for strings
                    if(node->child[0] != nullptr)
                    {
                        emitStart(node->child[0]);
                        emitRM((char *)"LDA", 3, node->child[0]->memoryOffset, 0, (char *)"Load address of char array");
                        emitRM((char *)"LDA", 4, node->memoryOffset, 1, (char *)"address of lhs");

                        emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
                        emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");

                        emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");

                        emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
                    }

                }
                else
                {
                    
                    //check initiailzed variable
                    if(node->child[0] != nullptr)
                    {

                        if(node->isArray)
                        {
                            emitRM((char*)"ST", 3, node->memoryOffset + 1, 1, (char*)"save array size", (char*)node->attr.name);
                        }
                        else
                        {
                            emitStart(node->child[0]);
                            emitRM((char*)"ST", 3, node->memoryOffset, 1, (char*)"store variable 136", (char*)node->attr.name);
                        }
                    }
                }
            }
}

void emitParam(TreeNode* node)
{
    //loop through children
    for(int i = 0; i < MAXCHILDREN; i++)
    {
        emitStart(node->child[i]);
    }
}

void emitFunc(TreeNode* node)
{
    node->emitCodeLine = emitSkip(0);

    TreeNode* cntSiblings;
    int pcount;
    int tmpIdx = tempOffset;

    cntSiblings = node->child[0];

    if(cntSiblings != nullptr)
    {

        for(pcount = 0; cntSiblings != nullptr; pcount++)
        {
            cntSiblings = cntSiblings->sibling;
        }

        if(!(node->child[1]->nodekind == StmtK && node->child[1]->subkind.stmt == CompoundK))
        {

            tempOffset -= pcount + 2;
            emitComment((char*)"TOFF:", tempOffset);
        }
    }

    node->emitLocation = emitSkip(0) - 1;

    emitComment((char *)("FUNCTION"), (char *) node->attr.name);
    emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");

    for(int i = 0; i < MAXCHILDREN; i++)
    {
        
        if(node->child[i] != nullptr)
        {
            emitStart(node->child[i]);
        }
    }

    emitComment((char *)("Add standard closing in case there is no return statement"));
    emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
    emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
    emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
    emitRM((char *)"JMP", 7, 0, 3,(char *)("Return"));
    emitComment((char *)("END FUNCTION"), (char *) node->attr.name);

    //tempOffset = 0;
    tempOffset = tmpIdx;
    emitComment((char*)"TOFF:", tempOffset);
}

void emitStmt(TreeNode* node)
{

    int whileLoc = 0, tmpBloc = 0, whileSkp = 0, ldaLoc = 0, forCdrn = 0, elseLoc = 0;
    int forOff = 0, forLoc = 0, forSkp = 0;

    switch(node->subkind.stmt)
    {

        case IfK:
            {
                emitIf(node, elseLoc);
            }
            break; 

        case WhileK:
                {
                    emitWhile(node, whileLoc, tmpBloc, whileSkp, ldaLoc);
                }
                break; 
        
        case ForK:
                {
                    emitFor(node, forOff, forLoc, forSkp);
                }
                break;

        case RangeK:
                {
                    emitRange(node);
                }
                break;

        case ReturnK:
                {
                    emitReturn(node);
                }
                break;

        case BreakK:
                {
                    emitBreak(node);
                }
                break;

        case CompoundK:
                    {
                        emitCompound(node);
                    }
                    break;

    }
}

void emitIf(TreeNode* node, int elseLoc)
{
    //start if statement
    emitComment((char*)("IF"));
    stFlag = false;
    inIF = true;

    //analyze child0
    emitStart(node->child[0]);
    emitComment((char*)("THEN"));

    //set else location and then location
    elseLoc = 0;
    thenLoc = emitSkip(1);
    if(node->child[1]->subkind.stmt == IfK)
    {
        nestThen = thenLoc--;
    }            

    //start analyzing child1
    emitStart(node->child[1]);

    //if there is an else statement updated location
    if(node->child[2] != nullptr)
    {
        elseLoc = emitSkip(1);
    }

    if(node->child[1]->subkind.stmt != IfK)
    {
        //go back to then section
        //nestThen -= 2;
        backPatchAJumpToHere((char*)"JZR", 3, thenLoc, (char *)("Jump around the THEN if false [backpatch]"));
    }
    else
    {
        
        backPatchAJumpToHere((char*)"JZR", 3, nestThen, (char *)("Jump around the THEN if false [backpatch]"));
    }

    //if there is an else statement, analyze child2 jump the else
    if(node->child[2] != nullptr)
    {
        emitComment((char*)"ELSE");
        emitStart(node->child[2]);
        backPatchAJumpToHere((char*)"JMP", 7, elseLoc, (char *)("Jump around the ELSE [backpatch]"));
    }

    //done
    emitComment((char*)"END IF");
    inIF = false;

}

void emitWhile(TreeNode* node, int whileLoc, int tmpBloc, int whileSkp, int ldaLoc)
{
    whileLoc = emitSkip(0);
    stFlag = false;
    emitComment((char*)("WHILE"));
    
    emitStart(node->child[0]);
    tmpBloc = breakLoc;
    breakLoc = emitSkip(0);
    emitRM((char *)"JNZ", 3, 1, 7, (char *)("Jump to while part"));
    emitComment((char*)("DO"));
    whileSkp = emitSkip(1);
    
    emitStart(node->child[1]);
    emitRM((char*)"JMP", 7, whileLoc - emitSkip(0) - 1, 7, (char*)("go to the beginning of the loop"));
    ldaLoc = emitSkip(0);
    backPatchAJumpToHere(whileSkp, (char *)("Jump past loop [backpatch]"));
    breakLoc = tmpBloc;
    emitNewLoc(ldaLoc);
    emitComment((char*)("END WHILE"));
}

void emitReturn(TreeNode* node)
{
    emitComment((char*)("RETURN"));
    stFlag = false;
    emitStart(node->child[0]);

    if(node->child[0] != nullptr)
    {
        emitRM((char *)"LDA", 2, 0, 3, (char *)("Copy result to ret register"));
    }
    emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
    emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
    emitRM((char *)"JMP", 7, 0, 3, (char *)("Return"));
}

void emitBreak(TreeNode* node)
{
    emitComment((char*)("BREAK"));
    emitRM((char *)"JMP", 7, breakLoc - emitSkip(0), 7, (char *)("break"));
}

void emitFor(TreeNode* node, int forOff, int forLoc, int forSkp)
{
    tempOffset -= 3;
    doingFor = true;
    emitComment((char*)("TOFF: "), tempOffset);

    emitComment((char*)("FOR"));

    forOff = tempOffset;

    //emit index var
    emitStart(node->child[0]);

    //emit RangeK section
    emitStart(node->child[1]);

    forLoc = emitSkip(0);

    //Check if the range has been exceeded.
    emitRM((char *)"LD", 4, forOff + 3, 1, (char *)"loop index");
    emitRM((char *)"LD", 5, forOff + 2, 1, (char *)"stop value");
    emitRM((char *)"LD", 3, forOff + 1, 1, (char *)"step value");
    emitRO((char *)"SLT", 3, 4, 5, (char *)"Op <");
    emitRM((char *)"JNZ", 3, 1, 7, (char *)"Jump to loop body");
    
    forSkp = emitSkip(1);

    //go through compound section for for loop
    emitStart(node->child[2]);

    emitRM((char *)"LD", 3, forOff + 3, 1, (char *)"Load index");
    emitRM((char *)"LD", 5, forOff + 1, 1, (char *)"Load step");

    emitRO((char *)"ADD", 3, 3, 5, (char *)"increment");

    emitRM((char *)"ST", 3, forOff + 3, 1, (char *)"store back to index");
    emitGotoAbs(forLoc, (char *)"go to beginning of loop");
    backPatchAJumpToHere(forSkp, (char *)"Jump past loop [backpatch]");

    emitComment((char*)("END FOR"));
    doingFor = false;
}

void emitRange(TreeNode* node)
{
    //get first part of range
    emitStart(node->child[0]);
    emitRM((char *)"ST", 3, tempOffset + 3, 1, (char *)"save starting value in index variable");

    //get second part of range
    emitStart(node->child[1]);
    emitRM((char *)"ST", 3, tempOffset + 2, 1, (char *)"save stop value");

    //check if there is a 3rd child in the range
    //go through 3rd child if so
    if (node->child[2] != NULL)
    {
        emitStart(node->child[2]);
        emitRM((char *)"ST", 3, tempOffset + 1, 1, (char *)"save step value");
    }
    //else default increment and save current step.
    else
    {
        emitRM((char *)"LDC", 3, 1, 6, (char *)"default increment by 1");
        emitRM((char *)"ST", 3, tempOffset + 1, 1, (char *)"save step value");
    }
}  

void emitCompound(TreeNode* node)
{
    cpdSize = tempOffset;
    emitComment((char*)("COMPOUND"));
    if(!doingFor){
        tempOffset = node->memorySize;
    }
    emitComment((char*)"TOFF: ", tempOffset);
    for(int i = 0; i < MAXCHILDREN; i++)
    {
        
        //maybe only t here instead of node->child[i]?
        if(node != NULL){
            emitStart(node->child[i]);
        }
    }

    emitComment((char*)("Compound Body"));
    tempOffset = cpdSize;
    emitComment((char*)"TOFF: ", tempOffset);

    
    emitComment((char*)("END COMPOUND"));
}

void emitExp(TreeNode *node)
{

    //shorthands for checking child 0 and child1 in AssignK and OpK
    TreeNode* lhs;
    TreeNode* rhs;
    TreeNode* callLookup;

    //setup leftSide and rightSide of AssignKs and OpKs
    if(node->child[0] != nullptr)
    {
        lhs = node->child[0];
    }
    else
    {
        lhs = nullptr;
    }
    if(node->child[1] != nullptr)
    {

        rhs = node->child[1];
    }
    else
    {
        rhs = nullptr;
    }

    switch(node->subkind.exp)
    {

        //Look up assignment op
        //TreeNode* askOp;

        case AssignK:
                {
                    emitAssign(node, lhs, rhs);
                }
                break; 

        case OpK:
                {
                    emitOp(node, lhs, rhs);
                }
                break; 

        case ConstantK:
                {
                    emitConstant(node);
                }
                break;

        case IdK:
                {
                    emitId(node);
                }
                break;

        case CallK:
                {
                    emitCall(node, callLookup);
                }
                break;
    }
}

void emitAssign(TreeNode* node, TreeNode* lhs, TreeNode* rhs)
{
     //int tmpIdx;

    emitComment((char*)("ASSIGNMENT EXPRESSION"));

    //tempOffset--;

    //askOp = (TreeNode*)symbolTable.lookup(node->attr.name);

    //check for standard assignment -- like syntaxTree
    if(!strcmp(node->attr.name, "<="))
    {

        //check for arrays
        if(!strcmp(node->child[0]->attr.name, "["))
        {

            /*if(leftSide->child[1]->subkind.exp == IdK){
                emitRM((char *)"LD", 3, leftSide->child[1]->mOffset, 1, (char *)("1 load variable 373"), leftSide->child[1]->attr.name);
            }
            else{*/
            /*if(leftSide->child[1]->subkind.exp == IdK){
                printf("Here: %s %d\n", leftSide->child[1]->attr.name, node->linenum);
            }
            if(leftSide->child[0]->subkind.exp != ConstantK){
                printf("Here RS %s %d\n", leftSide->child[0]->attr.name, node->linenum);
            }*/
            emitStart(lhs->child[1]);
            //}
            
            emitRM((char *)"ST", 3, tempOffset, 1, (char *)("Push index 373"));
            tempOffset--;
            emitComment((char*)"TOFF:", tempOffset);

            if(rhs->subkind.exp == AssignK)
            {
                //printf("Here %s %d", rightSide->attr.name, node->linenum);
                if(!strcmp(rhs->attr.name, "<="))
                {
                    nestAsgn = true;
                }
            }
            emitStart(rhs);
            
            tempOffset++;
            emitComment((char*)"TOFF:", tempOffset);
            emitRM((char *)"LD", 4, tempOffset, 1,(char *)("Pop index")); 

            if(lhs->child[0]->memoryType == Global || lhs->child[0]->memoryType == LocalStatic)
            {

                emitRM((char *)"LDA", 5, lhs->child[0]->memoryOffset, 0, (char *)("Load address of base of array 383"), (char *)lhs->child[0]->attr.name);
            }
            else
            {
                if(node->child[1]->child[1] != nullptr)
                {
                    emitRM((char *)"LD", 5, lhs->child[0]->memoryOffset, 1, (char *)("Load address of base of array 493"), (char *)lhs->child[0]->attr.name);

                }
                else if(nestAsgn){
                    emitRM((char *)"LD", 5, lhs->child[0]->memoryOffset, 1, (char *)("Load address of base of array 497"), (char *)lhs->child[0]->attr.name);
                }
                //might need to remove
                else if(node->child[0]->child[1]->subkind.exp == IdK && node->child[1]->subkind.exp == ConstantK && inIF)
                {
                    emitRM((char *)"LD", 5, lhs->child[0]->memoryOffset, 1, (char *)("Load address of base of array 500"), (char *)lhs->child[0]->attr.name);
                }
                
                else
                {
                    emitRM((char *)"LDA", 5, lhs->child[0]->memoryOffset, 1, (char *)("Load address of base of array 390"), (char *)lhs->child[0]->attr.name);
                }
            }
            emitRO((char *)"SUB", 5, 5, 4, (char *)("Compute offset of value"));
            emitRM((char *)"ST", 3, 0, 5, (char *)("Store variable"), (char *)lhs->child[0]->attr.name);
            nestAsgn = false;
        }
        else if(lhs->isArray && rhs->isArray)
        {

            if(lhs->expType == Char && rhs->expType == Char)
            {
                emitRM((char *)"LDA", 3, rhs->memoryOffset, 1, (char *)"Load address of char array", rhs->attr.name);
                emitRM((char *)"LDA", 4, lhs->memoryOffset, 1, (char *)"address of lhs");

                emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
                emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");

                emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");

                emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
            }
        }
        //having issues in IdK with localStatics, writing a manual check 
        //here to manually load the right side
        else if(lhs->memoryType == LocalStatic && rhs->memoryType == LocalStatic)
        {
            emitRM((char *)"LD", 3, node->child[1]->memoryOffset, 0, (char *)("1 Load variable 797"), node->child[1]->attr.name);
            stFlag = true;
            isUnary = true;
            emitStart(lhs);

        }
        //not an array
        else
        {
            emitStart(rhs);
            stFlag = true;
            isUnary = true;
            emitStart(lhs);
            
        }
    }

    //check for ++ --
    else if(rhs == nullptr)
    {

        stFlag = false;
        isUnary = true;

        emitStart(lhs);

        if(!strcmp(lhs->attr.name, "[")){

            lhs = lhs->child[0];
            opKarr = true;
        }

        if(!strcmp(node->attr.name, "++"))
        {
            emitRM((char *)"LDA", 3, 1, 3, (char *)("increment value of"), (char *)lhs->attr.name);
        }
        else if(!strcmp(node->attr.name, "--"))
        {
            emitRM((char *)"LDA", 3, -1, 3, (char *)("decrement value of"), (char *)lhs->attr.name);
        }

        if(opKarr)
        {
            emitRM((char *)"ST", 3, 0, 5,(char *)("Store variable"), (char *)lhs->attr.name); 
        }
        else
        {
            emitRM((char *)"ST", 3, lhs->memoryOffset, 1,(char *)("Store variable"), (char *)lhs->attr.name);
        }
        
        lhs = node->child[0];
    }

    else
    {

        //check for array, need to do unique stuff
        //for an array version
        //load address of base of array will probably need global checks
        if(!strcmp(lhs->attr.name, "["))
        {

            emitStart(lhs->child[1]);
            emitRM((char *)"ST", 3, tempOffset, 1, (char *)("Push index 446"));

            tempOffset--;
            emitComment((char*)"TOFF:", tempOffset);

            //array index to array index assignment
            if(rhs->child[1] != nullptr)
            {
                emitRM((char *)"LDA", 3, rhs->child[0]->memoryOffset, 0, (char *)("Load address of base of array 446"), (char *)rhs->child[0]->attr.name);
                emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push left side");
                emitStart(rhs->child[1]);
                emitRM((char *)"LD", 4, tempOffset, 1, (char *)"Pop left into ac1");
                emitStart(rhs->child[0]);
                emitRO((char *)"SUB", 3, 4, 3, (char *)"Compute location from index");
                emitRM((char *)"LD", 3, 0, 3, (char *)"Load array element");

                tempOffset++;
                emitComment((char*)"TOFF:", tempOffset);

                emitRM((char *)"LD", 4, tempOffset, 1, (char *)("Pop index"));
                emitRM((char *)"LDA", 5, lhs->child[0]->memoryOffset, 0, (char *)("Load address of base of array 458"), (char *)lhs->child[0]->attr.name);
                emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");
                emitRM((char *)"LD", 4, 0, 5, (char *) "Load LHS variable 499");
            }
            else
            {
                emitStart(rhs);
                tempOffset++;
                emitComment((char*)"TOFF:", tempOffset);
                emitRM((char *)"LD", 4, tempOffset, 1, (char *)"Pop index");
                emitRM((char *)"LD", 5, lhs->child[0]->memoryOffset, 1, (char *)("Load address of base of array 458"), (char *)lhs->child[0]->attr.name);
                emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");
                emitRM((char *)"LD", 4, 0, 5, (char *) "Load LHS variable 508");
            }

            
            
            if(!strcmp(node->attr.name, "+="))
            {
                emitRO((char *)"ADD", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
            else if(!strcmp(node->attr.name, "-="))
            {
                emitRO((char *)"SUB", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
            else if(!strcmp(node->attr.name, "*="))
            {
                emitRO((char *)"MUL", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
            else if(!strcmp(node->attr.name, "/="))
            {
                emitRO((char *)"DIV", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
            //store
            if(lhs->child[0] != nullptr)
            {
                emitRM((char *)"ST", 3, lhs->memoryOffset, 5, (char *)("Store variable"),(char *)lhs->child[0]->attr.name);
            }
            else
            {
                emitRM((char *)"ST", 3, lhs->memoryOffset, 5, (char *)("Store variable"),(char *)lhs->attr.name);
            }
            
        }
        else
        {

            stFlag = false;
            emitStart(rhs);
            isUnary = false;
            emitStart(lhs);

            //check for each other assignment operator
            if(!strcmp(node->attr.name, "+="))
            {
                emitRM((char *)"LD", 4, lhs->memoryOffset, 0, (char *) "Load LHS var");
                emitRO((char *)"ADD", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
            else if(!strcmp(node->attr.name, "-="))
            {
                emitRM((char *)"LD", 4, lhs->memoryOffset, 0, (char *) "Load LHS var");
                emitRO((char *)"SUB", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
            else if(!strcmp(node->attr.name, "*="))
            {
                emitRM((char *)"LD", 4, lhs->memoryOffset, 0, (char *) "Load LHS var");
                emitRO((char *)"MUL", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
            else if(!strcmp(node->attr.name, "/="))
            {
                emitRM((char *)"LD", 4, lhs->memoryOffset, 0, (char *) "Load LHS var");
                emitRO((char *)"DIV", 3, 4, 3, (char *)("Op"), (char *)node->attr.name);
            }
        
        
            //check mem types
            if(lhs->memoryType == Global || lhs->memoryType == LocalStatic)
            {
                emitRM((char *)"ST", 3, lhs->memoryOffset, 0, (char *)("Store variable"), (char *)lhs->attr.name);
            }
            else
            {
                emitRM((char *)"ST", 3, lhs->memoryOffset, 1, (char *)("Store variable"), (char *)lhs->attr.name);
            }
            
            //reset unary flag
            isUnary = true;
        }
    }
}

void emitOp(TreeNode* node, TreeNode* lhs, TreeNode* rhs)
{
    emitComment((char*)("OP EXPRESSION"));
            

    //Check Unary ops
    if(rhs == nullptr)
    {

        emitStart(node->child[0]);

        if(!strcmp(node->attr.name, "-"))
        {

            emitRO((char *)"NEG", 3, 3, 3, (char *)("Op unary -"), (char *)node->attr.name);
        }

        else if(!strcmp(node->attr.name, "*"))
        {

            if(node->child[0]->memoryType == Global || node->child[0]->memoryType == LocalStatic)
            {

                emitRM((char *)"LDA", 3, lhs->memoryOffset, 0, (char *)("Load address of base of array 540"), (char *)lhs->attr.name);
            }
            else if(node->child[0]->memoryType == Parameter)
            {
                emitRM((char *)"LD", 3, lhs->memoryOffset, 1, (char *)("Load address of base of array 543"), (char *)lhs->attr.name);
            }
            else
            {
                emitRM((char *)"LDA", 3, lhs->memoryOffset, 1, (char *)("Load address of base of array 546"), (char *)lhs->attr.name);
            }
            
            emitRM((char *)"LD", 3, 1, 3, (char *)("Load array size 669"));
        }

        else if(!strcmp(node->attr.name, "?"))
        {
            emitRO((char *)"RND", 3, 3, 6, (char *)("Op unary"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "NOT") || !strcmp(node->attr.name, "not"))
        {

            emitRM((char *)"LDC", 4, 1, 6, (char *)("Load 1"));
            emitRO((char *)"XOR", 3, 3, 4, (char *)("Op XOR to get logical not"));
        }
    }
    //binary checks
    else
    {

        
        stFlag = false;

        //move past index in use
        //tmpIdx--; 

        //attempt to fix issues with arrays so far...but it
        //seems to be causing problems with c0f.c-
        if(!strcmp(node->attr.name, "["))
        {

            //tmpIdx = tempOffset;
            if(isUnary == false || lhs->expType == Char)
            {
                if(lhs->isArray)
                {

                    if(lhs->memoryType == Global || lhs->memoryType == LocalStatic)
                    {
                        emitRM((char *)"LDA", 3, lhs->memoryOffset, 0, (char *)"1 Load address of base of array 578", (char*)lhs->attr.name);
                    }
                    //might need to add this later
                    
                    else if(lhs->memoryType == Parameter)
                    {
                        emitRM((char *)"LD", 3, lhs->memoryOffset, 1, (char *)"2 Load address of base of array 583", (char*)lhs->attr.name);
                    }
                    
                    else
                    {
                        emitRM((char *)"LDA", 3, lhs->memoryOffset, 1, (char *)"2 Load address of base of array 587", (char*)lhs->attr.name);
                    }

                    emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push left side");
                    tempOffset--;
                    emitComment((char*)"TOFF:", tempOffset);
                    
                    
                    emitStart(node->child[1]);
                    

                    tempOffset++;
                    emitComment((char*)"TOFF:", tempOffset);

                    emitRM((char *)"LD", 4, tempOffset, 1, (char *)"1 Pop left into ac1");
                    emitRO((char *)"SUB", 3, 4, 3, (char *)"1 Compute location from index");
                    emitRM((char *)"LD", 3, 0, 3, (char *)"1 Load array element");

                }
            }
            else
            {

                if(lhs->isArray)
                {

                    /*printf("Here: %s %d\n", node->attr.name, node->linenum);

                    if(leftSide->expType == Char){
                        emitRM((char *)"LD", 3, leftSide->mOffset, 1, (char *)"2 Load address of base of array 766", (char*)leftSide->attr.name);
                        emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push left side");
                    }*/

                    tempOffset--;
                    emitComment((char*)"TOFF:", tempOffset);

                    emitStart(rhs);

                    tempOffset++;
                    emitComment((char*)"TOFF:", tempOffset);

                    if(lhs->memoryType == Global || lhs->memoryType == LocalStatic)
                    {
                        emitRM((char *)"LDA", 5, lhs->memoryOffset, 0, (char *)"1 Load address of base of array 620", (char*)lhs->attr.name);
                    }
                    else if(lhs->memoryType == Parameter)
                    {
                        emitRM((char *)"LD", 5, lhs->memoryOffset, 1, (char *)"2 Load address of base of array 623", (char*)lhs->attr.name);
                    }
                    else
                    {
                        emitRM((char *)"LDA", 5, lhs->memoryOffset, 1, (char *)"3 Load address of base of array 626", (char*)lhs->attr.name);
                    }

                    emitRO((char *)"SUB", 5, 5, 3, (char *)"2 Compute location from index");
                    emitRM((char *)"LD", 3, 0, 5, (char *)"2 Load array element");

                }

            }
        }
        
        //string literal compare checks
        else if(lhs->isArray && rhs->isArray)
        {
            emitRM((char *)"LDA", 3, lhs->memoryOffset, 1, (char *)"2 Load address of base of array 814", (char*)lhs->attr.name);
            emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push left side");
            emitRM((char *)"LDA", 3, rhs->memoryOffset, 1, (char *)"2 Load address of base of array 814", (char*)rhs->attr.name);
            emitRM((char*)"LD", 4, tempOffset, 1, (char*)("Load Left into ac1"), (char*)node->attr.name);
            emitRM((char*)"LD", 5, 1, 3, (char*)("AC2 <= |RHS|"));
            emitRM((char*)"LD", 6, 1, 4, (char*)("AC3 <= |LHS|"));
            emitRM((char*)"LDA", 2, 0, 5, (char*)("R2 <= |RHS|"));
            emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");
            emitRM((char*)"LD", 6, 1, 4, (char*)("AC3 <= |LHS|"));
            emitRO((char*)"CO", 4, 3, 5, (char*)("setup array compare LHS vs RHS"));
            emitRO((char*)"TNE", 5, 4, 3, (char*)("if not equal then test"));
            emitRO((char*)"JNZ", 5, 2, 7, (char*)("jump not equal"));
            emitRM((char*)"LDA", 3, 0, 2, (char*)("AC1 <= |RHS|"));
            emitRM((char*)"LDA", 4, 0, 6, (char*)("AC <= |LHS|"));
        }
        else
        {

            emitStart(node->child[0]);

            //save temp index from where we are
            //tmpIdx = tempOffset;  

            emitRM((char*)"ST", 3, tempOffset, 1, (char*)("Push the left side 677"));
            tempOffset--;
            emitComment((char*)"TOFF:", tempOffset);


            emitStart(node->child[1]);

            tempOffset++;
            emitComment((char*)"TOFF:", tempOffset);
            emitRM((char*)"LD", 4, tempOffset, 1, (char*)("Load Left into 1"), (char*)node->attr.name);
        }
        

        if(!strcmp(node->attr.name, "AND") || !strcmp(node->attr.name, "and"))
        {
            emitRO((char *)"AND", 3, 4, 3, (char *)("Op AND"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "OR") || !strcmp(node->attr.name, "or"))
        {
            emitRO((char *)"OR", 3, 4, 3, (char *)("Op OR"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, ">"))
        {
            emitRO((char *)"TGT", 3, 4, 3, (char *)("Op >"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "<"))
        {
            emitRO((char *)"TLT", 3, 4, 3, (char *)("Op <"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, ">="))
        {
            emitRO((char *)"TGE", 3, 4, 3, (char *)("Op >="), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "<="))
        {
            emitRO((char *)"TLE", 3, 4, 3, (char *)("Op <="), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "="))
        {
            emitRO((char *)"TEQ", 3, 4, 3, (char *)("Op =="), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "!="))
        {
            emitRO((char *)"TNE", 3, 4, 3, (char *)("Op !="), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "+"))
        {
            emitRO((char *)"ADD", 3, 4, 3, (char *)("Op +"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "-")){
            emitRO((char *)"SUB", 3, 4, 3, (char *)("Op -"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "/"))
        {
            emitRO((char *)"DIV", 3, 4, 3, (char *)("Op /"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "%"))
        {
            emitRO((char *)"MOD", 3, 4, 3, (char *)("Op %"), (char *)node->attr.name);
        }
        else if(!strcmp(node->attr.name, "*"))
        {
            emitRO((char *)"MUL", 3, 4, 3, (char *)("Op *"), (char *)node->attr.name);
        }
        //additional check for array here?
        //else if(!strcmp(node->attr.name, "[")){
            
        //}

    }
    //tempOffset = tmpIdx;
}

void emitCall(TreeNode* node, TreeNode* callLookup)
{
    int tmpIdx = tempOffset;

    emitComment((char*)("CALL EXPRESSION"));

    //track param count and if call has params(children)
    int pCount = 0;
    bool hasChild = false;

    //lookup original fn decl from symbol table
    TreeNode* curFunc = (TreeNode*)symbolTable.lookup(node->attr.name);

    //print call name
    emitComment((char*)"CALL", node->attr.name);

    if(node->child[0] != nullptr)
    {

        hasChild = true;
        TreeNode* getParams = node->child[0];

        for(int i = 0; i < MAXCHILDREN; i++)
        {
            if(getParams != nullptr)
            {
                getParams = getParams->sibling;
                pCount++;
            }
        }

        //printf("pCount: %d\n", pCount);

        //tempOffset -= pCount;

        //check single parameter
        if(pCount == 1)
        {

            //printf("%s\n", node->child[0]->attr.name);

            if(node->child[0]->subkind.exp == IdK && !node->child[0]->isArray)
            {
                if(node->child[0]->isInit)
                {
                    tempOffset--;
                    tmpIdx--;
                    emitComment((char*)"TOFF:", tempOffset);
                }
            }

            //tempOffset -= pCount;


            emitRM((char *)"ST", 1, tempOffset, 1, (char *)("1 Store fp in ghost frame for"), (char *)node->attr.name);

            emitComment((char*)"Param 1");

            if(node->child[0]->subkind.exp == IdK && !node->child[0]->isInit)
            {

                if(node->child[0]->memoryType == Global || node->child[0]->memoryType == LocalStatic)
                {

                    if(node->child[0]->isArray)
                    {
                        emitRM((char *)"LDA", 3, node->child[0]->memoryOffset, 0, (char *)("Load address of base of array 908"), node->child[0]->attr.name);
                        tempOffset--;
                    }
                    else
                    {
                        emitRM((char *)"LD", 3, node->child[0]->memoryOffset, 0, (char *)("1 variable"), node->child[0]->attr.name);
                    }
                
                }
                else if(node->child[0]->memoryType == Parameter)
                {
                    
                    if(!node->child[0]->isArray)
                    {
                        //emitRM((char *)"LD", 3, node->child[0]->mOffset, 1, (char *)("2 variable"), node->child[0]->attr.name);
                    }
                }
                /*else
                {
                    //printf("call name %s, %d\n", node->attr.name, node->linenum);
                }*/
                else if(node->child[0]->memoryType == Local)
                {
                    if(node->child[0]->isArray)
                    {
                        if(node->child[0]->expType != Char)
                        {
                            emitRM((char *)"LDA", 3, node->child[0]->memoryOffset, 1, (char *)("load address of base of array 916"), node->child[0]->attr.name);
                        }

                        tempOffset--;
                    }
                }
            }

            tempOffset-= pCount;
            emitComment((char*)"TOFF:", tempOffset);

            //if not array, adjust temp offset
            if(!node->child[0]->isArray)
            {

                tempOffset -= pCount;
                stFlag = false;
            }
            /*else if(nestCall)
            {
                emitRM((char *)"LDA", 3, node->child[0]->mOffset, 1, (char *)("Load address of base of array 913"));
                tempOffset-=pCount;
                nestCall = false;
            }*/
            

            emitComment((char*)"TOFF:", tempOffset);

            if(node->child[0]->subkind.exp == CallK)
            {
                nestCall = true;
            }
            
            emitStart(node->child[0]);
            
            

            //printf("%d\n", isUnary);
            //check for string lit's taken as args in a call
            if(node->child[0]->expType == CharInt)
            {
                callLookup = (TreeNode*)symbolTable.lookup(node->attr.name);
                if(callLookup != nullptr)
                {
                    //printf("Here: %s\n", callLookup->attr.name);
                    if(callLookup->child[0]->isArray)
                    {
                        //printf("Here: %s\n", callLookup->attr.name);
                        emitRM((char *)"LDA", 3, node->child[0]->memoryOffset, 0, (char *)"Load address of char array");
                        tempOffset--;
                    }
                }
            }

            emitRM((char *)"ST", 3, tempOffset, 1,(char *)"Push parameter 1001");
            emitComment((char *)("Param end"), node->attr.name);
            emitRM((char *)"LDA", 1, tmpIdx, 1,(char *)"1 Ghost frame becomes new active frame");
            
        }

        //more than 1 parameter
        else if(pCount > 1)
        {
            //set base number of parms
            int parmIterator = 1;
            TreeNode *curChild;
            //tempOffset++;
            emitComment((char*)"TOFF:", tempOffset);

            emitRM((char *)"ST", 1, tempOffset, 1, (char *)("2 Store fp in ghost frame for"), (char *)node->attr.name);

            if(node->child[0]->subkind.exp == IdK || node->child[0]->subkind.exp == OpK){

                curChild = (TreeNode*)symbolTable.lookup(node->child[0]->attr.name);

                //printf("Here: %s %d", curChild->attr.name, node->linenum);

                //check for array
                /*if(!strcmp(node->child[0]->attr.name, "[")){
                    printf("Open Bracket %s\n", node->child[0]->attr.name);
                }*/

                if(curChild == nullptr)
                {
                    curChild = node->child[0];
                }

            }
            else
            {
                curChild = node->child[0];
            }

            tempOffset--;
            
            emitComment((char*)"TOFF:", tempOffset);

            //check for arrays
            if(node->child[0]->subkind.exp != ConstantK && !strcmp(node->child[0]->attr.name, "["))
            {
                
                if(node->child[0] != nullptr)
                {
                    
                    mpCall = true;
                    tempOffset--;
                    emitComment((char*)"TOFF:", tempOffset);
                    emitComment((char *)("1035 Param"), parmIterator);

                    /*if(node->child[0]->child[0]->isArray)
                    {
                        
                        if(node->child[0]->child[0]->memT == Global)
                        {
                            emitRM((char *)"LDA", 3, node->child[0]->child[0]->mOffset, 0, (char *)("MP: Load address of base of array"));
                        }
                        else
                        {
                            emitRM((char *)"LDA", 3, node->child[0]->child[0]->mOffset, 1, (char *)("MP: Load address of base of array"));
                        }
                        emitRM((char *)"ST", 3, tempOffset, 1,(char *)("Push parameter"));
                        emitRM((char *)"LD", 4, tempOffset, 1, (char *)"1 Pop left into ac1");
                        emitRO((char *)"SUB", 3, 4, 3, (char *)"1 Compute location from index");
                        emitRM((char *)"LD", 3, 0, 3, (char *)"1 Load array element");
                    }*/
                    
                    emitStart(node->child[0]);
                    
                    emitRM((char *)"ST", 3, tempOffset, 1,(char *)("Push parameter 1064"));
                    
                    node->emitCodeLine -= 1;

                    if(node->child[0]->sibling != nullptr)
                    {
                        curChild = node->child[0]->sibling;
                    }
                    
                    parmIterator++;
                    
                    mpCall = false;
                }
            }

            //loop through all children (parameters)
            while(curChild != nullptr)
            {

                //printf("Here %d %d\n", parmIterator, node->linenum);

                tempOffset--;
                emitComment((char*)"TOFF:", tempOffset);
                emitComment((char *)("1071 Param"), parmIterator);

                //check for arrays
                if(curChild->isArray)
                {

                    //check mem types
                    if(curChild->memoryType == Global || curChild->memoryType == LocalStatic)
                    {

                        //check first parameter
                        //if(pCount == 1)
                        //{

                            emitRM((char *)"LDA", 3, curChild->memoryOffset, 0, (char *)("Load address of base of array 1025"), (char *)curChild->attr.name);
                        //}
                        /*else
                        {

                            emitRM((char *)"LDA", 3, curChild->mOffset, 0, (char *)("Load address of base of array"), (char *)curChild->attr.name);
                        }*/
                    }
                    else
                    {

                        //check first parameter
                        if(node->child[0]->subkind.exp == OpK)
                        {

                            emitRM((char *)"LD", 3, curChild->memoryOffset, 1, (char *)("Load address of base of array 1119"), (char *)curChild->attr.name);
                        }
                        else{

                            emitRM((char *)"LDA", 3, curChild->memoryOffset, 1, (char *)("Load address of base of array 1123"), (char *)curChild->attr.name);
                        }                                   
                    }
                    emitRM((char *)"ST", 3, tempOffset, 1,(char *)("1101 Push parameter"));
                }

                else if(curChild->subkind.exp == OpK || curChild->subkind.exp == IdK)
                {

                    /*emitStart(curChild->child[0]);
                    emitRM((char *)"ST", 3, tempOffset, 1,(char *)("Push left side"));
                    emitStart(curChild->child[1]);
                    */
                    mpCall = true;
                    emitStart(curChild);
                    
                    
                    emitRM((char *)"ST", 3, tempOffset, 1,(char *)("1115 Push parameter"));
                    mpCall = false;
                    
                }
                
                //not an array
                else
                {
                    
                    if(curChild->expType == Integer)
                    {
                        emitRM((char *)"LDC", 3, curChild->attr.value, 6, (char *)"Load integer constant");
                    }
                    else if(curChild->expType == Boolean)
                    {
                        
                        int boolVal;

                        if(!strcmp(curChild->attr.name, "true"))
                        {
                            boolVal = 1;
                        }
                        else
                        {
                            boolVal = 0;
                        }
                        emitRM((char *)"LDC", 3, boolVal, 6,(char *)"Load Boolean constant");
                    }
                    else if(curChild->expType == Char)
                    {
                        emitRM((char *)"LDC", 3, curChild->attr.value, 6, (char *)"Load character constant");
                    }

                    emitRM((char *)"ST", 3, tempOffset, 1,(char *)"3 Push parameter");
                }

                //increment parmiterator
                parmIterator++;
                if(curChild->sibling != nullptr)
                {
                    curChild = curChild->sibling;
                }
                else
                {
                    curChild = nullptr;
                }
            }
            emitComment((char *)("Param end"), node->attr.name);
            emitRM((char *)"LDA", 1, tmpIdx, 1,(char *)"Ghost frame becomes new active frame");

        }
    }
    //no parameters
    else if(pCount == 0)
    {
        emitRM((char *)"ST", 1, tmpIdx, 1, (char *)("3 Store fp in ghost frame for"), (char *)node->attr.name);
        emitComment((char *)("Param end"), node->attr.name);
        emitRM((char *)"LDA", 1, tempOffset, 1,(char *)"Ghost frame becomes new active frame");
    }

    curFunc = (TreeNode*)symbolTable.lookup(node->attr.name);
    emitRM((char *)"LDA", 3, 1, 7,(char *)"Return address in ac");
    int backpatch = emitSkip(0);
    emitRM((char *)"JMP",7, curFunc->emitCodeLine - backpatch - 1, 7, (char *)("CALL OUTPUT"), node->attr.name);       
    emitRM((char *)"LDA", 3, 0, 2,(char *)"Save the result in ac");
    emitComment((char *)("CALL end"), node->attr.name);

    tempOffset = tmpIdx;
    emitComment((char*)"TOFF:", tempOffset);
}

void emitConstant(TreeNode* node)
{
    if(node->expType == Integer)
    {
        emitRM((char *)"LDC", 3, node->attr.value, 6,(char *)"Load Integer constant");
    }
    //printing out weird values when using node->attr.value in Boolean
    //trying to fix by manually setting
    else if(node->expType == Boolean)
    {
        int boolVal;

        if(!strcmp(node->attr.name, "true"))
        {
            boolVal = 1;
        }
        else
        {
            boolVal = 0;
        }

        emitRM((char *)"LDC", 3, boolVal, 6,(char *)"Load Boolean constant");
    }
    else if(node->expType == Char)
    {
        emitRM((char *)"LDC", 3, node->attr.cvalue, 6,(char *)"Load Character constant");
    }
    else if(node->expType == CharInt)
    {
        emitStrLit(node->memoryOffset, node->attr.string);
    }
}

void emitId(TreeNode* node)
{
    //store
            if(stFlag)
            {

                if(node->memoryType == Global || node->memoryType == LocalStatic)
                {
                    if(!node->isArray)
                    {
                        emitRM((char *)"ST", 3, node->memoryOffset, 0,(char *)("Store variable"), node->attr.name);
                        stFlag = false;
                    }
                }
                else if(node->memoryType == Local)
                {
                    if(!node->isArray)
                    {
                        emitRM((char *)"ST", 3, node->memoryOffset, 1, (char *)("Store variable"), node->attr.name);
                        stFlag = false;
                    }
                }
                else if(node->memoryType == Parameter)
                {
                    emitRM((char *)"ST", 3, node->memoryOffset, 1, (char *)("Store variable"), node->attr.name);
                    stFlag = false;
                }

            }
            //load
            else
            {

                if(node->memoryType == Global || node->memoryType == LocalStatic)
                {

                    if(isUnary)
                    {
                        
                        if(node->isArray)
                        {
                            emitRM((char *)" LDA", 3, node->memoryOffset, 0, (char *)("1 Load address of base of array 671"), node->attr.name);
                            tempOffset--;
                            emitComment((char*)"TOFF:", tempOffset);
                        }
                        else
                        {
                            emitRM((char *)"LD", 3, node->memoryOffset, 0, (char *)("1 Load variable 797"), node->attr.name);
                        }
                    }
                    else
                    {
                        //emitRM((char *)"LD", 4, node->mOffset, 0, (char *)("1 load lhs variable"), node->attr.name);
                    }
                }

                else if(node->memoryType == Local)
                {

                    if(isUnary)
                    {
                        
                        if(node->isArray)
                        {
                            emitRM((char *)" LDA", 3, node->memoryOffset, 1, (char *)("2 Load address of base of array 783"), node->attr.name);
                            //tempOffset--;
                            emitComment((char*)"TOFF:", tempOffset);
                        }
                        else
                        {
                            emitRM((char *)"LD", 3, node->memoryOffset, 1, (char *)("2 Load variable 815"), node->attr.name);
                        }
                    }
                    else
                    {
                        if(!node->isInit)
                        {
                            if(node->isArray)
                            {
                                //printf("Here:%s %d\n", node->attr.name, node->linenum);
                                //tempOffset--;
                                 //emitRM((char *)"LD", 3, node->mOffset, 1, (char *)("load address of base of array 836"), node->attr.name);
                            }
                            else
                            {
                                emitRM((char *)"LD", 3, node->memoryOffset, 1, (char *)("1 load variable 851"), node->attr.name);
                            }
                        }
                        else if(node->isInit && !node->isArray)
                        {
                            //emitRM((char *)"LD", 3, node->mOffset, 1, (char *)("1 load variable 862"), node->attr.name);
                        }
                        //emitRM((char *)"LD", 4, node->mOffset, 1, (char *)("2 load lhs variable"), node->attr.name);
                    }
                }

                else if(node->memoryType == LocalStatic)
                {

                    if(isUnary)
                    {
                        
                        if(node->isArray)
                        {
                            emitRM((char *)" LDA", 3, node->memoryOffset, 0, (char *)("3 Load address of base of array 802"), node->attr.name);
                            tempOffset--;
                            emitComment((char*)"TOFF:", tempOffset);
                        }
                        else
                        {
                            emitRM((char *)"LD", 3, node->memoryOffset, 0, (char *)("3 Load variable 833"), node->attr.name);
                        }
                    }
                    else
                    {
                        //emitRM((char *)"LD", 4, node->mOffset, 0, (char *)("3 load lhs variable"), node->attr.name);
                    }
                }

                else if(node->memoryType == Parameter)
                {

                    if(isUnary)
                    {
                        
                        if(node->isArray && node->expType != Char)
                        {
                            emitRM((char *)" LDA", 3, node->memoryOffset, 1, (char *)("4 Load address of base of array 820"), node->attr.name);
                            tempOffset--;
                            emitComment((char*)"TOFF:", tempOffset);
                        }
                        else
                        {
                            if(node->expType != Char){
                            emitRM((char *)"LD", 3, node->memoryOffset, 1, (char *)("4 Load variable 851"), node->attr.name);
                            }
                        }
                    }
                    else
                    {
                        //printf("Here IdK: %s %d\n", node->attr.name, node->linenum);
                        if(!node->isInit)
                        {
                            if(node->isArray)
                            {
                                tempOffset--;
                                emitRM((char *)"LD", 3, node->memoryOffset, 1, (char *)("load address of base of array 836"), node->attr.name);
                            }
                            else{
                                
                            emitRM((char *)"LD", 3, node->memoryOffset, 1, (char *)("1 load variable 861"), node->attr.name);
                            }
                        }
                        else if(node->isInit && !node->isArray)
                        {
                            emitRM((char *)"LD", 3, node->memoryOffset, 1, (char *)("1 load variable 861"), node->attr.name);
                        }
                        //emitRM((char *)"LD", 4, node->mOffset, 1, (char *)("4 load lhs variable"), node->attr.name);
                    }
                }
            }
}

void emitGlobAndStats(TreeNode* node)
{

    if(node != nullptr)
    {

        if(node->nodekind == DeclK && node->subkind.decl == VarK)
        {

            if(node->memoryType == Global || node->isStatic)
            {

                if(node->isArray)
                {

                    emitRM((char *)"LDC", 3, node->memorySize - 1, 6,(char *)"load size of array", (char *) node->attr.name);
				    emitRM((char *)"ST", 3, node->memoryOffset + 1, 0,(char *)"save size of array", (char *) node->attr.name);
                }
                else
                {

                    if(node->child[0] != nullptr)
                    {
                        emitStart(node->child[0]);
                        emitRM((char *)"ST", 3, node->memoryOffset, 0,(char *)"Store variable",(char *)node->attr.name);
                    }
                }
            }
        }

        for(int i = 0; i < MAXCHILDREN; i++)
        {
            emitGlobAndStats(node->child[i]);
        }
        if(node->sibling != nullptr)
        {
            emitGlobAndStats(node->sibling);
        }
    }
    
}

void emitIO(TreeNode* node)
{

    emitSkip(1);
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));
	emitComment((char *)("FUNCTION input"));
	TreeNode *curIO = (TreeNode*)symbolTable.lookup((char *)("input"));
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	curIO->emitCodeLine = emitSkip(0)-1;
	curIO->attr.name = (char *) "input";
	emitRO((char *)"IN", 2, 2, 2,(char *)("Grab int input"));
	emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
	emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
	emitRM((char *)"JMP", 7, 0, 3,(char *)("Return"));
	emitComment((char *)("END FUNCTION input"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

    emitComment((char *)("FUNCTION output"));
	curIO = (TreeNode*)symbolTable.lookup((char *)("output"));
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	curIO->emitCodeLine = emitSkip(0)-1;
	curIO->attr.name = (char *) "output";
	emitRM((char *)"LD", 3, -2, 1,(char *)("Load parameter"));
    emitRO((char *)"OUT",3,3,3,(char *)("Output integer"));
	emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
	emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
	emitRM((char *)"JMP", 7, 0, 3,(char *)("Return"));
	emitComment((char *)("END FUNCTION output"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

    emitComment((char *)("FUNCTION inputb"));
	curIO = (TreeNode*)symbolTable.lookup((char *)("inputb"));
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	curIO->emitCodeLine = emitSkip(0)-1;
	curIO->attr.name = (char *) "inputb";
	emitRO((char *)"INB", 2, 2, 2, (char *)("Grab bool input"));
	emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
	emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
	emitRM((char *)"JMP", 7, 0, 3, (char *)("Return"));
	emitComment((char *)("END FUNCTION inputb"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION outputb"));
	curIO = (TreeNode*)symbolTable.lookup((char *)("outputb"));
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	curIO->emitCodeLine = emitSkip(0)-1;
	curIO->attr.name = (char *) "outputb";
	emitRM((char *)"LD", 3, -2, 1,(char *)("Load parameter"));
	emitRO((char *)"OUTB", 3, 3, 3, (char *)("Output bool"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION outputb"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION inputc"));
	curIO = (TreeNode*)symbolTable.lookup((char *)("inputc"));
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	curIO->emitCodeLine = emitSkip(0)-1;
	curIO->attr.name = (char *) "inputc";
	emitRO((char *)"INC", 2, 2, 2, (char *)("Grab char input"));
	emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
	emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
	emitRM((char *)"JMP", 7, 0, 3, (char *)("Return"));
	emitComment((char *)("END FUNCTION inputc"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION outputc"));
	curIO = (TreeNode*)symbolTable.lookup((char *)("outputc"));
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	curIO->emitCodeLine = emitSkip(0)-1;
	curIO->attr.name = (char *) "outputc";
	emitRM((char *)"LD", 3, -2, 1, (char *)("Load parameter"));
	emitRO((char *)"OUTC", 3, 3, 3, (char *)("Output char"));
	emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
	emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
	emitRM((char *)"JMP", 7, 0, 3, (char *)("Return"));
	emitComment((char *)("END FUNCTION outputc"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION outnl"));
	curIO = (TreeNode*)symbolTable.lookup((char *)("outnl"));
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	curIO->emitCodeLine = emitSkip(0)-1;
	curIO->attr.name = (char *) "outnl";
	emitRO((char *)"OUTNL", 3, 3, 3, (char *)("Output a newline"));
	emitRM((char *)"LD", 3, -1, 1, (char *)("Load return address"));
	emitRM((char *)"LD", 1, 0, 1, (char *)("Adjust fp"));
	emitRM((char *)"JMP", 7, 0, 3, (char *)("Return"));
	emitComment((char *)("END FUNCTION outnl"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));
}

void emitInit(TreeNode* node)
{

    TreeNode* mainFunc;
	
	int bp = emitSkip(0)-1;
	emitNewLoc(0);
	mainFunc = (TreeNode*)symbolTable.lookup("main"); 
	emitRM((char *)"JMP", 7, bp, 7, (char *)("Jump to init [backpatch]"));
	emitComment((char *)("INIT"));
	emitSkip(bp);
	emitRM((char *)"LDA", 1, 0 + globalOffset, 0, (char *)("set first frame at end of globals"));
	emitRM((char *)"ST", 1, 0, 1, (char *)("store old fp (point to self)"));
	emitComment((char *)("INIT GLOBALS AND STATICS"));
	emitGlobAndStats(node);
	emitComment((char *)("END INIT GLOBALS AND STATICS"));
	emitRM((char *)"LDA", 3, 1, 7, (char *)("Return address in ac"));
	bp = emitSkip(0);
	emitRM((char *)"JMP", 7, (mainFunc->emitCodeLine-bp-1), 7, (char *)("Jump to main"));
	emitRO((char *)"HALT", 0, 0, 0, (char *)("DONE!"));
	emitComment((char *)("END INIT"));
}
