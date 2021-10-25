#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a)>(b)?(a):(b))

#define REPEAT(n) int i=0; for(i=0; i<n; i++)

typedef struct aplicant node;
typedef struct aplicant *ndPtr;

struct aplicant
{
    char name[25], surname[25], dep[10];
    float average;
    ndPtr next;
};

void write2File(ndPtr First, char dep[], float avg);
ndPtr findWinner(ndPtr First, char dep[], float avg);
void addNodeEnd(ndPtr *First, node n);

FILE *infile,*outfile;

int main()
{
    infile = fopen("data.txt", "r");
    outfile = fopen("results.txt", "w");

    if(infile==NULL)
        exit(1);

    int n; // number of applicants
    char depCr[10]; // dep criteria
    float avgCr; // avg criteria
    ndPtr First=NULL,winner=NULL;
    node tmp;
    fscanf(infile, "%d%s%f", &n, depCr, &avgCr);
//Read n and criteria from the files
    REPEAT(n)
    {
        fscanf(infile, "%s%s%s%f", tmp.name, tmp.surname, tmp.dep, &tmp.average);
        tmp.next = NULL;
        addNodeEnd(&First, tmp);
    }
//call findWinner() function, and write info of the winner to the file.
    winner = findWinner(First, depCr, avgCr);
    fprintf(outfile,"%s %s %s %.2f\n\n",winner->name,winner->surname,winner->dep,winner->average);
//write info of all students meeting the criteria.
    write2File(First, depCr, avgCr);
//close files.
    fclose(infile);
    fclose(outfile);
    return 0;
}
void write2File(ndPtr First, char dep[], float avg)
{
    while(First!=NULL)
    {
        if(First->average>=avg && !strcmp(First->dep, dep))
            fprintf(outfile,"%s %s %s %.2f\n",First->name,First->surname,First->dep,First->average);
        First=First->next;
    }
    return;
}
ndPtr findWinner(ndPtr First, char dep[], float avg)
{
    ndPtr Best=NULL;
    float bstAvg=0;
    while(First!=NULL)
    {
        if((MAX(bstAvg, First->average)==First->average)&&(!strcmp(dep, First->dep))&&(First->average>=avg))
            {
                Best = First;
                bstAvg = Best->average;
            }
        First = First->next;
    }
    return Best;
}
void addNodeEnd(ndPtr *First, node n)
{
//crate new node and allocate sapce in memory.
    ndPtr newNode;
    newNode = (ndPtr) malloc(sizeof(node));
//fill the content of the node
    *newNode=n;

    if((*First)==NULL)
    {
        (*First)=newNode;
    }
    else
    {
        ndPtr Last=*First;
        while(Last->next!=NULL)
            Last=Last->next;
        Last->next=newNode;
        Last=newNode;
    }
    return ;
}
