import sys
import Initializer
import Invocation
# Accepting inputs via a command line
with open(sys.argv[1], 'r') as f:
    Initializer.Initializer.create()
    lines = f.readlines()
    for i in range(0, len(lines)):
        params = lines[i].rstrip().split(" ")
        if "ADD_CHILD" == params[0]:
            result = Invocation.add_child(params[1], params[2], params[3])
        if "GET_RELATIONSHIP" == params[0]:
            result = Invocation.get_relationship(params[1], params[2])
        print(result)
quit()


