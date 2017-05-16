from os import listdir
from os.path import isfile, join

baseString ="bbattery_FIPS_140_2File (\""

onlyfiles = [f for f in listdir("RC4_NN_drop") if isfile(join("RC4_NN_drop", f))]

for i in onlyfiles:
    print baseString+i+"\");"
