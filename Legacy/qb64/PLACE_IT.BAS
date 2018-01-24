CLS
GOTO 2000
LET n = 0
LET m = 0

1000
CLS
        COLOR 7, 7
        PRINT "      "

        PRINT " ";
        COLOR 4, 4
        PRINT "  ";
        COLOR m, m
        PRINT "  ";
        COLOR 7, 7
        PRINT " "

        PRINT " ";
        COLOR 4, 4
        PRINT "  ";
        COLOR m, m
        PRINT "  ";
        COLOR 7, 7
        PRINT " "

        PRINT "      "
        COLOR 15, 0

PRINT ""
PRINT "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
PRINT "@     Moving     @     Placing    @ Action @"
PRINT "@ a=Left d=Right @ n=Left m=Right @ e=Exit @"
PRINT "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
INPUT "Action"; a$

IF a$ = "e" THEN END
IF a$ = "a" THEN GOTO 1000
IF a$ = "d" AND m = 0 THEN GOTO 2000

IF a$ = "n" THEN GOTO 1000
IF a$ = "m" AND m = 0 THEN GOTO 10
IF a$ = "m" AND m = 1 THEN LET m = 0 ELSE GOTO 1000
GOTO 1000

10
LET m = 1
GOTO 1000


2000
CLS
        COLOR 7, 7
        PRINT "      "

        PRINT " ";
        COLOR n, n
        PRINT "  ";
        COLOR 4, 4
        PRINT "  ";
        COLOR 7, 7
        PRINT " "

        COLOR 7, 7
        PRINT " ";
        COLOR n, n
        PRINT "  ";
        COLOR 4, 4
        PRINT "  ";
        COLOR 7, 7
        PRINT " "

        COLOR 7, 7
        PRINT "      "
        COLOR 15, 0

PRINT ""
PRINT "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
PRINT "@     Moving     @     Placing    @ Action @"
PRINT "@ a=Left d=Right @ n=Left m=Right @ e=Exit @"
PRINT "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
INPUT "Action"; a$

IF a$ = "e" THEN END
IF a$ = "d" THEN GOTO 2000
IF a$ = "a" AND n = 0 THEN GOTO 1000

IF a$ = "m" THEN GOTO 2000
IF a$ = "n" AND n = 0 THEN GOTO 20
IF a$ = "n" AND n = 1 THEN LET n = 0 ELSE GOTO 2000
GOTO 2000

20
LET n = 1
GOTO 2000

