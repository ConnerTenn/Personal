
'   1   2   3   4   5   6   7   8
'
'1 zaa zab zac zad zae zaf zag zah
'
'2 zai zaj zak zal zam zan zao zap
'
'3 zaq zar zas zat zau zav zaw zax
'
'4 zay zaz zba zbb zbc zbd zbe zbf
'
'5 zbg zbh zbi zbj zbk zbl zbm zbn
'
'6 zbo zbp zbq zbr zbs zbt zbu zbv
'
'7 zbw zbx zby zbz zca zcb zcc zcd
'
'8 zce zcf zcg zch zci zcj zck zcl



CLS
1
RANDOMIZE TIMER
zaa = INT(RND * 2)
zab = INT(RND * 2)
zac = INT(RND * 2)
zad = INT(RND * 2)
zae = INT(RND * 2)
zaf = INT(RND * 2)
zag = INT(RND * 2)
zah = INT(RND * 2)
zai = INT(RND * 2)
zaj = INT(RND * 2)
zak = INT(RND * 2)
zal = INT(RND * 2)
zam = INT(RND * 2)
zan = INT(RND * 2)
zao = INT(RND * 2)
zap = INT(RND * 2)
zaq = INT(RND * 2)
zar = INT(RND * 2)
zas = INT(RND * 2)
zat = INT(RND * 2)
zau = INT(RND * 2)
zav = INT(RND * 2)
zaw = INT(RND * 2)
zax = INT(RND * 2)
zay = INT(RND * 2)
zaz = INT(RND * 2)
zba = INT(RND * 2)
zbb = INT(RND * 2)
zbc = INT(RND * 2)
zbd = INT(RND * 2)
zbe = INT(RND * 2)
zbf = INT(RND * 2)
zbg = INT(RND * 2)
zbh = INT(RND * 2)
zbi = INT(RND * 2)
zbj = INT(RND * 2)
zbk = INT(RND * 2)
zbl = INT(RND * 2)
zbm = INT(RND * 2)
zbn = INT(RND * 2)
zbo = INT(RND * 2)
zbp = INT(RND * 2)
zbq = INT(RND * 2)
zbr = INT(RND * 2)
zbs = INT(RND * 2)
zbt = INT(RND * 2)
zbu = INT(RND * 2)
zbv = INT(RND * 2)
zbw = INT(RND * 2)
zbx = INT(RND * 2)
zby = INT(RND * 2)
zbz = INT(RND * 2)
zca = INT(RND * 2)
zcb = INT(RND * 2)
zcc = INT(RND * 2)
zcd = INT(RND * 2)
zce = INT(RND * 2)
zcf = INT(RND * 2)
zcg = INT(RND * 2)
zch = INT(RND * 2)
zci = INT(RND * 2)
zcj = INT(RND * 2)
zck = INT(RND * 2)
zcl = INT(RND * 2)

press$ = INKEY$
IF press$ = "a" THEN
        END
END IF

LET z = z + 1

'==============================================================

10
IF zaa + zab + zac + zad + zae + zaf + zag + zah = 1 THEN
        GOTO 20
        ELSE GOTO 1
END IF

20
IF zai + zaj + zak + zal + zam + zan + zao + zap = 1 THEN
        GOTO 30
        ELSE GOTO 1
END IF

30
IF zaq + zar + zas + zat + zau + zav + zaw + zax = 1 THEN
         GOTO 40
         ELSE GOTO 1
END IF

40
IF zay + zaz + zba + zbb + zbc + zbd + zbe + zbf = 1 THEN
        GOTO 50
        ELSE GOTO 1
END IF

50
IF zbg + zbh + zbi + zbj + zbk + zbl + zbm + zbn = 1 THEN
        GOTO 60
        ELSE GOTO 1
END IF

60
IF zbo + zbp + zbq + zbr + zbs + zbt + zbu + zbv = 1 THEN
        GOTO 70
        ELSE GOTO 1
END IF

70
IF zbw + zbx + zby + zbz + zca + zcb + zcc + zcd = 1 THEN
        GOTO 80
        ELSE GOTO 1
END IF

80
IF zce + zcf + zcg + zch + zci + zcj + zck + zcl = 1 THEN
        GOTO 100
        ELSE GOTO 1
END IF
 
'===============================================================

100
IF zaa + zai + zaq + zay + zbg + zbo + zbw + zce = 1 THEN
        GOTO 200
        ELSE GOTO 1
END IF

200
IF zab + zaj + zar + zaz + zbh + zbp + zbx + zcf = 1 THEN
        GOTO 300
        ELSE GOTO 1
END IF

300
IF zac + zak + zas + zba + zbi + zbq + zby + zcg = 1 THEN
        GOTO 400
        ELSE GOTO 1
END IF

400
IF zad + zal + zat + zbb + zbj + zbr + zbz + zch = 1 THEN
        GOTO 500
        ELSE GOTO 1
END IF

500
IF zae + zam + zau + zbc + zbk + zbs + zca + zci = 1 THEN
        GOTO 600
        ELSE GOTO 1
END IF

