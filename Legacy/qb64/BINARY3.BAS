1
LET x = x + 1
IF x = 1 AND zaa = 0 THEN
        LET zaa = 1
        GOTO 2
END IF
IF x = 2 AND zab = 0 THEN
        LET zab = 1
        LET zaa = 0
        GOTO 2
        ELSEIF x = 2 OR x = 3 THEN
        LET zaa = 0
END IF
IF x = 3 AND zac = 0 THEN
        zab = 1
        LET zab = 0
        GOTO 2
        ELSEIF x = 3 THEN
                LET zab = 0
END IF




       



2

SLEEP 1
        
press$ = INKEY$
IF press$ = "a" THEN
        END
END IF




CLS
PRINT zaa; zab; zac; zad; zae; zaf; zag; zah
PRINT zai; zaj; zak; zal; zam; zan; zao; zap
PRINT zaq; zar; zas; zat; zau; zav; zaw; zax
PRINT zay; zaz; zba; zbb; zbc; zbd; zbe; zbf
PRINT zbg; zbh; zbi; zbj; zbk; zbl; zbm; zbn
PRINT zbo; zbp; zbq; zbr; zbs; zbt; zbu; zbv
PRINT zbw; zbx; zby; zbz; zca; zcb; zcc; zcd
PRINT zce; zcf; zcg; zch; zci; zcj; zck; zcl
GOTO 1



