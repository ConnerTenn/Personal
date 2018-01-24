SCREEN 12
DIM x AS INTEGER
DIM y AS INTEGER
DIM G AS STRING
DIM A(10000) AS INTEGER
DIM B(10000) AS INTEGER
DIM C(10000, 10000) AS INTEGER
LET G = "FALSE"

FOR A = 0 + 1 TO 1000
    LET C(A, 400) = 2
NEXT
LET C(300, 390) = 2


DO: KEY$ = UCASE$(INKEY$)
    IF KEY$ = "W" THEN
        IF C(x, y - 10) = 0 THEN
            IF y > 0 THEN
                LET y = y - 10
                GOSUB Graphics
            END IF
        END IF
    END IF
    IF KEY$ = "A" THEN
        IF C(x - 10, y) = 0 THEN
            IF x > 0 THEN
                LET x = x - 10
                GOSUB Graphics
            END IF
        END IF
    END IF
    IF KEY$ = "D" THEN
        IF C(x + 10, y) = 0 THEN
            IF x < 600 THEN
                LET x = x + 10
                GOSUB Graphics
            END IF
        END IF
    END IF
    IF KEY$ = "P" THEN
        CLS
        END
    END IF
    '                                           FIX FLIP FLOP

    IF KEY$ = "I" THEN
        IF y < 10 THEN
            IF C(x, y - 10) = 0 THEN
                LET C(x, y - 10) = 2
            END IF
            IF C(x, y - 10) = 2 THEN
                LET C(x, y - 10) = 0
            END IF
        END IF
    END IF
    IF KEY$ = "J" THEN
        IF C(x - 10, y) = 0 THEN
            LET C(x - 10, y) = 2
        END IF
        IF C(x - 10, y) = 2 THEN
            LET C(x - 10, y) = 0
        END IF
    END IF
    IF KEY$ = "L" THEN
        IF C(x + 10, y) = 0 THEN
            LET C(x + 10, y) = 2
        END IF
        IF C(x + 10, y) = 2 THEN
            LET C(x + 10, y) = 0
        END IF
    END IF

    fall = fall + 1
    IF C(x, y + 10) = 2 THEN
        LET G = "TRUE"
    END IF
    IF C(x, y + 10) = 0 THEN
        LET G = "FALSE"
    END IF
    IF fall >= 10 THEN
        IF G = "FALSE" THEN
            LET y = y + 10
            LET fall = 0
        END IF
    END IF

    _DELAY 0.0001
    GOSUB Graphics
LOOP

Graphics:
CLS
PRINT G
FOR A = 0 + 1 TO 1000
    FOR B = 0 + 1 TO 1000
        IF C(A, B) = 2 THEN
            LINE (A, B)-(A + 10, B + 10), _RGB(0, 255, 0), BF
        END IF
    NEXT
NEXT
LINE (x, y)-(x + 10, y + 10), _RGB(255, 0, 0), BF
RETURN

