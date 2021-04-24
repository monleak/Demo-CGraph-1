#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgraph/cgraph.h"
#include "cgraph/cgraph_error.h"
typedef struct _Dinh
{
	int ID;
	char data[100];
}Dinh;

int create_test(cgraph_t *g,Dinh *A,int n,int mode) 
{
  cgraph_ivec_t edges = cgraph_ivec_create();
  int ret=0;
  for (CGRAPH_INTEGER i = 0; i < 2*n; ++i) 
  {
    ret += cgraph_ivec_push_back(&edges, (CGRAPH_INTEGER)A[i].ID);
  }
  if (ret) 
  {
    CGRAPH_ERROR("Can not create a vector");
    cgraph_ivec_free(&edges);
    return 3;
  }
  if(mode==1) return cgraph_create(g, edges, 0, true); //có hướng
  if(mode==2) return cgraph_create(g, edges, 0, false);  //vô hướng
}
void print_neis_out(cgraph_t *g, int id,Dinh *A,int n)
{
	cgraph_ivec_t neis = cgraph_ivec_create();
	cgraph_neighbors(g,&neis,(CGRAPH_INTEGER)id,CGRAPH_OUT);
	for (CGRAPH_INTEGER i = 0; i < cgraph_ivec_size(neis); ++i)
	{
    	for(int j=0;j<2*n;j++)
    	{
    		if(neis[i]==A[j].ID)
    		{
    			printf("%s ", A[j].data);
    			break;
    		}
    	}
    }
  	printf("\n");
  	cgraph_ivec_free(&neis);
}
int main()
{
	FILE *input = fopen("../input.txt","r");
	int canh,cohuong;
	fscanf(input,"%d %d\n",&canh,&cohuong);
	Dinh *A = (Dinh*)calloc(2*canh,sizeof(Dinh));
	int ID[100]={0};
	// char A[2*canh][100]={0};
	int kiemtra=0;
	for(int i=0;i<2*canh;i++)
	{
		fscanf(input," %s ",A[i].data);
		for(int j=0;j<i;j++)
		{
			if(strcmp(A[i].data,A[j].data)==0&&A[j].ID!=0)
			{
				A[i].ID=A[j].ID;
				kiemtra=1;
			}
		}
		if(kiemtra==0) A[i].ID=i+1;
		kiemtra=0;
	}
	cgraph_t B;
	int err = create_test(&B,A,canh,cohuong);
	if(err!=0)
	{
		printf("ERROR!\n");
		return 1;
	}
	char u[100];
	printf("Nhap ten dinh: ");scanf(" %s",u); // " %s" de tranh dau \n
	int _id=0;
	// for(int i=0;i<2*canh;i++)
	// {
	// 	if(strcmp(A[i].data,u)==0) _id=A[i].ID;
	// }
	int checkid=-1;
	do
	{
		checkid++;
		if(checkid==2*canh) break;
	}while(strcmp(A[checkid].data,u)!=0);
	if(checkid!=2*canh)
	{
		_id=A[checkid].ID;
		print_neis_out(&B,_id,A,canh); //danh sach dinh ke theo chieu di ra
	}
	else printf("Du lieu nhap vao khong phu hop\n");
	cgraph_destroy(&B);
	fclose(input);
	return 0;
}