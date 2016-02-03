#! /usr/bin/python3
import sys
# BEGIN USAGE
usage = 'srcfile_example.py value'
# END USAGE
if len(sys.argv) != 2 :
	sys.exit(usage)
value  = float( sys.argv[1] )
square = value * value
output = 'value * value = ' + str(square)
print(output)
