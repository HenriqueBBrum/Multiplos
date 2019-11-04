function interp_15(x,y)
  n = length(x);
  for i = 1:n
    P+=y(i)*L(i,n,x);
  endfor

  display(P);
  plot(x,y,'or',P);

endfunction


function retorno = L(i,n,x)
  L = 1;
  for k = 1:n
      L*=(X-x(k))/(x(i)-x(k));
  endfor

  retorno = L;
endfunction
