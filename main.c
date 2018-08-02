#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"hmath.h"
#include "ini.h"

#define bufLength 1000
Vector vtemp, vtemp2;
const double epsilon = 1e-6 ;

typedef struct {
	int labelNum;
	int dim;
	int stage;
	char MAS[300];
	char DATALIST[300];
	char FEAT[300];
	char LABEL[300];
	int mode;
}Config;

Config config;

static int handler(void* user, const char* section, const char* name, const char* value) {
	Config* pconfig = (Config*)user;
	#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("All", "labelNum")) { pconfig->labelNum = atoi(value); }
	else if (MATCH("All", "dim")) { pconfig->dim = atoi(value);   }
	else if (MATCH("All", "stage")) { pconfig->stage = atoi(value);}
	else if (MATCH("All", "MAS")) { strcpy(pconfig->MAS,value);}
	else if (MATCH("All", "DATALIST")) { strcpy(pconfig->DATALIST,value);}
	else if (MATCH("All", "FEAT")) { strcpy(pconfig->FEAT,value);}
	else if (MATCH("All", "LABEL")) { strcpy(pconfig->LABEL,value);}
	else if (MATCH("All", "Mode")) { pconfig->mode = atoi(value); }
	else return 0;
	return 1;
}

int numRowInFile(FILE* f) {
	int c; int i = 0;
	while ((c = fgetc(f)) != EOF)
	{
		if (c == '\n')
			i++;
	}
	fseek(f, 0, SEEK_SET);
	printf("the num of rows in file is %d\n", i);
	return i;
}

long singleFileCal(FILE* f, int dim, Vector vsum , Vector v2sum) {
	long nrows = (long)numRowInFile(f);
	int i; int j;
	for (i = 1; i <= nrows; i++) {
		LoadSVectorE(f, vtemp);
		for (j = 1; j <= dim; j++) {
			vsum[j] += vtemp[j];
			v2sum[j] += vtemp[j] * vtemp[j];
		}
	//	ShowVector(vsum);
	}
	return nrows;
}

void MVN(int dim,Vector mean, Vector std, Vector v) {
	int i;
	if(config.mode==1)for (i = 1; i <= dim; i++){
        v[i] = (v[i] - mean[i]) / std[i];
    }
	else if (config.mode == 2)for (i = 1; i <= dim; i++)v[i] = v[i] - mean[i];
	else { printf("mode is not limited to 1 MVN and 2 MN\nmode %d is not recognizable.\n", config.mode); exit(-1); }
}

void featToDNNFeat(char* segName,FILE* f, FILE* dnnFeatFile, FILE* dnnLabelFile,Vector mean ,Vector std ,int label,int dim,int labelNum) {
	int nrows = numRowInFile(f);
	int i;
	fprintf(dnnFeatFile, segName); fprintf(dnnLabelFile, segName);
	fprintf(dnnFeatFile, "  ["); fprintf(dnnLabelFile, "  [");
	for (i = 1; i <= nrows; i++) {
		LoadSVectorE(f, vtemp2);
		MVN(dim, mean, std, vtemp2);
		WriteSVector2(dnnFeatFile, vtemp2);
		WriteIntVec2(dnnLabelFile, CreateIIntVec(labelNum, label));
	}
	fprintf(dnnFeatFile, "]\n"); fprintf(dnnLabelFile, "]\n");
}

int main(int argc , char* argv[]) {
	int fileNum; FILE* f; FILE* flist; FILE* dnnFeatFile; FILE* dnnLabelFile; int i;
	char fileNameBuf[bufLength];
	long nrows = 0;
	Vector vsum=NULL ; Vector v2sum=NULL ;
	Vector vmean=NULL ; Vector vstd=NULL ;
	char* fileName; int fileLabel; char* filePath;
	int labelNum,dim,stage;

	if (ini_parse(argv[1], handler, &config) < 0) {
		printf("Can't load 'config.ini'\n");
		system("pause");
		return 1;
	}
	else printf("finish reading the config.ini\n");
	printf("%s\n%s\n",config.MAS,config.DATALIST);
	labelNum=config.labelNum;dim=config.dim;stage=config.stage;
	
	vsum = CreateVector(dim); v2sum = CreateVector(dim);
	vmean = CreateVector(dim); vstd = CreateVector(dim);
	vtemp = CreateVector(dim); vtemp2 = CreateVector(dim);
	ZeroVector(vsum); ZeroVector(v2sum);

	if (stage <= 1) {
		printf("We will cal the mean and std , and the dimension is %d\n", dim);
		printf("Start cal\n");
		flist = fopen(config.DATALIST , "r");
		while (fgets(fileNameBuf, bufLength, flist) != NULL) {
			printf("%s", fileNameBuf);
			if (fileNameBuf[0] == '\n')break;
			filePath = strtok(fileNameBuf, "\t");
			f = fopen(filePath, "r");
			nrows += singleFileCal(f, dim, vsum, v2sum);
			printf("Now the accumulated rows num is %ld\n ", nrows);
			fclose(f);
		}
		fclose(flist);
		printf("\nfinish traversaling all data files and the accumulated rows num is %ld\n ", nrows);
		for (i = 1; i <= dim; i++) {
			vmean[i] = vsum[i] / (double)nrows;
			vstd[i] = sqrt(v2sum[i] / (double)nrows - vmean[i] * vmean[i]);
		}
        for (i = 1; i <= dim; i++){
            if(vstd[i]>=0 && vstd[i]<=epsilon)vstd[i]=0;
            if(vstd[i]<=0 && vstd[i]>=epsilon)vstd[i]=0;
        }
		f = fopen(config.MAS, "w");
		WriteSVectorE(f, vmean);
		WriteSVectorE(f, vstd);
		fclose(f);
	}

	if (stage <= 2) {
		f = fopen(config.MAS, "r");
		LoadSVectorE(f, vmean); LoadSVectorE(f, vstd);
		fclose(f);
		flist = fopen(config.DATALIST, "r");
		dnnFeatFile = fopen(config.FEAT, "w");
		dnnLabelFile = fopen(config.LABEL, "w");
		while (fgets(fileNameBuf, bufLength, flist) != NULL) {
			printf("%s", fileNameBuf);
			if (fileNameBuf[0] == '\n')break;
			filePath = strtok(fileNameBuf, "\t");
			fileName = strtok(NULL, "\t");
			fileLabel = atoi(strtok(NULL, "\n"));
			f = fopen(filePath, "r");
			featToDNNFeat(fileName, f, dnnFeatFile, dnnLabelFile, vmean, vstd, fileLabel, dim,labelNum);
			fclose(f);
			printf("converting %s and its label is %d\n ", fileName,fileLabel);
		}
		fclose(dnnFeatFile); fclose(dnnLabelFile);
	}
//	system("pause");
	return 0;
}
