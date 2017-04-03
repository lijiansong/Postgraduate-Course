function spam()
%Spam data training and testing result
    clc;
    I = load('spamtest.ascii','-ascii');
    X = I(:,1:57);   %:x57
    Y = I(:,58);     %:x1
    T = load('spamtrain.ascii','-ascii');
    tX = T(:,1:57);   %:x57
    tY = T(:,58);     %:x1
    trees = floor(logspace(0,3,10));
    tr_bag = cell(1000,3);
    tr_boost = cell(1000,3);
    wt_boost = zeros(1000,1);
    err_boost = zeros(1000,1);
    test_error_bag = zeros(1,size(trees,2));
    train_error_bag = zeros(1,size(trees,2));
    test_error_boost = zeros(1,size(trees,2));
    train_error_boost = zeros(1,size(trees,2));
    for d = 1:3
        alpha  = ones(size(Y,1),1);
        for i = 1:10
            %sprintf('depth: %d trees: %d\n',d,trees(i));
            remain = 1;
            if i >1
                remain = trees(i) - trees(i-1);
            end
            for sz = 1:remain
                S = datasample(I,size(Y,1));
                B_X = S(:,1:57);   %80x57
                B_Y = S(:,58);     %80x1
                t_bag = traindt(B_X,B_Y,d);
                t_boost = traindtw(X,Y,alpha,d);
                if i > 1
                    tr_bag(trees(i-1) + sz,:) = t_bag;
                    tr_boost(trees(i-1) + sz,:) = t_boost;
                    err_boost(trees(i-1) + sz) = error_calculation(X,Y,t_boost,1,alpha);
                    wt_boost(trees(i-1) + sz) = log(1-err_boost(trees(i-1) + sz)) - log(err_boost(trees(i-1) + sz));
                    alpha = update_alpha(X,Y,t_boost,alpha,wt_boost(trees(i-1) + sz));
                else
                    tr_bag(sz,:) = t_bag;
                    tr_boost(sz,:) = t_boost;
                    err_boost(sz) = error_calculation(X,Y,t_boost,1,alpha);
                    wt_boost(sz) = log(1-err_boost(sz)) - log(err_boost(sz));
                    alpha = update_alpha(X,Y,t_boost,alpha,wt_boost(sz));
                end
            end

            test_error_bag(i) = classification_error(X,Y,tr_bag(1:trees(i),:),trees(i));
            train_error_bag(i) = classification_error(tX,tY,tr_bag(1:trees(i),:),trees(i));
            
            test_error_boost(i) = classification_error(X,Y,tr_boost(1:trees(i),:),trees(i));
            train_error_boost(i) = classification_error(tX,tY,tr_boost(1:trees(i),:),trees(i));
        end
        figure(1);
        semilogx(trees,test_error_bag,'--','LineWidth',d);
        hold on;
        semilogx(trees,train_error_bag,'LineWidth',d);
        title('Bagging');
        xlabel('number of trees');
        ylabel('error rate');
        legend('depth = 1','depth = 1','depth = 2','depth = 2','depth = 3','depth = 3');
        figure(2);
        semilogx(trees,test_error_boost,'--','LineWidth',d);
        hold on;
        semilogx(trees,train_error_boost,'LineWidth',d);
        title('AdaBoost');
        xlabel('number of trees');
        ylabel('error rate');
        legend('depth = 1','depth = 1','depth = 2','depth = 2','depth = 3','depth = 3');
    end
end

function err = classification_error(X,Y,t,B)
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
    err = 0;
    for j = 1:m
        if tY(j) ~= Y(j)
            err = err + 1;
        end
    end
    err = err./size(Y,1);
end

function err = error_calculation(X,Y,t,B,alpha)
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
    %testY  = zeros(size(Y,1),1);
    testY = dt(X,t);
    [m n] = size(testY);
    al = alpha;
    for j = 1:m
        if testY(j) ~= Y(j)
            al(j) = alpha(j).*exp(w);
        end
    end
end