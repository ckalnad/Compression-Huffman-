#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
	FILE *fpt1,*fpt2;
	fpt1 = fopen(argv[1],"rb");

	char c,cc;
	int count=0,count1=0;
    int i=0,symcount=0;

 if (fpt1 == NULL)
    {
        printf("Cannot open file ");
        exit(0);
    }
 
    while((c=fgetc(fpt1))!=EOF)
    {
        printf("%c",c);
		count++;
	}

    printf("\nCount=%d\n",count);
    rewind(fpt1);

    int data[count-1];
	while(i<count)
	{
    	while((cc=fgetc(fpt1))!=EOF)
     	{
			data[i]=cc;
			i++;
		}
    
	}

	//printf("%s\n",data);

	rewind(fpt1);
    
    fpt2 = fopen("letters.txt", "w");
    
    if (fpt2 == NULL)
    {
        printf("Cannot open file ");
        exit(0);
    }


int ii=0;
unsigned char jj=0;
unsigned char ch=0;
int countchar[255]={0};

for(ii=0;ii<count;ii++)
{
	for(jj=0;jj<255;jj++)
	{
		if(data[ii]==(ch+jj))
		{
			countchar[jj]++;
		}
	}
}

for(jj=0;jj<255;jj++)
{
	printf("%c%d",jj,countchar[jj]);
	fwrite(&jj,1,1,fpt2);
	fwrite(&countchar[jj],1,1,fpt2);
}

fclose(fpt2);
fpt2 = fopen("letters.txt", "rb");
FILE *fpt3;
fpt3 = fopen("aaa.txt","w");

int count11=0;
char cd,dc;
int iii=0;


cd=fgetc(fpt2);
fwrite(&cd,1,1,fpt3);

while((cd=fgetc(fpt2))!=EOF)
    {
        printf("%c",cd);
		count11++;
		iii++;
		fwrite(&cd,1,1,fpt3);
    }


    printf("\nCount2=%d\n",count11);
    rewind(fpt2);

    fclose(fpt3);
	fpt3 = fopen("aaa.txt","rb"); 
	rewind(fpt3);   

    int data1[count11-1];
	
    iii=0;
	while(iii<count11)
	{
    	while((dc=fgetc(fpt3))!=EOF)
     	{
     		//printf("in while");
			data1[iii]=dc;
			//printf("%c",dc);
			//printf("HI");
			printf("%c",data1[iii]);
			iii++;
		}
    
	}

	

	int q=0,w=0;
	unsigned char a,b;
        

    for (q = 1; q < count11; q=q+2) 
    {
		for (w = q + 2; w < count11; w=w+2)
		{
			if (data1[q] > data1[w]) 
			{
				a =  data1[q];
				b = data1[q-1];
				data1[q] = data1[w];
				data1[q-1] = data1[w-1];
				data1[w] = a;
				data1[w-1] = b;
			}
		}
	}


int jjj=0;
FILE *fpt4;
fpt4=fopen("sorted.txt","w");

for(jjj=0;jjj<508;jjj++)
{
	printf("%c",data1[jjj]);
	fwrite(&data1[jjj],1,1,fpt4);

}

FILE *fpt5;
fpt5=fopen("finalsort.txt","w");

int rrr=0;
int datacount=0;
int freqcount=0;

for(rrr=0;rrr<508;rrr=rrr+2)
{
	if(data1[rrr+1]!=0)
	{
	printf("%c",data1[rrr]);
	fwrite(&data1[rrr],1,1,fpt5);
	datacount++;
	freqcount++;
	
	fwrite(&data1[rrr+1],1,1,fpt5);
	}

}
int ttt=0;
char opo,pop;

printf("%d\n",datacount);
printf("%d\n",freqcount);

unsigned char datasorted[(datacount/2)-1];
unsigned char freqsorted[(freqcount/2)-1];

fclose(fpt5);
fpt5=fopen("finalsort.txt","rb");

for(ttt=0;ttt<datacount/2;ttt++)
{
	opo=fgetc(fpt5);
	datasorted[ttt]=opo;
	pop=fgetc(fpt5);
	freqsorted[ttt]=pop;
}

printf("%s",datasorted);
printf("%s",freqsorted);

//Binary tree begins here
//Postorder traversing
//-ve index - leaf node - alphabet
//+ve index - internal node - frequency

