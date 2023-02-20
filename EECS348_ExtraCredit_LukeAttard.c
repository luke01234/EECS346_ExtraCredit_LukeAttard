#include <stdio.h>
#include <stdlib.h>

int IndexOf(int val, int list[])
{
    for (int i=0; i<5;i++)
    {
        if (list[i]==val)
        {
            return i;
        }
    }
    return 5;
}

int IsIn(int val, int list[])
{
    for (int i=0; i<5;i++)
    {
        if (list[i]==val)
        {
            return 1;
        }
    }
    return 0;
}
/*void PrintAll(int list[])
{
    for (int i=0;i<5;i++)
    {
        printf("%i ",list[i]);
    }
    printf("\n");
}*/

void  PrintToTerminalAndFile(int list[])
{
  FILE *outputfile = fopen("outputfile.txt", "w");
  for (int i=0;i<5;i++)
  {
    printf("Department %i gets programmer %i.\n",i, list[i]);
    fprintf(outputfile,"Department %i gets programmer %i.\n",i,list[i]);
  }
}

void Sort(int deps[5][5], int progs[5][5])
{
    int firstPic[5]={0,0,0,0,0};
    int i=0;
    while (IsIn(0,firstPic))
    {
        /*printf("old: ");
        PrintAll(firstPic);
        printf("adding %i\n",deps[IndexOf(0,firstPic)][i]);*/
        if (!IsIn(deps[IndexOf(0,firstPic)][i], firstPic))
        {
            firstPic[IndexOf(0,firstPic)]=deps[IndexOf(0,firstPic)][i];
            i=0;
        }
        else
        {
            int valToAdd=deps[IndexOf(0,firstPic)][i];
            int oldDept = IndexOf(deps[IndexOf(0,firstPic)][i], firstPic)+1;
            int curDept = IndexOf(0, firstPic)+1;
            //printf("old dept %i, new dept %i\n",oldDept,curDept);
            int priority1 = IndexOf(oldDept, progs[deps[IndexOf(0,firstPic)][i]-1]);
            int priority2 = IndexOf(curDept, progs[deps[IndexOf(0,firstPic)][i]-1]);
            //printf("priority1: %i priority2: %i programmer: ",priority1, priority2);
            //printf("%i\n",valToAdd);
            if (priority1<priority2)
            {
                i++;
            }
            else
            {
              firstPic[oldDept-1]=0;
              firstPic[curDept-1]=valToAdd;
              i=0;
              /*printf("new: ");
              PrintAll(firstPic);
              printf("\n");*/
            }
            
        }
    }
    PrintToTerminalAndFile(firstPic);
    //PrintAll(firstPic);
}

void main()
{
    FILE *inputfile = fopen("matching-data.txt","r");

    if(inputfile == NULL)
    {
        perror("Unable to open file! Please create an input file of name 'matching-data.txt' in this directory.");
        exit(1);
    }

    char chunk[3];
    float vals[12];
    int departmentPrefs[5][5];
    int programmerPrefs[5][5];
    
    int indexInner = 0;
    int indexOuter = 0;

    while(fgets(chunk,sizeof(chunk),inputfile)!= NULL)
    {
        
        if (indexInner<5)
        {
            int num = atoi(chunk);
            if (indexOuter<5)
            {
                departmentPrefs[indexInner][indexOuter]=num;
            }
            else
            {
                programmerPrefs[indexInner][indexOuter-5]=num;
            }
            indexInner++;
        }
        else if (indexOuter<10)
        {
            indexOuter++;
            indexInner=0;
        }   
        
    }
    
    Sort(departmentPrefs,programmerPrefs);
}