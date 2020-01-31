#! /usr/bin/python3
# $begin src_example.py$$ $newlinech #$$ $escape $$
# $spell srcthisfile src py$$
# $section Example Python Source File$$
# $head Usage$$
# $srcthisfile%0%# BEGIN USAGE%# END USAGE%2%$$
# $head Discussion$$
# Note the $code srcthisfile$$ command skips the first two
# $code # BEGIN USAGE$$ in $code src_example.py$$.
# $end
import sys
# BEGIN USAGE
usage = 'src_example.py value'
# END USAGE
if len(sys.argv) != 2 :
	sys.exit(usage)
value  = float( sys.argv[1] )
square = value * value
output = 'value * value = ' + str(square)
print(output)
