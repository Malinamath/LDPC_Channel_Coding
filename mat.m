function M = mat(n, E)
    [p, q] = size(E);
    M = zeros(n * p, n * q);
    
    for i = 1:p
        for j = 1:q
            s = E(i, j);
            for k = 1:n
                if k + s <= n
                    M((i - 1) * n + s + k, (j - 1) * n + k) = 1;
                else
                    M((i - 2) * n + s + k, (j - 1) * n + k) = 1;
                end
            end
        end
    end
end