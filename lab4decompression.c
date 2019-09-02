#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
	FILE *fpt1,*fpt2;
	fpt1=fopen("compressfile.txt","rb");
	fpt2=fopen("decompress.txt","w");

	typedef struct{
	int index;
	int weight;
	}nodetree;

	int count=0,i=0;
	char cc,c;
	int index=0;
	int weight=0;
	nodetree *nodes=0;
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


	int noofnodes=0;
	int *indexofleaf = 0;
	int *indexofparent = 0;

	int remindex=0;
	remindex=remindex+1;
	while(remindex<noofnodes)
	{
	index=(remindex+2)/2;
	weight=nodes[remindex+1].weight + nodes[remindex+2].weight;

	noofnodes=noofnodes+1;
	int ppp;
	ppp=noofnodes;
	while (nodes[ppp].weight > weight && ppp > 0) 
	{
		printf("insidewhileoftree\n");
        memcpy(&nodes[ppp + 1], &nodes[ppp], sizeof(nodetree));
        //switch(nodes[ppp].index)
        {
        if(nodes[ppp].index > 0) 
    		{
    		printf("insideifoftree\n");
            indexofparent[nodes[ppp].index]+=1;
        	}
        else if(nodes[ppp].index < 0) 
        	{
        	printf("insideelseoftree\n");
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



int bufferbits=0;
int sizeofbuffer=256;
int iii=0;
int indexofnode=0;
char qqq;

for(iii=0;iii<count;iii++)
{
	printf("%c",data[iii]);
	bufferbits=data[iii];
	indexofnode=nodes[noofnodes].index;
	qqq=indexofnode;
	fwrite(&qqq,1,1,fpt2);
}

return 0;
}