600
IF zaf + zan + zav + zbd + zbl + zbt + zcb + zcj = 1 THEN
        GOTO 700
        ELSE GOTO 1
END IF

700
IF zag + zao + zaw + zbe + zbm + zbu + zcc + zck = 1 THEN
        GOTO 800
        ELSE GOTO 1
END IF

800
IF zah + zap + zax + zbf + zbn + zbv + zcd + zcl = 1 THEN
        GOTO 1000
        ELSE GOTO 1
END IF

'=====================================================================

1000
IF zaa > 2 THEN
        GOTO 1
        ELSE GOTO 1500
END IF

1500
IF zab + zai > 2 THEN
        GOTO 1
        ELSE GOTO 2000
END IF

2000
IF zac + zaj + zaq > 2 THEN
        GOTO 1
        ELSE GOTO 2500
END IF

2500
IF zad + zak + zar + zay > 2 THEN
        GOTO 1
        ELSE GOTO 3000
END IF

3000
IF zae + zal + zas + aza + abg > 2 THEN
        GOTO 1
        ELSE GOTO 3500
END IF

3500
IF zaf + zam + zat + zba + zbh + zbo > 2 THEN
        GOTO 1
        ELSE GOTO 4000
END IF

4000
IF zag + zan + zau + zbb + zbi + zbp + zbw > 2 THEN
        GOTO 1
        ELSE GOTO 4500
END IF

4500
IF zah + zao + zav + zbc + zbj + zbq + zbx + zce > 2 THEN
        GOTO 1
        ELSE GOTO 5000
END IF

5000
IF zap + zaw + zbd + zbk + zbr + zby + zcf > 2 THEN
        GOTO 1
        ELSE GOTO 5500
END IF

5500
IF zax + zbe + zbl + zbs + zbz + zcg > 2 THEN
        GOTO 1
        ELSE GOTO 6000
END IF

6000
IF zbf + zbm + zbt + zca + zch > 2 THEN
        GOTO 1
        ELSE GOTO 6500
END IF

6500
IF zbn + zbu + zcb + zci > 2 THEN
        GOTO 1
        ELSE GOTO 7000
END IF

7000
IF zbv + zcc + zcj > 2 THEN
        GOTO 1
        ELSE GOTO 7500
END IF

7500
IF zcd + zck > 2 THEN
        GOTO 1
        ELSE GOTO 8000
END IF

8000
IF zcl > 2 THEN
        GOTO 10000
        ELSE GOTO 1
END IF

'=====================================================================

10000
IF zah > 2 THEN
        GOTO 1
        ELSE GOTO 15000
END IF

15000
IF zag + zap > 2 THEN
        GOTO 1
        ELSE GOTO 20000
END IF

20000
IF zaf + zao + zax > 2 THEN
        GOTO 1
        ELSE GOTO 25000
END IF

25000
IF zae + zan + zaw + zbf > 2 THEN
        GOTO 1
        ELSE GOTO 30000
END IF

30000
IF zad + zam + zav + abe + abn > 2 THEN
        GOTO 1
        ELSE GOTO 35000
END IF

35000
IF zac + zal + zau + zad + zbm + zbv > 2 THEN
        GOTO 1
        ELSE GOTO 40000
END IF

40000
IF zab + zak + zat + zbc + zbl + zbu + zcd > 2 THEN
        GOTO 1
        ELSE GOTO 45000
END IF

45000
IF zaa + zaj + zas + zbb + zbk + zbt + zcc + zcl > 2 THEN
        GOTO 1
        ELSE GOTO 50000
END IF

50000
IF zai + zar + zba + zbj + zbs + zcb + zck > 2 THEN
        GOTO 1
        ELSE GOTO 55000
END IF

55000
IF zaq + zaz + zbi + zbr + zca + zcj > 2 THEN
        GOTO 1
        ELSE GOTO 60000
END IF

60000
IF zay + zbh + zbq + zbz + zci > 2 THEN
        GOTO 1
        ELSE GOTO 65000
END IF

65000
IF zbg + zbp + zby + zch > 2 THEN
        GOTO 1
        ELSE GOTO 70000
END IF

70000
IF zbo + zbx + zcg > 2 THEN
        GOTO 1
        ELSE GOTO 75000
END IF

75000
IF zbw + zcf > 2 THEN
        GOTO 1
        ELSE GOTO 80000
END IF

80000
IF zce > 2 THEN
        GOTO 100000
        ELSE GOTO 1
END IF













100000
PRINT zaa; zab; zac; zad; zae; zaf; zag; zah
PRINT zai; zaj; zak; zal; zam; zan; zao; zap
PRINT zaq; zar; zas; zat; zau; zav; zaw; zax
PRINT zay; zaz; zba; zbb; zbc; zbd; zbe; zbf
PRINT zbg; zbh; zbi; zbj; zbk; zbl; zbm; zbn
PRINT zbo; zbp; zbq; zbr; zbs; zbt; zbu; zbv
PRINT zbw; zbx; zby; zbz; zca; zcb; zcc; zcd
PRINT zce; zcf; zcg; zch; zci; zcj; zck; zcl

PRINT "trials:"; z


