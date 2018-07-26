#include <stdio.h>
#include <stdlib.h>

char *monthName (int month) {
    char *result;
    switch (month) {
        case 1: result = "Jan\n"; break;
        case 2: result = "Feb\n"; break;
        case 3: result = "Mar\n"; break;
        case 4: result = "Apr\n"; break;
        case 5: result = "May\n"; break;
        case 6: result = "Jun\n"; break;
        case 7: result = "Jul\n"; break;
        case 8: result = "Aug\n"; break;
        case 9: result = "Sept\n"; break;
        case 10: result = "Oct\n"; break;
        case 11: result = "Nov\n"; break;
        case 12: result = "Dec\n"; break;
        default : result = "Invalid\n";
    }
    return result; 
}
