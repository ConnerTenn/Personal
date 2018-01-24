SCREEN 12
LINE (20, 40)-(200, 70), 8, BF
DO
    x = _MOUSEX
    y = _MOUSEY
    DO WHILE _MOUSEINPUT
        IF _MOUSEBUTTON(1) AND x > 20 AND x < 200 THEN
            IF y > 40 AND y < 70 THEN
                END
            END IF
        END IF
    LOOP
    IF x > 20 AND x < 200 AND y > 40 AND y < 70 THEN
        LINE (20, 40)-(200, 70), 7, BF
    ELSE
        LINE (20, 40)-(200, 70), 8, BF
    END IF
LOOP




