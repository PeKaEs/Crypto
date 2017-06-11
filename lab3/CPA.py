import subprocess
import os

bytesCount = 0
IV = []
IV3 = []
IV2=""
IVlist = []

with open("CPAtarget.txt.en", "rb") as f:
    byte = f.read(1)
    while (byte != "" and bytesCount < 16):
        #print byte
        IV.append(str(byte))

        byte = f.read(1)
        bytesCount = bytesCount + 1



#print IV
#IV[15] = chr(ord(IV[15])+1)
IVlist = IV
IV2="".join(IV)
#print IV2

IV2 = "-pIV "+IV2
IVlist[15] = chr(ord(IVlist[15])+1)
#print IV



#subprocess.call(["./encode ", "-f CPAtest.txt ", "-c legitKeyStore ", "-k first ", "-m cfb ", "-p keystore ", IV2], shell=True)
#trig = "./encode "+ "-f CPAtest.txt "+ "-c legitKeyStore " + "-k first " + "-m cfb " + "-p keystore " + IV2
#os.system(trig)
#./encode -f CPAtarget.txt -c legitKeyStore -k first -m cfb -p keystore -pIV aaaaaaaaaaaaaaaa

bytesCount = 0

with open("CPAtest.txt", "rb") as f:
    byte = f.read(1)
    while byte != "":
        print byte
        IV3.append(str(byte))
        byte = f.read(1)
        bytesCount = bytesCount + 1

bytesCount = 0
print IV3
print IVlist

for i in range(16):
    IV3[i] = chr(ord(IV3[i]) ^ ord(IVlist[i]))

choosenPlain = "".join(IV3)

with open("CPAtest_choosen.txt", "wb") as f:
    f.write(choosenPlain)
    bytesCount = bytesCount + 1

trig = "./encode "+ "-f CPAtest_choosen.txt "+ "-c legitKeyStore " + "-k first " + "-m cfb " + "-p keystore " + IV2
os.system(trig)

with open("CPAtest_choosen.txt.en", "rb") as f:
    choosenEncStr = f.read()

with open("CPAtarget.txt.en", "rb") as f:
    targentEncStr = f.read()

print choosenEncStr
print targentEncStr

if choosenEncStr != targentEncStr :
    print "Content of CPAtest.txt wasnt a messesage in CPAtarget.txt"
else:
    print "Content of CPAtest.txt is equal to the messesage in CPAtarget.txt"
