function formaDeNewton(x,y,x_til)
  
  n = length(x);
  D = zeros(n);
  
  for j = 1:n+1
    for i = 1:n-j+1
      D(i,j) = f_value(D,x,y,i,j);
    endfor
    
  endfor
  
  display(D)
  
  y_til = calculaPolinomio(D, x,x_til)
 
endfunction

function retorno = f_value(D,X,Y,i,j)
  if j == 1 
    retorno = Y(i);
  else
    j_ant = j - 1;
    i_ant_sup = i;
    i_ant_inf = i+1;
    %Verificar se X(1) estácorreto
    result = (D(i_ant_inf,j_ant) - D(i_ant_sup,j_ant))/(X(j) - X(1));
    retorno = result;
    
  endif
    
endfunction


function retorno = calculaPolinomio(D,X,x_til)
  Pn = 0;
  n = length(X);
  for j = 1:n
    aux = 1;
    for i = 1:j-1
      aux*=(x_til - X(i));  
    endfor
    Pn+=D(1,j)*aux;
  endfor
  
  retorno = Pn;
    
endfunction
