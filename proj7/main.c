#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct Block{
    int used;
    int start;
    int end;
    char name[5];
}block;

typedef struct Node{
   block* hole;
   struct Node* next;
   struct Node* pre;
}node;

node* head;
node* tail;
/* allocate memory for certain process in certain memory blocks*/
void insert_process(node* , int,char*);  
/* traverse the whole memory and output*/
void traverse();  
/* this function will generate a new array with new head and tail based on the original mem*/
void compact(); 
/*free all the dynamic allocated memory*/
void free_all();
/*init linked list*/
void init();
/*release process into unused blocks*/
void release_process(node*);
/*merge the contiguous unused blocks*/
void merge_left(node*);
void merge_right(node*);
void merge_two_sides(node*);

int max_size;




int main(int argc, char* argv[]){
    assert(argc == 2);
    max_size = atoi(argv[1]);
    init();
    traverse();
    /*init the linked list*/


    return 0;
}

void init(){
    head  = (node*) malloc(sizeof(node));
    tail = (node*) malloc(sizeof(node));
    node* fisrt_block;
    node *first_block = (node*) malloc(sizeof(node));
    block* tmp;
    tmp = (block*)malloc(sizeof(block));
    tmp -> start = 0;
    tmp -> end = max_size - 1;
    tmp -> used = 0;
    first_block -> hole = tmp;
    first_block -> pre = head;
    first_block -> next = tail;
    head -> next = first_block;
    head -> pre = NULL;
    tail -> next = NULL;
    tail -> pre = first_block;
}

void insert_process(node* insblock, int process_size, char*name){
    //l (proc) ins r 
    node* proc = (node*) malloc(sizeof(node));
    proc -> hole -> used = 1;
    proc -> hole -> start = insblock -> hole -> start;
    proc -> hole -> end = proc -> hole -> start + process_size;
    proc -> hole -> name = name;
    node* l  = insblock -> pre;
    l -> next = proc;
    proc -> pre = l;
    proc -> next = insblock;
    insblock -> pre = proc;
    insblock -> hole -> start = proc -> hole -> end + 1;
    if(insblock -> hole -> start == insblock -> hole -> end){
        // remove the hole
        node*r = insblock -> next;
        proc -> next = r;
        r -> pre = proc;
        free(insblock -> hole);
        free(insblock);  
    }
    return 0;
}

void release_process(node* proc){
    // l - proc -left
    proc -> hole -> used = 0;
    int l,r;
    l = (proc -> pre -> hole -> used == 0) && (proc -> pre != head);
    r = (proc -> next -> hole -> used == 0) && (proc -> pre != tail);
    if(l && r){
        merge_two_sides(proc);
        return;
    }
    else if(l){
        merge_left(proc);
        return;
    }
    else{
        merge_right(proc);
        return;
    }
}

void merge_left(node* s){
      // a - left - s - b;
      // assume that before this operation, s is unused
      node*a = s -> pre -> pre;
      node* left = s -> pre;
      int size_left;
      s -> hole -> start = s -> pre -> hole -> start;
      a -> next = s;
      s -> pre = a;
      free(left -> hole);
      free(left); 
      return 0;
}

void merge_right(node* s){
    // a - s - right
    node* right = s -> next;
    node* a = s -> pre;
    right -> hole -> start = s -> hole -> start;
    a -> next = right;
    right -> pre = a;
    free(s -> hole);
    free(s);
    return 0;
}

void merge_twosides(node* s){
    // a-l-s-r-b 
    node*l = s -> pre;
    node*r = s -> next;
    node*a = l -> pre;
    node*b = r -> next;
    
    s -> hole -> start = l -> hole -> start;
    s -> hole -> end = r -> hole -> end;
    a -> next = s;
    s -> pre = a;
    s -> next = b;
    b -> pre = s;
    
    free(l -> hole);
    free(l);
    free(r -> hole);
    free(r);
}


/*different fit strategies, return 0 is successfully, else -1*/

int worstFit(int process_size){
    // find the largest hole;
    int max_hole_size = -1;
    node*tmp = head -> next;
    while(tmp != tail){
       if(tmp -> hole -> used){
           tmp = tmp -> next;
       }else{
           int hole_size = tmp -> hole -> start - tmp -> hole -> end;
           max_hole_size = (hole_size > max_hole_size) ? hole_size : max_hole_size;
           tmp = tmp -> next;
       }
    }
    tmp = head -> next;
    if(max_hole_size + 1 < process_size) return -1;
    while(1){
         if(tmp -> hole -> used){
           tmp = tmp -> next;
         }else{
           int hole_size = tmp -> hole -> start - tmp -> hole -> end;
           if(hole_size == max_hole_size){
               insert_process(tmp, process_size);
               break;
           }
           tmp = tmp -> next;
       }
    }
    return 0;

}

int bestFit(int process_size){
    int min_fit_hole_size = -1;
    node*tmp = head -> next;
    while(tmp != tail){
       if(tmp -> hole -> used){
           tmp = tmp -> next;
           continue;
       }
       int hole_size = tmp -> hole -> start - tmp -> hole -> end + 1;
       if(hole_size < process_size){
           tmp = tmp -> next;
           continue;
       }
       else{
           min_fit_hole_size = (hole_size < min_fit_hole_size) ? hole_size : min_fit_hole_size;
           tmp = tmp -> next;
       }
    }

    tmp = head -> next;
    if(min_fit_hole_size == -1) return -1;
    while(1){
         if(tmp -> hole -> used){
           tmp = tmp -> next;
         }else{
           int hole_size = tmp -> hole -> start - tmp -> hole -> end;
           if(hole_size == min_fit_hole_size){
               insert_process(tmp, process_size);
               break;
           }
           tmp = tmp -> next;
       }
    }
    return 0;
}

int firstFit(int process_size){
    node*tmp = head -> next;
    while(tmp != tail){
        if(tmp -> hole -> used){
           tmp = tmp -> next;
         }else{
           int hole_size = tmp -> hole -> start - tmp -> hole -> end;
           if(hole_size >= process_size){
                insert_process(tmp, process_size);
                return 0;
           }else{
                tmp = tmp -> next;
                continue;
           }
         }
    }

    return -1;
}

void compact(){
    /*to do*/
    node*new_head;
    node*new_tail;
    node*tmp = head -> next;
    int free_size;
    

}

void traverse(){
    node* tmp = head;
    tmp = tmp -> next;
    while(tmp != tail){
        if(tmp -> hole -> used){
            printf("Mem[%d]-[%d], [%s]\n", tmp -> hole -> start, tmp -> hole -> end, tmp -> hole -> name);
        }else{
            printf("Mem[%d]-[%d], unused\n", tmp -> hole -> start, tmp -> hole -> end);
        }
        tmp = tmp -> next;
    }
}
