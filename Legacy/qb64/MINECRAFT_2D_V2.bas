1

'PreeIntro

CLS

SCREEN 12
DIM x AS INTEGER
DIM y AS INTEGER
DIM A(20000) AS INTEGER
DIM B(20000) AS INTEGER
DIM C(20000, 20000) AS INTEGER
LET G$ = "FALSE"

Block = 2
BlockR = 0
BlockG = 255
BlockB = 0

x = 600
y = 700

W$ = "False"

s = 1

'generation

a = 0
FOR q = 0 TO 200
    a = a + 20
    LET C(200 + a, 780) = 3
NEXT
a = 0
FOR q = 0 TO 200
    a = a + 20
    LET C(200 + a, 760) = 3
NEXT
a = 0
FOR q = 0 TO 200
    a = a + 20
    LET C(200 + a, 740) = 3
NEXT
a = 0
FOR q = 0 TO 200
    a = a + 20
    LET C(200 + a, 720) = 2
NEXT
o = 120
RANDOMIZE TIMER
'FOR u = 0 + 1 TO 15
'   i = INT(RND * 6) + 1
'      IF i = 1 THEN
'      o = o + 300
'      GOSUB RightStep
'   END IF
'   IF i = 2 THEN
'       o = o + 300
'        GOSUB LeftStep
'   END IF
'NEXT
LET C(1200, 600) = 5
LET C(400, 600) = 5

' bottom
FOR a = 200 TO 1980
    LET C(a, 800) = 4
NEXT
'top
FOR a = 200 TO 1980
    LET C(a, 20) = 4
NEXT
'left
FOR a = 20 TO 800
    LET C(200, a) = 4
NEXT
'right
FOR a = 20 TO 800
    LET C(2000, a) = 4
NEXT

DO WHILE C(x, y) = 2 OR C(x, y) = 3
    y = y - 20
LOOP


LINE (0, 0)-(20000, 20000), _RGB(163, 222, 255), BF

' Intro
COLOR 0, 11
PRINT ""
PRINT ""
PRINT "      같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�"
PRINT "      같         W          같                  I                  같"
PRINT "      같       Move         같                Place                같"
PRINT "      같      Foward        같              Block UP               같"
PRINT "      같                    같                                     같"
PRINT "      같   A    S      D    같    J             K            L     같"
PRINT "      같 Move  Move   Move  같  Place         Place        Place   같"
PRINT "      같 Left  Down   Right 같 Block Left  Block Down  Block Right 같"
PRINT "      같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�"
PRINT "             같               같                          같         "
PRINT "             같 P = Quit Game 같  Numbers = Change Block  같         "
PRINT "             같               같                          같         "
PRINT "             같같같같같같같같같같같같같같같같같같같같같같같�         "
PRINT "                     같  Press Space To Continue  같                 "
PRINT "                     같같같같같같같같같같같같같같같�                 "
COLOR 15, 0
DO: KEY$ = UCASE$(INKEY$)
LOOP UNTIL KEY$ = " "

GOSUB graphics

s = 2


