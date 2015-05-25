inf = open("timeLog.txt", "r");
outf = open("data.csv", "w");
x = inf.readlines();
arr = []
for i in x:
    a, b = i.split(', ')
    a = int(a)
    b = float(b)
    arr += [[a, b]]
arr = sorted(arr)
outf.write("operations, time\n" + "\n".join(map(lambda x: str(x[0]) + ", " + ("%.10f" % x[1]), arr)))
outf.close()
