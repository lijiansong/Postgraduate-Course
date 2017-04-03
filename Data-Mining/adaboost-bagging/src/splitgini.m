function split = splitgini(X,Y,alpha,isleaf,minnum)

cl = unique(Y);
Ys = repmat(Y,1,length(cl))==repmat(cl',size(Y,1),1);
Ys = Ys.*repmat(alpha,1,length(cl));
[~,split] = max(sum(Ys,1),[],2);
split = cl(split);
if (~isleaf && size(X,1)>minnum && length(cl)>1)
	bestsc = inf;
	bestvar = 0;
	bestth = 0;
	for d=1:size(X,2)
		[sc,th] = splitginid(d,X,Y,alpha,cl);
		if (sc<bestsc)
			bestsc = sc;
			bestvar = d;
			bestth = th;
		end;
	end;
	if (~isinf(bestsc))
		split = [bestvar,bestth];
	end;
end;

function [bsc,th] = splitginid(d,X,Y,alpha,cl)

[Xp,perm] = sort(X(:,d),1);
Yp = Y(perm);
ap = alpha(perm);

csum = repmat(Yp,1,length(cl))==repmat(cl',size(Yp,1),1);
csum = csum.*repmat(ap,1,length(cl));
csum = cumsum(csum,1);
sm = sum(csum,2);
csum2 = bsxfun(@minus,csum(end,:),csum);
sm2 = sum(csum2,2);

sc = sum(bsxfun(@ginihelp,csum,sm),2);
scp = sum(bsxfun(@ginihelp,csum2,sm2),2);
sc = sc + scp;

eq = [Xp(1:end-1)==Xp(2:end); false];
sc(eq) = inf;
[bsc,i] = min(sc);
if (bsc==sc(end))
	bsc = inf;
	th = 0;
else
	th = (Xp(i)+Xp(i+1))/2;
end;

function v = ginihelp(a,b)
	v = a.*(1-a./b);