DO: KEY$ = UCASE$(INKEY$)

    ' Direction
    IF KEY$ = "W" THEN
        IF C(x, y - 20) = 0 OR C(x, y - 20) = 5 OR C(x, y - 20) = 6 OR C(x, y - 20) = 7 OR C(x, y - 20) = 8 THEN
            IF G$ = "TRUE" THEN
                IF y > 0 THEN
                    LET y = y - 20
                    GOSUB graphics
                END IF
            END IF
        END IF
    END IF
    IF KEY$ = "S" THEN
        IF C(x, y + 20) = 0 OR C(x, y + 20) = 5 OR C(x, y + 20) = 6 OR C(x, y + 20) = 7 OR C(x, y + 20) = 8 THEN
            LET y = y + 20
            GOSUB graphics
        END IF
    END IF
    IF KEY$ = "A" THEN
        IF C(x - 20, y) = 0 OR C(x - 20, y) = 5 OR C(x - 20, y) = 6 OR C(x - 20, y) = 7 OR C(x - 20, y) = 8 THEN
            LET x = x - 20
            GOSUB graphics
        END IF
    END IF
    IF KEY$ = "D" THEN
        IF C(x + 20, y) = 0 OR C(x + 20, y) = 5 OR C(x + 20, y) = 6 OR C(x + 20, y) = 7 OR C(x + 20, y) = 8 THEN
            LET x = x + 20
            GOSUB graphics
        END IF
    END IF
    IF KEY$ = "P" THEN
        CLS
        END
    END IF

    ' Block Selector
    IF KEY$ = "1" THEN
        Block = 2
        BlockR = 0
        BlockG = 255
        BlockB = 0
        GOSUB graphics
    END IF
    IF KEY$ = "2" THEN
        Block = 3
        BlockR = 120
        BlockG = 140
        BlockB = 115
        GOSUB graphics
    END IF
    IF KEY$ = "3" THEN
        Block = 5
        BlockR = 0
        BlockG = 0
        BlockB = 255
        GOSUB graphics
    END IF


    ' Block Place
    IF KEY$ = "I" THEN
        IF C(x, y - 20) = 0 OR C(x, y - 20) = 5 OR C(x, y - 20) = 6 OR C(x, y - 20) = 7 OR C(x, y - 20) = 8 THEN
            LET C(x, y - 20) = Block
            GOSUB graphics
            GOTO 2
        END IF
        IF C(x, y - 20) = 2 OR C(x, y - 20) = 3 THEN
            LET C(x, y - 20) = 0
            GOSUB graphics
            GOTO 2
        END IF
    END IF
    IF KEY$ = "J" THEN
        IF C(x - 20, y) = 0 OR C(x - 20, y) = 5 OR C(x - 20, y) = 6 OR C(x - 20, y) = 7 OR C(x - 20, y) = 8 THEN
            LET C(x - 20, y) = Block
            GOSUB graphics
            GOTO 2
        END IF
        IF C(x - 20, y) = 2 OR C(x - 20, y) = 3 THEN
            LET C(x - 20, y) = 0
            GOSUB graphics
            GOTO 2
        END IF
    END IF
    IF KEY$ = "K" THEN
        IF C(x, y + 20) = 0 OR C(x, y + 20) = 5 OR C(x, y + 20) = 6 OR C(x, y + 20) = 7 OR C(x, y + 20) = 8 THEN
            LET C(x, y + 20) = Block
            GOSUB graphics
            GOTO 2
        END IF
        IF C(x, y + 20) = 2 OR C(x, y + 20) = 3 THEN
            LET C(x, y + 20) = 0
            GOSUB graphics
            GOTO 2
        END IF
    END IF
    IF KEY$ = "L" THEN
        IF C(x + 20, y) = 0 OR C(x + 20, y) = 5 OR C(x + 20, y) = 6 OR C(x + 20, y) = 7 OR C(x + 20, y) = 8 THEN
            LET C(x + 20, y) = Block
            GOSUB graphics
            GOTO 2
        END IF
        IF C(x + 20, y) = 2 OR C(x + 20, y) = 3 THEN
            LET C(x + 20, y) = 0
            GOSUB graphics
            GOTO 2
        END IF
    END IF

    2
    ' Fall
    IF fall < 150 THEN
        IF G$ = "FALSE" THEN
            fall = fall + 1
        END IF
    END IF
    IF C(x, y + 20) = 2 OR C(x, y + 20) = 3 OR C(x, y + 20) = 4 OR C(x, y + 20) = 5 OR C(x, y + 20) = 6 OR C(x, y + 20) = 7 OR C(x, y + 20) = 8 THEN
        LET G$ = "TRUE"
    END IF
    IF C(x, y + 20) = 0 THEN
        LET G$ = "FALSE"
    END IF
    IF fall >= 150 THEN
        IF G$ = "FALSE" THEN
            LET y = y + 20
            LET fall = 0
            GOSUB graphics
        END IF
    END IF

    ' Water Physics
    IF Wfall < 121 THEN
        Wfall = Wfall + 1
    END IF


    W = 0
    IF Wfall >= 120 THEN
        FOR a = 0 TO 4000 STEP 20
            FOR b = 0 TO 1400 STEP 20
                IF C(a, b) = 5 OR C(a, b) = 6 THEN
                    IF C(a, b + 20) = 2 OR C(a, b + 20) = 3 OR C(a, b + 20) = 4 THEN 'Source or flow with block below
                        IF C(a - 20, b) = 0 THEN
                            LET C(a - 20, b) = 11
                            W = 1
                        END IF
                        IF C(a + 20, b) = 0 THEN
                            LET C(a + 20, b) = 11
                            W = 1
                        END IF
                    END IF
                    IF C(a, b + 20) = 0 OR C(a, b + 20) = 7 OR C(a, b + 20) = 8 THEN 'source or flow with empty beneth
                        LET C(a, b + 20) = 10
                        W = 1
                    END IF
                END IF
                IF C(a, b) = 6 THEN ' Destroy Flow Block
                    IF C(a, b - 20) = 2 OR C(a, b - 20) = 3 OR C(a, b - 20) = 0 THEN
                        LET C(a, b) = 13
                        W = 1
                    END IF
                END IF
                IF C(a, b) = 7 THEN
                    IF C(a, b + 20) = 2 OR C(a, b + 20) = 3 OR C(a, b + 20) = 4 THEN 'spread1 with block below
                        IF C(a - 20, b) = 0 THEN
                            LET C(a - 20, b) = 12
                            W = 1
                        END IF
                        IF C(a + 20, b) = 0 THEN
                            LET C(a + 20, b) = 12
                            W = 1
                        END IF
                    END IF
                    IF C(a, b + 20) = 0 THEN 'spread1 with empty beneth
                        LET C(a, b + 20) = 10
                        W = 1
                    END IF
                END IF
                IF C(a, b) = 7 THEN ' Destroy Spread1
                    IF (C(a + 20, b) = 0 OR C(a + 20, b) = 2 OR C(a + 20, b) = 3 OR C(a + 20, b) = 4 OR C(a + 20, b) = 7 OR C(a + 20, b) = 8) AND (C(a - 20, b) = 0 OR C(a - 20, b) = 2 OR C(a - 20, b) = 3 OR C(a - 20, b) = 4 OR C(a - 20, b) = 7 OR C(a - 20, b) = 8) THEN
                        LET C(a, b) = 13
                        W = 1
                    END IF
                END IF
                IF C(a, b) = 8 THEN
                    IF C(a, b + 20) = 0 THEN 'spread2 with empty beneth
                        LET C(a, b + 20) = 10
                        W = 1
                    END IF
                END IF
                IF C(a, b) = 8 THEN ' Destroy Spread2
                    IF (C(a + 20, b) = 0 OR C(a + 20, b) = 2 OR C(a + 20, b) = 3 OR C(a + 20, b) = 4 OR C(a + 20, b) = 6 OR C(a + 20, b) = 8) AND (C(a - 20, b) = 0 OR C(a - 20, b) = 2 OR C(a - 20, b) = 3 OR C(a - 20, b) = 4 OR C(a - 20, b) = 6 OR C(a - 20, b) = 8) THEN
                        LET C(a, b) = 13
                        W = 1
                    END IF
                END IF
            NEXT
        NEXT
        Wfall = 0
        W$ = "False"
        FOR a = 0 TO 4000 STEP 20
            FOR b = 0 TO 1400 STEP 20
                IF C(a, b) = 9 THEN
                    LET C(a, b) = 5
                END IF
                IF C(a, b) = 10 THEN
                    LET C(a, b) = 6
                END IF
                IF C(a, b) = 11 THEN
                    LET C(a, b) = 7
                END IF
                IF C(a, b) = 12 THEN
                    LET C(a, b) = 8
                END IF
                IF C(a, b) = 13 THEN
                    LET C(a, b) = 0
                END IF
            NEXT
        NEXT
        IF W = 1 THEN
            GOSUB graphics
        END IF
    END IF



    _DELAY 0.0001