typedef struct{
	int index;
	int weight;
}nodetree;

int noofnodes=0;
nodetree *nodes = 0;
int *indexofleaf = 0;
int *indexofparent = 0;

indexofleaf=(int*)calloc(freqcount,sizeof(int));
nodes=(nodetree*)calloc(2*(datacount+freqcount-1),sizeof(nodetree));
indexofparent=(int*)calloc(freqcount,sizeof(int));

//addition of extra leaves
int fff=0;
int weight=0;
int index=0;


for(fff=0;fff<datacount;++fff)
{
weight=freqsorted[fff];
fff=fff+1;
index=-fff;
//switch(freqsorted[fff])
{
	if(freqsorted[fff]>0)
	{
	noofnodes=noofnodes+1;
	int mmm;
	mmm=noofnodes;
	while (nodes[mmm].weight > weight && mmm > 0) 
	{
        memcpy(&nodes[mmm + 1], &nodes[mmm], sizeof(nodetree)); //move larger weight nodes to right
        //switch(nodes[mmm].index)
        {
        if(nodes[mmm].index < 0) 					//+ve index - leaf node
    		{
            indexofleaf[-nodes[mmm].index]+=1;
    		}
        else if(nodes[mmm].index > 0) 
        	{
            indexofparent[nodes[mmm].index]+=1;		//-ve index - parent node
        	}
		}
		mmm=mmm-1;
	}
	mmm=mmm+1;
    nodes[mmm].index = index;				//place the nodes to required position
    nodes[mmm].weight = weight;
    //switch(index)
    {
    if(index < 0) 
    {
        indexofleaf[-index] = mmm;
    }
    else if(index > 0) 
    {
        indexofparent[index] = mmm;
    }
	}	
}
}
}


printf("\nBulding of leaves done\n");
//Bulding of tree

int remindex=0;
remindex=remindex+1;
while(remindex<noofnodes)
{
	index=(remindex+2)/2;
	weight=nodes[remindex+1].weight + nodes[remindex+2].weight;			//Addition of weights of adjacent nodes

	noofnodes=noofnodes+1;
	int ppp;
	ppp=noofnodes;
	while (nodes[ppp].weight > weight && ppp > 0) 
	{
		//printf("insidewhileoftree\n");
        memcpy(&nodes[ppp + 1], &nodes[ppp], sizeof(nodetree));
        //switch(nodes[ppp].index)
        {
        if(nodes[ppp].index > 0) 
    		{
    		//printf("insideifoftree\n");
            indexofparent[nodes[ppp].index]+=1;
        	}
        else if(nodes[ppp].index < 0) 
        	{
        	//printf("insideelseoftree\n");
            indexofleaf[-nodes[ppp].index]+=1;
    		}
		}
ppp=ppp-1;
}
ppp=ppp+1;
    nodes[ppp].index = index;
    nodes[ppp].weight = weight;
    //switch(index)
    {
    if(index < 0) 
    {
        indexofleaf[-index] = ppp;
    }
    else if(index > 0) 
    {
        indexofparent[index] = ppp;
    }
	}
	indexofparent[remindex/2]=ppp;	
}

printf("Bulding of tree done\n");


FILE *fpt6;
fpt6=fopen("compressfile.txt","w");

//writing to file

int bbb=0;
char dt;
int indexofnode;
indexofnode=0;
int *first;
first=(int *)calloc((datacount-1),sizeof(int));
int counter=0;
int bufferbits=0;
int bitnow=0;
int sizeofbuffer = 256;
unsigned char arrbuff[sizeofbuffer-1];

for(bbb=0;bbb<datacount;bbb++)
{
	dt=datasorted[bbb];
	counter=counter+1;
	first[counter]=indexofnode % 2; //take remaning bits
	indexofnode=indexofparent[(indexofnode+1)/2];
	bitnow=first[counter];

	//switch(bufferbits)
	{
		if(bufferbits==sizeofbuffer<<sizeof(int))
		{
			bufferbits=bitnow;
			fwrite(&bufferbits,1,sizeofbuffer,fpt6);
			bufferbits=0;

		}
	}

	
}


fclose(fpt1);
fclose(fpt2);
fclose(fpt3);
fclose(fpt4);
fclose(fpt5);
fclose(fpt6);
return 0;
}









