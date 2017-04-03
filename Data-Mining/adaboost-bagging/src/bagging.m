function bagging()
%Bagging
    clc;
    I = load('class2d.ascii','-ascii');
    X = I(:,1:2);   %80x2
    Y = I(:,3);     %80x1
    trees = [1,10,100,1000];
    tr = cell(1000,3);
    %Bagging
    for d = 1:3
        for i = 1:4
            f = 4*(d-1)+i;
            figure(f)
            remain = 1;
            if i >1
                remain = trees(i) - trees(i-1);
            end
            for sz = 1:remain
                S = datasample(I,80);
                B_X = S(:,1:2);   %80x2
                B_Y = S(:,3);     %80x1
                t = traindt(B_X,B_Y,d);
                if i > 1
                    tr(trees(i-1) + sz,:) = t;
                else
                    tr(sz,:) = t;
                end
            end
            plotclassifier(X,Y,@(X) myclassifier(X,tr(1:trees(i),:),trees(i)),0.5,0);
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

function Y = myclassifier(X,t,B)
    tY = zeros(2500,1);
    for i = 1:B
        tY = tY + dt(X,t(i,:));
    end
    Y = tY./B;
    [m n] = size(Y);
    for j = 1:m
        if Y(j) > 0
            Y(j) = 1;
        else
            Y(j) = -1;
        end
    end
end