LOOP

graphics:
'
' Block ID: 0 = Air
' Block ID: 1 = Player
' Block ID: 2 = Green Block
' Block ID: 3 = Brown Block
' Block ID: 4 = Black Block
' Block ID: 5 = Water Source
' Block ID: 6 = Water Flow
' Block ID: 7 = Water Spread 1
' Block ID: 8 = Water Spread 2
' Block ID: 9 = Ghost Water Source
' Block ID: 10 = Ghost Water Flow
' Block ID: 11 = Ghost Water Spread 1
' Block ID: 12 = Ghost Water Spread 2
' Block ID: 13 = Ghost Air
'
CLS
LINE (0, 0)-(20000, 20000), _RGB(163, 222, 255), BF
IF s = 2 THEN
    COLOR 0, 11
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT ""
    PRINT "X="; x; ", Y="; y; "    Ground="; G$
    COLOR 15, 0
END IF

LINE (40, 40)-(38, 222), _RGB(0, 0, 0), BF ' Left
LINE (420, 40)-(422, 222), _RGB(0, 0, 0), BF ' Right
LINE (38, 40)-(422, 38), _RGB(0, 0, 0), BF ' Top
LINE (38, 220)-(422, 222), _RGB(0, 0, 0), BF ' Bottom

FOR a = 0 + 40 TO 400 STEP 20
    FOR b = 0 + 40 TO 200 STEP 20
        IF C(a + x - 200, b + y - 100) = 2 THEN
            GOSUB Green
        END IF
        IF C(a + x - 200, b + y - 100) = 3 THEN
            GOSUB Brown
        END IF
        IF C(a + x - 200, b + y - 100) = 4 THEN
            GOSUB Black
        END IF
        IF C(a + x - 200, b + y - 100) = 5 THEN
            GOSUB WSource
        END IF
        IF C(a + x - 200, b + y - 100) = 6 THEN
            GOSUB WFlow
        END IF
        IF C(a + x - 200, b + y - 100) = 7 THEN
            GOSUB WSpread1
        END IF
        IF C(a + x - 200, b + y - 100) = 8 THEN
            GOSUB WSpread2
        END IF
    NEXT
