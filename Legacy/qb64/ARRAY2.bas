DIM x AS INTEGER
DIM y AS INTEGER
DIM S(1000) AS INTEGER
DIM R(1000) AS INTEGER


INPUT "X"; a
INPUT "Y"; b
INPUT "Value"; c
S(a) = c
R(b) = c
C(x, y) = S(x)
C(x, y) = R(y)
INPUT "X"; a
INPUT "Y"; b
INPUT "Value"; c
S(a) = c
R(b) = c
C(x, y) = S(x)
C(x, y) = R(y)

INPUT "Recall X"; x
INPUT "Recall Y"; y
C(x, y) = S(x)
C(x, y) = R(y)

PRINT C(x, y)

