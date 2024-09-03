#include<stdio.h>

struct student{
    int roll;
    float cga;
    int name;

};

int main(){
     struct student s1 = {5,3.2,"milan"};

     printf("%s\n",s1.name);

     struct student *ptr = &s1;
     printf("%d\n",(*ptr).roll);
     
    
     printf("%d\n",ptr->roll);//arrow using ptr
    
return 0;
}