NEXT

LINE (270, 420)-(320, 470), _RGB(BlockR, BlockG, BlockB), BF
LINE (200, 100)-(200 + 20, 100 + 20), _RGB(255, 0, 0), BF
RETURN

Green:
LINE (a, b)-(a + 20, b + 20), _RGB(0, 255, 0), BF
RETURN

Brown:
LINE (a, b)-(a + 20, b + 20), _RGB(120, 140, 115), BF
RETURN

Black:
LINE (a, b)-(a + 20, b + 20), _RGB(0, 0, 0), BF
RETURN

WSource:
LINE (a, b)-(a + 20, b + 20), _RGB(0, 0, 255), BF
RETURN

WFlow:
LINE (a, b)-(a + 20, b + 20), _RGB(50, 50, 255), BF
RETURN

WSpread1:
LINE (a, b + 6)-(a + 20, b + 20), _RGB(50, 50, 255), BF
RETURN

WSpread2:
LINE (a, b + 12)-(a + 20, b + 20), _RGB(50, 50, 255), BF
RETURN

'Gen
RightStep:
t = 0
FOR q = 0 + 1 TO 5
    t = t + 20
    C(o - t, p) = 2
NEXT
t = 0
FOR q = 0 + 1 TO 4
    t = t + 20
    C(o - t, p - 20) = 2
NEXT
t = 0
FOR q = 0 + 1 TO 3
    t = t + 20
    C(o - t, p - 40) = 2
NEXT
t = 0
FOR q = 0 + 1 TO 2
    t = t + 20
    C(o - t, p - 60) = 2
NEXT
RETURN

LeftStep:
t = 0
FOR q = 0 + 1 TO 5
    t = t + 20
    C(o + t, p) = 2
NEXT
t = 0
FOR q = 0 + 1 TO 4
    t = t + 20
    C(o + t, p - 20) = 2
NEXT
t = 0
FOR q = 0 + 1 TO 3
    t = t + 20
    C(o + t, p - 40) = 2
NEXT
t = 0
FOR q = 0 + 1 TO 2
    t = t + 20
    C(o + t, p - 60) = 2
NEXT
RETURN


