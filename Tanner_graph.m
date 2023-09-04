function Tanner_graph = Tanner_graph(H)
    % Tanner graph of a code with parity-check matrix H
    [p, q] = size(H);
    G = graph;
    
    for i = 1:p
        G = addnode(G, ['c' num2str(i)]);
    end

    for j = 1:q
        G = addnode(G, ['v' num2str(j)]);
    end

    for i = 1:p
        for j = 1:q
            if H(i, j) == 1
                G = addedge(G, ['c' num2str(i)], ['v' num2str(j)]);
            end
        end
    end
    
    TG = G;
end




