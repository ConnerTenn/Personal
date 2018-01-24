SCREEN 12
1
INPUT "Speed (1-3)"; s
IF s = 1 THEN
    LET s = 0.01
ELSE IF s = 2 THEN
        LET s = 0.006
    ELSE IF s = 3 THEN
            LET s = 0.004 ELSE GOTO 1
        END IF
    END IF
END IF



2
direction$ = "up_right"
x = 300
y = 150



LET paddle1Y = 200
LET paddle2Y = 200

DO: K$ = UCASE$(INKEY$)
    IF K$ = "W" AND paddle1Y > 60 THEN
        IF direction$ = "up_left" OR direction$ = "down_left" THEN
            LET paddle1Y = paddle1Y - 10
        END IF
    END IF
    IF K$ = "S" AND paddle1Y < 460 THEN
        IF direction$ = "up_left" OR direction$ = "down_left" THEN
            LET paddle1Y = paddle1Y + 10
        END IF
    END IF
    IF K$ = "O" AND paddle2Y > 60 THEN
        IF direction$ = "up_right" OR direction$ = "down_right" THEN
            LET paddle2Y = paddle2Y - 10
        END IF
    END IF
    IF K$ = "L" AND paddle2Y < 460 THEN
        IF direction$ = "up_right" OR direction$ = "down_right" THEN
            LET paddle2Y = paddle2Y + 10
        END IF

    END IF

    _DELAY s
    T = T + 0.005

    IF direction$ = "up_left" THEN
        GOSUB up_left
    END IF
    IF direction$ = "up_right" THEN
        GOSUB up_right
    END IF
    IF direction$ = "down_left" THEN
        GOSUB down_left
    END IF
    IF direction$ = "down_right" THEN
        GOSUB down_right
    END IF

    IF y >= 460 THEN
        IF direction$ = "down_left" THEN
            LET direction$ = "up_left"
        END IF
        IF direction$ = "down_right" THEN
            LET direction$ = "up_right"
        END IF
    END IF
    IF y <= 20 THEN
        IF direction$ = "up_left" THEN
            LET direction$ = "down_left"
        END IF
        IF direction$ = "up_right" THEN
            LET direction$ = "down_right"
        END IF
    END IF
    IF x = 610 THEN
        FOR q = 0 + 1 TO 50
            IF paddle2Y - q = y THEN
                IF direction$ = "up_right" THEN
                    LET direction$ = "up_left"
                END IF
                IF direction$ = "down_right" THEN
                    LET direction$ = "down_left"
                END IF
            END IF
        NEXT
    END IF
    IF x = 10 THEN
        FOR q = 0 + 1 TO 50
            IF paddle1Y - q = y THEN
                IF direction$ = "up_left" THEN
                    LET direction$ = "up_right"
                END IF
                IF direction$ = "down_left" THEN
                    LET direction$ = "down_right"
                END IF
            END IF
        NEXT
    END IF
    IF x < 0 THEN
        score2 = score2 + 1
        _DELAY 1
        GOTO 2
    END IF
    IF x > 625 THEN
        score1 = score1 + 1
        _DELAY 1
        GOTO 2
    END IF
    IF score1 >= 6 OR score2 >= 6 THEN
        GOTO 3
    END IF

    CLS
    PRINT "Player1 Score="; score1; "   Player2 Score="; score2; "   "; T
    CIRCLE (x, y), 5
    LINE (5, paddle1Y)-(0, paddle1Y - 50), 15, BF
    LINE (615, paddle2Y)-(620, paddle2Y - 50), 15, BF
LOOP

3
END

up_left:
LET x = x - 1
LET y = y - 1
RETURN

up_right:
LET x = x + 1
LET y = y - 1
RETURN

down_left:
LET x = x - 1
LET y = y + 1
RETURN

down_right:
LET x = x + 1
LET y = y + 1
RETURN












