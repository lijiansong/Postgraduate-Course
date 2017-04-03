function dt = traindtcore(X,Y,alpha,maxdepth,splitfn)
% function dt = traindtw(X,Y,alpha,maxdepth,splitfn)
%
% returns a representation of a decision tree learned on
%        n data points, each with dimension d and a categorical label
%        alpha is the weight of each point
%        maxdepth is the maximum depth of the tree
%        splitfn is a function that picks a split
%            it should be callable as splitfn(X,Y,alpha,isleaf,...)
%               where X,Y,alpha are the subset of the data at this node
%               isleaf is true if it must return a leaf
%               the remaining parameters are the trailing parameters to traindt
%            it should return either
%               1) a single class label (indicating a leaf)
%               2) a pair [dim thresh] indicating that the test is
%                   whether x(dim) < thresh
%   X: n x d
%   Y: n x 1
%   alpha: n x 1
%   maxdepth: 1 x 1
%   splitfn: function / function pointer
%   ...:  remaining args to be passed into splitfn
%
% note: the return value (dt) is a cell array
%       therefore, it should not be placed into a vector, but 
%       must be stored in a cell array if it is to be grouped with
%       other things

split = splitfn(X,Y,alpha,maxdepth<1);
if (length(split)>1) 
	var = split(1);
	thresh = split(2);
	left = traindtcore(X(X(:,var)<thresh,:),Y(X(:,var)<thresh),alpha(X(:,var)<thresh),maxdepth-1,splitfn);
	right = traindtcore(X(X(:,var)>=thresh,:),Y(X(:,var)>=thresh),alpha(X(:,var)>=thresh),maxdepth-1,splitfn);
	dt = {split,left,right};
else
	dt = split;
end;
