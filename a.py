
filename = "md5.h"

f = open(filename, "r")

string = f.read()

string = string.replace("ROR", "md5_ROR")
string = string.replace("ROL", "md5_ROL")

f = open(filename, "w")

f.write(string)



print(string)




