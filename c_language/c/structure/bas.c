#include<stdio.h>
struct student{
    int roll;
    float cga;
    int name;

};
int main(){
    struct student s1 = {5,3.2,"milan"};
    struct student s2 = {6,6,"jay"};
    printf("%d\n",s1.roll);
    printf("%s\n",s1.name);

  
return 0;
}
