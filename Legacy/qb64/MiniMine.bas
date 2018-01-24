1
SCREEN 9
DIM x AS INTEGER
DIM y AS INTEGER
DIM S(1000) AS INTEGER
DIM R(1000) AS INTEGER
DIM C(1000, 1000) AS INTEGER
INPUT "X"; a
INPUT "Y"; b
INPUT "Value"; C
S(a) = C
R(b) = C
C(x, y) = S(x)
C(x, y) = R(y)
y = 30
x = 10
2
PRINT "X:"; x / 10; " Y:"; (y - 20) / 10;
INPUT "Direction"; q$
IF q$ = "" THEN
    END
END IF
IF q$ = "w" THEN
    IF y > 30 THEN
        LET o = x
        LET p = y
        C(x, y) = S(x)
        C(x, y) = R(y)
        IF C(o, p - 10) = 0 THEN
            LET y = y - 10
        END IF
    END IF
END IF
IF q$ = "s" THEN
    IF y < 60 THEN
        LET o = x
        LET p = y
        C(o, p) = S(o)
        C(o, p) = R(p)
        IF C(o, p + 10) = 0 THEN
            LET y = y + 10
        END IF
    END IF
END IF
IF q$ = "a" THEN
    IF x > 10 THEN
        LET o = x
        LET p = y
        C(o, p) = S(o)
        C(o, p) = R(p)
        IF C(o - 10, p) = 0 THEN
            LET x = x - 10
        END IF
    END IF
END IF
IF q$ = "d" THEN
    IF x < 60 THEN
        LET o = x
        LET p = y
        C(o, p) = S(o)
        C(o, p) = R(p)
        IF C(o + 10, p) = 0 THEN
            LET x = x + 10
        END IF
    END IF
END IF
CLS
FOR o = 0 + 10 TO 60
    FOR p = 0 + 10 TO 40
        C(o, p) = S(o)
        C(o, p) = R(p)
        IF C(o, p) = 1 THEN
            PRINT C(o, p);
            CIRCLE (x, y), 10, _RGB(0, 255, 0)
        END IF
    NEXT
NEXT
CIRCLE (x, y), 5, _RGB(255, 0, 0)
GOTO 2






