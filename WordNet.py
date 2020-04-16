import string
from nltk.corpus import wordnet
import sys

syns = wordnet.synsets(sys.argv[1],wordnet.ADV)
if len(syns) > 0:
    f = open("wordnet output", "w")
    for item in syns:
        print(item.lemmas()[0].name())
        f.write("%s\n" % item.lemmas()[0].name())
    f.close()

