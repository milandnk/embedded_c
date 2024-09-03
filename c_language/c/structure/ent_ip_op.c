#include<stdio.h>
struct student{
    int roll;
    float cga;
    int name;
};

void printInfo(struct student s1){
    printf("%d\n",s1.roll);
    printf("%f\n",s1.cga);
    printf("%s\n",s1.name);

    s1.roll = 500;
    
}
int main(){
    struct student s[5];
    


  
return 0;
}
