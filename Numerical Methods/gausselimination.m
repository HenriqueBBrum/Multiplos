function gausselimination(A)
  
  for col = 1 : length(A)-1;
    
      display("-----------------------")
    
      maior = A(col,col);
      linha_maior = col;
      for i = col : length(A)-1
        if(abs(A(i,col))>abs(maior))
          temp = A([i],:);
          A([i],:) = A([linha_maior], :);
          A([linha_maior], :) = temp;
          linha_maior = i;
        endif
      endfor
            
      for linha = col : length(A)-1;
        A = A
        if(linha+1==length(A))
          break;
        endif
        mult = A(linha+1,col)/A(col,col) ;
        nova_linha = A([linha+1],:)-mult*A([col],:);
        A([linha+1], :) = nova_linha;
      endfor
    
   endfor
  
  
endfunction

