function Y = dt(X,dectree)
% function Y = dt(X,dectree)
%
% returns the value(s) that the decision tree dectree evaluates to
%    on the points in X.  
%
% X: n x d
% dectree: as returned by traindt
% Y (return value): n x 1

if (length(dectree)==1)
	Y = ones(size(X,1),1)*dectree(1);
else
	Y = zeros(size(X,1),1);
	d = dectree{1};
	var = d(1);
	thresh = d(2);
	Y(X(:,var)<thresh) = dt(X(X(:,var)<thresh,:),dectree{2});
	Y(X(:,var)>=thresh) = dt(X(X(:,var)>=thresh,:),dectree{3});
end;
