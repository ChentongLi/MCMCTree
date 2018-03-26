int IsInclude(char *a,char b[20][10],int n){

    int i;
    for (i=0;i<n;i++)
        if (strcmp(a,b[i])==0)
            return 1;

    return 0;

}

BiNode *init()
{

    FASTAFILE *ffp;
    char *seq;
    char *name;
    int   L;
    char *filename="p1sequence.fasta";

	int n=0;
	BiNode* S[MAXDATASIZE];
	int top=-1;
	ffp = OpenFASTA(filename);

    if (ffp==NULL) {

        printf("wrong input!\n");
        return NULL;
    }


	// data name
	char b0[6][10]={"AY000431","AY000433","AY000434","AY000435","AY000441","AY000465"};
	char b1[1][10]={"AY000436"};
	char b2[8][10]={"AY000421","AY000425","AY000426","AY000427","AY000428","AY000429",
	"AY000462","AY000467"};
	char b3[7][10]={"AY000422","AY000423","AY000432","AY000439","AY000461","AY000463",
	"AY000464"};
    char b4[5][10]={"AY000424","AY000456","AY000459","AY000466","AY000468"};
    char b5[8][10]={"AY000437","AY000438","AY000442","AY000443","AY000446","AY000453",
    "AY000457","AY000458"};
    char b6[8][10]={"AY000430","AY000444","AY000445","AY000449","AY000451","AY000452",
    "AY000454","AY000469"};
    char b7[6][10]={"AY000440","AY000447","AY000448","AY000450","AY000455","AY000460"};



	while(ReadFASTA(ffp, &seq, &name, &L)){
        S[n]=malloc(sizeof(BiNode));
		S[n]->lchi=NULL;
		S[n]->rchi=NULL;
        S[n]->sequence=calloc(1000,sizeof(char));
        S[n]->name=calloc(10,sizeof(char));
	    strcpy(S[n]->sequence,seq);
	    strncpy(S[n]->name,name,8);

	    if (IsInclude(S[n]->name,b0,6)) {S[n]->NodeTime=4;}
	    else if (IsInclude(S[n]->name,b1,1)) {S[n]->NodeTime=28;}
	    else if (IsInclude(S[n]->name,b2,8)) {S[n]->NodeTime=56;}
	    else if (IsInclude(S[n]->name,b3,7)) {S[n]->NodeTime=112;}
	    else if (IsInclude(S[n]->name,b4,5)) {S[n]->NodeTime=140;}
	    else if (IsInclude(S[n]->name,b5,17)) {S[n]->NodeTime=252;}
	    else if (IsInclude(S[n]->name,b6,9)) {S[n]->NodeTime=392;}
	    else if (IsInclude(S[n]->name,b7,6)) {S[n]->NodeTime=480;}
	    else {
                printf("%s have no time\n",S[n]->name);
                S[n]->NodeTime=252;
	    }
	    free(name);
	    free(seq);

		n++;
	}
	seqlength=strlen(S[1]->sequence);
	//printf("number of node=%d\n",n);
	top=n-1;
	//printf("length %d\n",strlen(S[top]->sequence));
	int i,j,len=n;
	int judge[MAXDATASIZE];
	//for (i=0;i<len;i++) printf("S[%d]=%d\n",i,S[i]->data);

	for (i=0;i<MAXDATASIZE;i++) judge[i]=i;
	//srand(time(0));
	int r;
	while(len>1){ //shuffle algorithm to build the Tree
		top++;
		S[top]=malloc(sizeof(BiNode));
		S[top]->name=calloc(10,sizeof(char));
		strcpy(S[top]->name,"AYNULL");
		S[top]->sequence=NULL;
		r=rand()%len;
		j=judge[r];
		S[top]->lchi=S[j];
		len--;
		judge[r]=judge[len];
		//printf("j=%d\n",j);

		r=rand()%len;
		j=judge[r];
		S[top]->rchi=S[j];
		len--;
		judge[r]=judge[len];
		judge[len]=top;
		len++;

		S[top]->NodeTime=MIN(S[top]->lchi->NodeTime,S[top]->rchi->NodeTime)-1;
		//printf("j=%d\n\n",j);

	}
    //printf("top=%d\n",top);
	//for (i=0;i<top+1;i++) printf("S[%d]=%d\n",i,S[i]->data);
	return S[top];
}
