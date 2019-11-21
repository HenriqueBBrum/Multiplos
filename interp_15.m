function interp_15(x,y)
  graphics_toolkit("gnuplot")
  n = length(x);
  P = 0.0;
  for i = 1:n
    P+=y(i)*L(i,n,x);
  endfor
  
  z = [0:0.01:x(n)];
  plot(x,y,'or',z,polyval(P,z));

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
