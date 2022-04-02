file = open("data.csv")
data = file.readlines()
output = ""
for i in data:
    output += "{"
    for x in i.split(";"):
        cellData = str(x).replace("\n", "").replace(",", ".")
        output += cellData
        if not '\n' in x:
            output += ", "
    output += "},\n"
print(output)
