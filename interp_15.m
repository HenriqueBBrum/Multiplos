function interp_15(x,y)
  n = length(x);
  P = 0.0;
  for i = 1:n
    P+=y(i)*L(i,n,x);
  endfor
  
  plot(x,y,'or', x,polyval(P,x));

endfunction


function retorno = L(i,n,x)
  p = 1;
  for k = 1:n
    if x(k)!=x(i)
      L=poly(x(k))/(x(i)-x(k));
      p = conv(p,L);
    endif
  endfor

  retorno = p;
endfunction