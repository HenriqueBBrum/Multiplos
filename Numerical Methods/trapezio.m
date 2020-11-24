function trapezio(f,a,b,epslon)
  n = 1000;
  h = (b-a)/n;
  dxs = [];
  for i = 0:n
    dxs = derivada2(f,);
  endfunction
  
  M2 = max(dxs);
  m = sqrt(((b-a)^2*M2)/12*epslon);
  newH = (b-a)/m;
  
  for i = 0:n
    
  endfor
  
  
endfunction



function dx = derivada2(f,x)
  d = 10^(⁻5);
  dx = (f(x+2*d) - 2f(x+d)+f(x))/d^2;
endfunction 