function f = Factorial(n)
%FACTORIAL of a positive integer
% $begin Factorial.m$$ $newlinech %$$
% $spell 
%	Matlab
% $$
%
% $section Compute Factorial of an Integer Scalar$$
%
% $table
% $bold Syntax$$
% $syntax%Factorial(%n%)%$$
% $tend
%
% $head Description$$
% Returns the value
% $math%
%	n * (n-1) * ... * 2 * 1
% %$$
% where $italic n$$ is a positive integer.
%
% $head Example$$
% If you execute the command 
% $codep
%	Factorial(3)
% $$
% Matlab will reply
% $codep
%	6
% $$
%
% $end
if ( n == 1 )
	f = 1;
else
   f = n * Factorial(n-1);
end
