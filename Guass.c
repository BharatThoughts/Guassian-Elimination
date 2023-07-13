#include<stdio.h>
#include <stdlib.h>
float **Exchange(float **x,int t_row,int i_row,int n){
	int i;float temp;
	for(i=0;i<=n;i++){
		temp=*(*(x+i_row)+i);
		*(*(x+i_row)+i)=*(*(x+t_row)+i);
		*(*(x+t_row)+i)=temp;
	}
	return x;
}
float **Eliminate(float **x,int i_row,int t_row,float m,int n){int i;
	for(i=i_row;i<=n;i++){
		*(*(x+t_row)+i)=*(*(x+t_row)+i)-*(*(x+i_row)+i)*m;
	}
	return x;
}
float **upper_triangular(float **x,int n){int i,d,g_row,row,j;float m,g=*x[0];
	for(i=0;i<n;i++){
		g=*(x[i]+i);
		g_row=i;
		
		//find greatest row of x1,x2...xn and storing in g_row //
		    for(d=i;d<n;d++){
		    	if(*(*(x+d)+i)>g){
		    		g=*(*(x+d)+i);
		    		g_row=d;
				}
			}
			
		//--- done with greatest row---//
		//Exchange g_row with i//
		    if(g_row!=i){
		    	x=Exchange(x,g_row,i,n);
			}
		//--- done with Exchanging rows---//
		//Elimination of xi//
		    for(row=(i+1);row<n;row++){
		    	m=(float)*(*(x+row)+i)/x[i][i];
		    	//printf("%f\n",(float)*(*(x+row)+i)/x[i][i]);
		    	x=Eliminate(x,i,row,m,n);
			}
		//---done with Elimination---//
		
	}
	if(*(*(x+(n-1))+(n-1))==0||(x[n-1][n-1]<0&&x[n-1][n-1]>-0.99)){
		if(x[n-1][n]==0){
			printf("INFINITE SOLUTION");
		}
		else{
			printf("NO SOLUTION");
		}
		exit(0);
	}
	return x;
}
void Back_substitution(float **m,int n,float x[n]){int i,j;float sum=0;
	for(i=(n-1);i>=0;i--){
		for(j=(i+1);j<n;j++){
			sum+=*(*(m+i)+j)*x[j];
		}
		x[i]=(*(*(m+i)+n)-sum)/m[i][i];
		
		sum=0;
	}
	return;
}
void print_output(int n,float *x){int i;
	for(i=0;i<n;i++){
		printf("%f\n",*(x+i));
	}
	return;
}
//Book2.csv
int main(){
	FILE *f;
	char c,filename[50];int n,i=0,j=0,k,tens=1;
	printf("ENTER FILENAME: ");
	scanf("%s",&filename);
	printf("ENTER n: ");
	scanf("%i",&n);
	float **x,*S;
	
	x=(float **)malloc(n*sizeof(float *));
	for(k=0;k<n;k++){
		*(x+k)=(float *)malloc((n+1)*sizeof(float));
	}
	f=fopen(filename,"r");
	
	//--erorr message for not opening file--
	
	if(f==NULL){
		printf("\nError: File Name does not exist");
		free(x);
		return 0;
	}
	//----error message end -----//
    
    //---- reading input augmented matrix------//
	c=fgetc(f);
    //printf("%c\n",c);
	while(!feof(f)){
		if(c!=','&&c!='\n'){
			while(c!=','&&c!='\n'){
			
			if(c=='-'){
				c=fgetc(f);
				x[j][i]=(float)(-(c-'0')*tens);
				//printf("c=%c\n",c);
				//printf("x[j][i]=%i\n",x[j][i]);
			}
			else{
			    x[j][i]=(float)(c-'0')*tens;
			}
			c=fgetc(f);
			//printf("x[j][i]=%i\n",x[j][i]);
			while(c!=','&&c!='\n'){
				//printf("c=%c\n",c);
				//printf("%f\n",x[j][i]*10);
				if (c == '.') {
					c = fgetc(f);
					tens = tens * 10;
					x[j][i]=(x[j][i]>0)?x[j][i] + (float)(c - '0') / tens : x[j][i]-(float)(c-'0')/tens;
					c = fgetc(f);
					while (c != ',' && c != '\n') {
						tens = tens * 10;
					    x[j][i]=(x[j][i]>0)?x[j][i] + (float)(c - '0') / tens : x[j][i]-(float)(c-'0')/tens;
						c = fgetc(f);
					}
					tens = 1;
					break;
				}
		        x[j][i]=(x[j][i]>0)?x[j][i]*10+(float)(c-'0'):x[j][i]*10-(float)(c-'0');
		        
		        c=fgetc(f);
			}
			i++;
			j=(i==(n+1))?j+1:j;
			i=(i==(n+1))?0:i;
		    
			tens=tens*10;
			
			//printf("%c",c);
		    }
		}
		tens=1;
	    c=fgetc(f);
	    //printf("c=%c\n",c);
    }
    //--- End of Reading Matrix---//
    //Conversion to upper triangular matrix//
    x=upper_triangular(x,n);
    
    //--- Done with upper triangular matrix//
    //Back substitution for solutions//
    S=(float *)calloc(n,sizeof(float));
    Back_substitution(x,n,S);
    //---Done with Back substituting//
    //Print the output//
    printf("SOLUTION OF THE EQUATIONS ARE:\n");
    print_output(n,S);
    //--Done with output--//
	free(x);
	free(S); 
	fclose(f);
	return 0;
}
