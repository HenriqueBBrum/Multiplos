function mnewton(f, x0, epslon)
  der = 0;
  h = 0.0001;
  i = 0;
  do
    der = (f(x0+h)-f(x0))/h;
    x = x0 - f(x0)/der;
    x0 = x;
    printf("Iteracao: %d,  x = %f, f(x) = %f\n", i, x, f(x));
    i++;
  until(f(x)<epslon)
  
  printf("Final: Iterações : %d,   x : %f\n", i, x);
  
endfunction