word = str(raw_input("Input Word: "))
allowed = "IOSHZXN"
good = True
bad = "Bad Letters: "

for char in word:
    if char not in allowed:
        good = False
        bad = bad + char + " "
if (good):
    print "YES"
else:
    print "NO"
    print bad
    
