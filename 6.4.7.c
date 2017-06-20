#include <string.h>           
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct OWN{  
	float data;
	struct OWN *next;
}OWN;

typedef struct{    
	OWN *beg;
	OWN *end;
	OWN *cur;
}LOWL;

LOWL *lowl_create_empty(void){						
	LOWL *list;
	list= NULL;
	
	if(( list=malloc(sizeof(LOWL)))==NULL){
		return 0;
	}
		
	list->cur=NULL;
	list->beg=NULL;
	return list;
}

LOWL *lowl_create_random(unsigned int size){				
  	int i;
	OWN *uzol;				
  	LOWL *list;					
  	
  	uzol=NULL;
  	if(( uzol=malloc(sizeof(OWN)))==NULL) 
	  return NULL;
  	uzol->data=rand()%10;
  	uzol->next=NULL;
	  	
  	list=NULL;
  	list=malloc(sizeof(LOWL));
  	list->beg=uzol;
  	list->cur=uzol;
  	
   for(i=1; i<size; i++){	
    	if(( uzol=malloc(sizeof(OWN)))==NULL) 
			return NULL;
    	
	    uzol->data=rand()%10;
	    uzol->next=NULL;											
	    
	    list->cur->next=uzol ;
		list->cur=list->cur->next;
	}
	
	list->cur = list->beg;
	
	return list;
}


void *lowl_destroy(LOWL *list){						
	OWN *p;
	
	list->cur = list->beg;
	
	while(list->cur->next != NULL){
		p = list->cur->next;
		free(list->cur);
		list->cur = p;
	}
	free(list->cur);
	free(list);
}

void lowl_print(LOWL *list){
	OWN *p;
	
	for(p=list->beg; p != NULL; p=p->next){
		if(p == list->cur)
		printf("(%d) ",p->data);
		else{
			printf("%d ",p->data);
		}
	}
		printf("\n ");
}

char lowl_cur_step_left(LOWL *list){
	OWN *a, *b;
	
	if (list->cur==list->beg)
	return BOUNDARY_REACHED;
	
	if(list->cur->next != NULL){
		for(b=list->cur,a=list->cur->next; a!=list->cur;b=a,a=a->next){
			if(a->next==NULL){
				b=a;
				a=list->beg;
			}	
		}					// v b je predchadzajuci
		return LOWL_SUCCESS;
	}
	
	if(list->cur->next==NULL){
		for(a=list->cur,b=list->beg; b!=list->cur; a=b,b=b->next){	
 		}
 		list->cur = a;
 		return LOWL_SUCCESS;
	}
}

char lowl_cur_step_right(LOWL *list){
				
	if(list->cur->next==NULL)
	return BOUNDARY_REACHED;
	 
		else{
			list->cur=list->cur->next;
			return LOWL_SUCCESS;	
	}	 
}


OWN *lowl_insert_left(LOWL* list, float val){	
	OWN *a, *b, *c, *d;

	if(list->cur==list->beg){													
		if( (list->cur==NULL) && (list->beg==NULL)){
			a->data=val;	
			list->cur=a;
			list->beg=list->cur;
			list->beg->next=NULL;
			return a;
		}
		
		b=list->beg;	
		a->data=val;
	
		a->next=b;
		list->beg=a;
		list->cur=b;
		return a;	
	}
	
	if(list->cur !=list->beg){				
		d=list->cur;	
		lowl_cur_step_left(list);
		
		list->cur->next->data=val;
		c=list->cur->next;
		list->cur=d;
		c->next=d;
		return c;
	}
		
}

OWN *lowl_insert_right(LOWL* list, float val){	
	OWN *a, *b;
	
	if( (list->cur->next==NULL) && (list->cur==list->beg)){			
		a->data=val;
		list->cur->next=a;
		a->next=NULL;
		return a;
	}
	
	else{
		b=list->cur->next;
		a->data=val;
		list->cur->next=a;
		a->next=b;
		return a;		
	}

	return a;	
}


int lowl_delete(LOWL* list){					
	int data;
	OWN *a, *b; 
	
	data=list->cur->data;
	a=list->cur; 
	
	if( (list->cur->next==NULL) && (list->cur==list->beg) ){
		free(a);
		list->cur=NULL;
		return data;
	}
	
	if(list->cur==list->beg){												
		list->beg=list->cur->next;
		list->cur=list->beg;
		free(a);
		
		return data;
	}
	
	if(list->cur->next !=NULL){	
		lowl_cur_step_left(list);
		b=list->cur;
		list->cur=a->next;
		b->next=list->cur;
		free(a);											
		
		return data;	
	}
	
	if(list->cur->next==NULL){		
		lowl_cur_step_left(list);
		b=list->cur;
		list->cur=b;
		b->next=NULL;
		free(a);
		
		return data;
	}	 
	
}


void lowl_inversion(LOWL *list){
	OWN *a, *b;
	int i;

	
	for(a=list->beg; a !=NULL;a=a->next){
	a->next=a-sizeof(float);
	}
	
	b=list->end;
	list->end=list->beg;
	list->beg=b;
	
	return list;
}


int main(){	
	srand(time(NULL));
	LOWL *list;
	unsigned int size = 8;

	list = lowl_create_random(size);
	printf("zoznam:");
	lowl_print(list);
	if (list == NULL)
	printf("Chyba");
	
	printf("obrateny:");
	lowl_inversion(list);
	lowl_print(list);
	
	return 0;
}







