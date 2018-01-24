SCREEN 12
1
direction$ = "up_right"
x = 300
y = 150
angle = 1


LET paddle1Y = 200
LET paddle2Y = 200

DO: K$ = UCASE$(INKEY$)
    IF K$ = "W" AND paddle1Y > 60 THEN
        LET paddle1Y = paddle1Y - 10
    END IF
    IF K$ = "S" AND paddle1Y < 305 THEN
        LET paddle1Y = paddle1Y + 10
    END IF
    IF K$ = "O" AND paddle2Y > 60 THEN
        LET paddle2Y = paddle2Y - 10
    END IF
    IF K$ = "L" AND paddle2Y < 305 THEN
        LET paddle2Y = paddle2Y + 10
    END IF

    _DELAY 0.009
    T = T + 0.009

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

    IF y >= 300 THEN
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
    IF x = 10 OR x = 9 OR x = 8 THEN
        FOR q = 0 + 1 TO 60
            IF paddle1Y - q = y THEN
                FOR w = 0 + 1 TO 30
                    IF y = (paddle1Y - 30) - w THEN
                        LET direction$ = "up_right"
                        LET angle = w / 6
                    END IF
                    IF y = (paddle1Y - 30) + w THEN
                        LET direction$ = "down_right"
                        LET angle = w / 6
                    END IF
                    IF y = (paddle1Y - 30) THEN
                        LET direction$ = "up_right"
                        LET angle = 0
                    END IF
                NEXT
            END IF
        NEXT
    END IF
    IF x = 610 OR x = 611 OR x = 612 THEN
        FOR q = 0 + 1 TO 60
            IF paddle2Y - q = y THEN
                FOR w = 0 + 1 TO 30
                    IF y = (paddle2Y - 30) - w THEN
                        LET direction$ = "up_left"
                        LET angle = w / 6
                    END IF
                    IF y = (paddle2Y - 30) + w THEN
                        LET direction$ = "down_left"
                        LET angle = w / 6
                    END IF
                    IF y = (paddle2Y - 30) THEN
                        LET direction$ = "up_left"
                        LET angle = 0
                    END IF
                NEXT
            END IF
        NEXT
    END IF
    IF x < 0 THEN
        score2 = score2 + 1
        _DELAY 1
        GOTO 1
    END IF
    IF x > 625 THEN
        score1 = score1 + 1
        _DELAY 1
        GOTO 1
    END IF
    IF score1 >= 6 OR score2 >= 6 THEN
        GOTO 2
    END IF

    CLS
    PRINT "Player1 Score="; score1; "   Player2 Score="; score2; "   "; T
    CIRCLE (x, y), 5
    LINE (5, paddle1Y)-(0, paddle1Y - 60), 15, BF
    LINE (615, paddle2Y)-(620, paddle2Y - 60), 15, BF
    LINE (0, 306)-(1000, 306), 15
LOOP

2
END

up_left:
LET x = x - 1
LET y = y - angle
RETURN

up_right:
LET x = x + 1
LET y = y - angle
RETURN

down_left:
LET x = x - 1
LET y = y + angle
RETURN

down_right:
LET x = x + 1
LET y = y + angle
RETURN












