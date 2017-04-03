function adaboost()
%Adaboost
    clc;
    I = load('class2d.ascii','-ascii');
    X = I(:,1:2);   %80x2
    Y = I(:,3);     %80x1
    trees = [1,10,100,1000];
    tr = cell(1000,3);
    wt = zeros(1000,1);
    err = zeros(1000,1);
    %Boosting
    for d = 1:3
        alpha  = ones(80,1);
        for i = 1:4
            f = 4*(d-1)+i;
            figure(f)
            remain = 1;
            if i >1
                remain = trees(i) - trees(i-1);
            end
            for sz = 1:remain
                t = traindtw(X,Y,alpha,d);
                if i > 1
                    tr(trees(i-1) + sz,:) = t;
                    err(trees(i-1) + sz) = classification_error(X,Y,t,1,alpha);
                    wt(trees(i-1) + sz) = log(1-err(trees(i-1) + sz)) - log(err(trees(i-1) + sz));
                    alpha = update_alpha(X,Y,t,alpha,wt(trees(i-1) + sz));
                else
                    tr(sz,:) = t;
                    err(sz) = classification_error(X,Y,t,1,alpha);
                    wt(sz) = log(1-err(sz)) - log(err(sz));
                    alpha = update_alpha(X,Y,t,alpha,wt(sz));
                end
            end
            plotclassifier(X,Y,@(X) myclassifier(X,tr(1:trees(i),:),trees(i),wt(1:trees(i))),0.5,0);
            if(d == 1)
                if(trees(i) == 1)
                    title('depth = 1, num of trees = 1');
                elseif(trees(i) == 10)
                    title('depth = 1, num of trees = 10');
                elseif(trees(i) == 100)
                    title('depth = 1, num of trees = 100');
                elseif(trees(i) == 1000)
                    title('depth = 1, num of trees = 1000');
                end
            elseif(d == 2)
                if(trees(i) == 1)
                    title('depth = 2, num of trees = 1');
                elseif(trees(i) == 10)
                    title('depth = 2, num of trees = 10');
                elseif(trees(i) == 100)
                    title('depth = 2, num of trees = 100');
                elseif(trees(i) == 1000)
                    title('depth = 2, num of trees = 1000');
                end
            elseif(d == 3)
                if(trees(i) == 1)
                    title('depth = 3, num of trees = 1');
                elseif(trees(i) == 10)
                    title('depth = 3, num of trees = 10');
                elseif(trees(i) == 100)
                    title('depth = 3, num of trees = 100');
                elseif(trees(i) == 1000)
                    title('depth = 3, num of trees = 1000');
                end
            end
        end
    end
end

function Y = myclassifier(X,t,B,w)
    Y = zeros(2500,1);
    for i = 1:B
        Y = Y + dt(X,t(i,:)).*w(i);
    end
    [m n] = size(Y);
    for j = 1:m
        if Y(j) > 0
            Y(j) = 1;
        else
            Y(j) = -1;
        end
    end
end

function err = classification_error(X,Y,t,B,alpha)
    tY  = zeros(size(Y,1),1);
    for i = 1:B
        tY = tY + dt(X,t(i,:));
    end
    tY = tY./B;
    [m n] = size(tY);
    for j = 1:m
        if tY(j) > 0
            tY(j) = 1;
        else
            tY(j) = -1;
        end
    end
    al = 0;
    for j = 1:m
        if tY(j) ~= Y(j)
            al = al + alpha(j);
        end
    end
    err = al./sum(alpha);
end

function al = update_alpha(X,Y,t,alpha,w)
    tY  = zeros(size(Y,1),1);
    tY = dt(X,t);
    [m n] = size(tY);
    al = alpha;
    for j = 1:m
        if tY(j) ~= Y(j)
            al(j) = alpha(j).*exp(w);
        end
    end
end