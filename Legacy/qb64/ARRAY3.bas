DIM x AS INTEGER
DIM y AS INTEGER
DIM S(1000) AS INTEGER
DIM R(1000) AS INTEGER
DIM C(1000, 1000) AS INTEGER

1
CLS
INPUT "1=Enter new value  2=Recall  3=Exit"; question
CLS
IF question = 1 THEN
    GOSUB Enter
END IF
IF question = 2 THEN
    GOSUB Recall
END IF
IF question = 3 THEN
    END
END IF
GOTO 1

Enter:
INPUT "X"; a
INPUT "Y"; b
INPUT "Value"; C
S(a) = C
R(b) = C
C(x, y) = S(x)
C(x, y) = R(y)
RETURN

Recall:
INPUT "Recall X"; x
INPUT "Recall Y"; y
C(x, y) = S(x)
C(x, y) = R(y)
PRINT C(x, y)
PRINT ""
PRINT "Press 'a' To Continue"
DO
LOOP UNTIL INKEY$ = "a"
RETURN
