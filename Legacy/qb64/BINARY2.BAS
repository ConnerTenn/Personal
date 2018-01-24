1
SLEEP 1
x = x + 1
q$ = HEX$(x)

LET r = LEN(q$)
IF r = 1 OR r = 2 OR r = 3 OR r = 4 OR r = 5 OR r = 6 OR r = 7 THEN
        LET aa$ = RIGHT$(q$, r)
        LET a$ = LEFT$(aa$, 1)
END IF
IF r = 2 OR r = 3 OR r = 4 OR r = 5 OR r = 6 OR r = 7 THEN
        LET bb$ = RIGHT$(q$, r - 1)
        LET b$ = LEFT$(bb$, 1)
END IF
IF r = 3 OR r = 4 OR r = 5 OR r = 6 OR r = 7 THEN
        LET cc$ = RIGHT$(q$, r - 2)
        LET c$ = LEFT$(cc$, 1)
END IF
IF r = 4 OR r = 5 OR r = 6 OR r = 7 THEN
        LET dd$ = RIGHT$(q$, r - 3)
        LET d$ = LEFT$(dd$, 1)
END IF
IF r = 5 OR r = 6 OR r = 7 THEN
        LET ee$ = RIGHT$(q$, r - 4)
        LET e$ = LEFT$(ee$, 1)
END IF
IF r = 6 OR r = 7 THEN
        LET ff$ = RIGHT$(q$, r - 5)
        LET f$ = LEFT$(ff$, 1)
END IF
IF r = 7 THEN
        LET gg$ = RIGHT$(q$, r - 6)
        LET g$ = LEFT$(gg$, 1)
END IF



IF a$ = 1 THEN
        LET zaa = 1
        ELSEIF a$ = 2 THEN
                LET zaa = 0
                LET zab = 1
                ELSEIF a$ = 3 THEN
                        LET zaa = 1
                        LET zab = 1
                        ELSEIF a$ = 4 THEN
                                LET zaa = 0
                                LET zab = 0
                                LET zac = 1
                                ELSEIF a$ = 5 THEN
                                        LET zaa = 1
                                        LET zab = 0
                                        LET zac = 1
                                        ELSEIF a$ = 6 THEN
                                                LET zaa = 0
                                                LET zab = 1
                                                LET zac = 1
                                                ELSEIF a$ = 7 THEN
                                                        LET zaa = 1
                                                        LET zab = 1
                                                        LET zac = 1
                                                        ELSEIF a$ = 8 THEN
                                                                LET zaa = 0
                                                                LET zab = 0
                                                                LET zac = 0


                                            
                                              
























