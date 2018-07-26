// Written by Jansen Malem (z5141970)

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "textbuffer.h"

//void whiteBoxTest(void);

int main(int argc, char *argv[]) {
    //whiteBoxTest();

    printf("Black Box Test\n");
    TB new = newTB("This\nis\na\nblack\nbox\ntest\n");
    char *str = dumpTB(new);
    printf("Original Text : \n%s\n", str);

    // Test 1 swapTB and linesTB
    printf("Test 1 : SwapTB and linesTB\n");
    assert(linesTB(new) == 6);
    printf("Swapping the first and last nodes\n");
    swapTB(new, 0, 5);
    char *str1 = dumpTB(new);
    printf("After Swap : \n%s\n",str1);
    printf("Swapping the second and third nodes\n");
    swapTB(new, 2, 3);
    char *str1_2 = dumpTB(new);
    printf("After Swap : \n%s\n", str1_2);
    assert(linesTB(new) == 6);

    // Test 2 mergeTB
    printf("Test 2 : mergeTB\n");
    TB new2 = newTB("T\n");
    TB new2_1 = newTB("E\n");
    TB new2_2 = newTB("S\nT\n");
    TB new2_3 = newTB("EST\n");
    mergeTB(new2, 1, new2_1);
    char *str2 = dumpTB(new2);
    printf("After first merge : \n%s\n",str2);
    mergeTB(new2, 2, new2_2);
    char *str2_1 = dumpTB(new2);
    printf("After second merge : \n%s\n", str2_1);
    mergeTB(new2, 4, new2_3);
    char *str2_2 = dumpTB(new2);
    printf("After third merge : \n%s\n", str2_2);

    // Test 3 pasteTB
    TB new3 = newTB("Paste this\n");
    TB new3_1 = newTB("then print\n");
    TB new3_2 = newTB("this\n");
    pasteTB(new3, 1, new3_1);
    char *str3 = dumpTB(new3);
    printf("After first merge: \n%s\n", str3);
    char *str3_1 = dumpTB(new3_1);
    printf("the text buffer :( %s\n) remains untouched\n", str3_1);
    assert(linesTB(new3) == 2);
    assert(linesTB(new3_1) == 1);

    pasteTB(new3, 2, new3_2);
    assert(linesTB(new3) == 3);
    assert(linesTB(new3_2) == 1);

    char *str3_2 = dumpTB(new3_2);
    printf("the text buffer :( %s\n) remains untouched\n", str3_2);

    // Test 4 cutTB
    TB new4 = newTB("Cut\nthis\nlong\ntext\nplease\n");
    TB new4_1 = cutTB(new4, 1, 3);
    assert(linesTB(new4_1) == 3);
    char *str4 = dumpTB(new4_1);
    printf("After first cut: \n%s\n", str4);

    TB new4_2 = cutTB(new4, 1, 1);
    assert(linesTB(new4_2) == 1);
    char *str4_1 = dumpTB(new4_2);
    printf("After second cut: \n%s\n", str4_1);

    TB new4_3 = cutTB(new4, 0, 0);
    assert(linesTB(new4_3) == 1);
    char *str4_2 = dumpTB(new4_3);
    printf("After third cut: \n%s\n", str4_2);


    // Test 5 copyTB
    TB new5 = newTB("To\nbe\ncopied\n");
    TB new5_1 = copyTB(new5, 0, 2);
    char *str5 = dumpTB(new5_1);
    printf("After copying everything to new textbuffer: \n%s\n", str5);
    assert(linesTB(new5) == 3);
    assert(linesTB(new5_1) == 3);

    TB new5_2 = newTB("mini-test\n");
    TB new5_3 = copyTB(new5_2, 0, 0);

    printf("after\n");
    char *str5_1 = dumpTB(new5_3);
    printf("before\n");

    printf("After copying everything to new textbuffer: \n%s\n",str5_1);
    assert(linesTB(new5_2)==1);
    assert(linesTB(new5_3)==1);

    // Test 6 deleteTB
    TB new6 = newTB("To\nbe\ndeleted\nin\nthe\nnext\nmoment\n");
    deleteTB(new6, 0, 0);
    char *str6 = dumpTB(new6);
    printf("After deletion of the first element: \n%s\n", str6);

    deleteTB(new6, 0, 1);
    char *str6_1 = dumpTB(new6);
    printf("After deletion of the first two element: \n%s\n", str6_1);
    deleteTB(new6, 0, 2);
    char *str6_2 = dumpTB(new6);
    printf("After deletion of the first two element: \n%s\n", str6_2);

    // Test 7 replaceText
    TB new7 = newTB("Heyeyey\neye\nwhey\nprey\nhey\n");
    char *str7 = dumpTB(new7);
    printf("Original text :\n%s\n",str7);

    replaceText(new7, "ey", "ha");
    char *str7_1 = dumpTB(new7);
    printf("after replacing ey with ha text :\n%s\n", str7_1);

    replaceText(new7, "ha", "po");
    char *str7_2 = dumpTB(new7);
    printf("after replacing ha with po text :\n%s\n", str7_2);


    free(str);
    free(str1);
    free(str1_2);

    free(str2);
    free(str2_1);
    free(str2_2);

    free(str3);
    free(str3_1);
    free(str3_2);

    free(str4);
    free(str4_1);
    free(str4_2);

    free(str5);
    free(str5_1);

    free(str6);
    free(str6_1);
    free(str6_2);

    free(str7);
    free(str7_1);
    free(str7_2);

    releaseTB(new);
    releaseTB(new2);
    releaseTB(new3);
    releaseTB(new3_1);
    releaseTB(new3_2);
    releaseTB(new4);
    releaseTB(new4_1);
    releaseTB(new4_2);
    releaseTB(new4_3);
    releaseTB(new5);
    releaseTB(new5_1);
    releaseTB(new5_2);
    releaseTB(new5_3);
    releaseTB(new6);
    releaseTB(new7);

    printf("All BlackBox Test passed\n");
    return EXIT_SUCCESS;
}
