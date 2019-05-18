void merge(int *x,int aw,int mid,int ak){ 
	int *z = new int[ak+1];
	int i,j,k,l; 
	i=aw; 
	j=mid+1; 
	k=aw; 
	do{ 
		if(x[i]<=x[j]){
			z[k]=x[i];
			i++;
		}else{
			z[k]=x[j];
			j++;
		} 
		k++;
	}while((i<=mid) && (j<=ak)); 
	
	if(i>mid){
		for(l=j;l<=ak;l++){
			z[k]=x[l];
			k++;
		}
	}else{
		for(l=i;l<=mid;l++){
			z[k]=x[l];
			k++;
		}
	}
	for(k=aw;k<=ak;k++) 
			x[k]=z[k];
	delete[] z;
	z = NULL;
}

void mergesort(int *x,int aw,int ak){ 
	int mid;
	if(aw<ak){
		mid =(aw+ak)/2; 
		mergesort(x,aw,mid); 
		mergesort(x,mid+1,ak); 
		merge(x,aw,mid,ak); 
	} 
}