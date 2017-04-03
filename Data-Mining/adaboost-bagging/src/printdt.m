function printdt(tree)
% function printdt(tree)
%
% displays a tree in the format returned by traindt

printdthelp(tree,'','','');

function printdthelp(tree,lstem,cstem,rstem)
if (length(tree)==1)
	disp(sprintf('%s--[y = %d]',cstem,tree(1)));
else
	d = tree{1};
	add = sprintf('--[x(%d) < %g]-+',d(1),d(2));
	b = blanks(length(add)-1);
	pre = sprintf('%s%s|',lstem,b);
	curr = sprintf('%s%s/',lstem,b);
	post = sprintf('%s%s ',lstem,b);
	printdthelp(tree{2},post,curr,pre);
	d = tree{1};
	disp([lstem b 'Y']);
	disp([cstem add]);
	disp([rstem b 'N']);
	pre = sprintf('%s%s|',rstem,b);
	curr = sprintf('%s%s\\',rstem,b);
	post = sprintf('%s%s ',rstem,b);
	printdthelp(tree{3},pre,curr,post);
end;
