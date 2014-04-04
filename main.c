#include    <stdio.h>
#define eprint(fmt,...) printf(fmt"\n",##__VA_ARGS__)
#include    "z.h"
void (*test_test(void))(void){
    return $(void,(void){printf("000000\n");});
}
int main(void){
    FILE *fd;
    int len;
    fd = try(NULL == ,fopen("l","w"),
            {
                perror("Open l");
                throw(e_open);
            });
    len = try(0 >= ,fwrite("hello",1,5,fd),
            {
                perror("Write \"hello\" to l");
                throw(e_write);
            });
    
    len = try(0 >= ,fwrite(" world",1,7,fd),
            {
                perror("Write \" world\" to l");
                throw(e_write1);
            });


    $(void,(void){printf("hello world\n");})();
    test_test()();

    if(and(1 <,2,3,4,5,6,-1)){
        printf("H\n");
    }
    try(0 == ,and(1<,2,3,4,5,or(0 >,-1,-2),6,-1));

    return 0;
    catch(e_write,e_write1){
        fclose(fd);
    }catch(e_open){
    }
    return -1;
}
