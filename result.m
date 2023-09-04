m = 4;
k = m - 1;
S = 0:k;
disp(S);

A = [];
for i = S
    if gcd(i, m) == 1
        b = i;
    end
    A = union(A, b);
    disp(A);
end

for a = A
    for s = S
        N = zeros(m, m);

        for i = 1:m
            for j = 1:m
                f = @(x) a * x - s;
                if mod(f(i - 1), m) == j - 1
                    N(i, j) = 1;
                else
                    N(i, j) = 0;
                end
            end
        end
        disp(N);
    end
end

function result = exam(m, A, S, g)
    [p, q] = size(A);
    B1 = 1:p;
    B2 = 1:q;
    
    for i0 = 1:p
        t0 = i0;
        for j0 = 1:q
            for i1 = setdiff(B1, i0)
                for j1 = setdiff(B2, j0)
                    for i2 = setdiff(B1, i1)
                        t1 = A(i1, j0) * mod(inv(A(i0, j0)), m) * (t0 + S(i0, j0)) - S(i1, j0);
                        if i2 ~= i0 && j2 ~= j0
                            if A(i2, j1) * mod(inv(A(i1, j1)), m) * (t1 + S(i1, j1)) - S(i2, j1) == t0
                                result = 1;
                                return;
                            end
                        end
                        for i3 = setdiff(B1, i2)
                            for j2 = setdiff(B2, j1)
                                t2 = A(i2, j1) * mod(inv(A(i1, j1)), m) * (t1 + S(i1, j1)) - S(i2, j1);
                                if i3 ~= i0 && j2 ~= j0
                                    if A(i3, j2) * mod(inv(A(i2, j2)), m) * (t2 + S(i2, j2)) - S(i3, j2) == t0
                                        result = 1;
                                        return;
                                    end
                                end
                                for i4 = setdiff(B1, i3)
                                    for j3 = setdiff(B2, j2)
                                        t3 = A(i3, j2) * mod(inv(A(i2, j2)), m) * (t2 + S(i2, j2)) - S(i3, j2);
                                        if i4 ~= i0 && j3 ~= j0
                                            if A(i3, j2) * mod(inv(A(i2, j2)), m) * (t2 + S(i2, j2)) - S(i3, j2) == t0
                                                result = 1;
                                                return;
                                            end
                                        end
                                    end
                                end
                            end
                        end
                    end
                end
            end
        end
    end
    
    result = 0;
end